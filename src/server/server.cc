#include "server.h"
#include <algorithm> // for upper
#include <cctype>    // for upper
#include <climits>
#include <cstdlib> // for getenv
#include <cstring> // for memset
#include <fstream> // for ifstream
#include <iostream>
#include <termios.h>
#include <unistd.h>

enum class Command { RUN, DEBUG, FIN_REQ, FIN_ACK, UNKNOWN };

static constexpr unsigned int INVALID_PORT_NUMBER = UINT32_MAX;

static inline unsigned int SearchLineForPortNumber(const std::string &line);
static inline unsigned int SearchConfigForPortNumber(std::ifstream &config);
static inline std::ifstream GetConfig();
static inline unsigned int GetPortFromConfig();
static inline void ConnectToProblemDatabase(DatabaseConnector &database_connector);
static inline std::string GetUserName();
static inline std::string GetUserPassword(const std::string &user);
static inline void HideUserInput();
static inline void ShowUserInput();
static inline Command InterpretRequest(std::string request);

Server::Server()
    : running_(false),
      socket_fd_(socket(PF_INET, SOCK_STREAM, 0)),
      accepted_fd_(0),
      size_(sizeof(struct sockaddr_in)) {
  host_addr_.sin_family = AF_INET;
  host_addr_.sin_port = htons(GetPortFromConfig());
  host_addr_.sin_addr.s_addr = 0;
  memset(&(host_addr_.sin_zero), 0, 8);
  int iSetOption = 1;

  setsockopt(socket_fd_, SOL_SOCKET, SO_REUSEADDR, (char *)&iSetOption, sizeof(iSetOption));
}

static inline unsigned int GetPortFromConfig() {
  auto config = GetConfig();
  return SearchConfigForPortNumber(config);
}

static inline std::ifstream GetConfig() {
  auto trainer_home = std::string(std::getenv("TRAINER_HOME"));
  auto config_path = trainer_home + "/client/config/trainer.cfg";
  std::ifstream config(config_path);

  if (!config.is_open()) {
    throw std::runtime_error("Cannot open file: " + config_path);
  }
  return config;
}

static inline unsigned int SearchConfigForPortNumber(std::ifstream &config) {
  std::string line;
  unsigned int port_number = INVALID_PORT_NUMBER;

  while (getline(config, line)) {
    port_number = SearchLineForPortNumber(line);
  }

  if (port_number == INVALID_PORT_NUMBER) {
    throw std::runtime_error("Cannot find option PORT_NUMBER");
  }

  return port_number;
}

static inline unsigned int SearchLineForPortNumber(const std::string &line) {
  auto pos = line.find("=");

  if (pos != std::string::npos) {
    auto key = line.substr(0, pos);
    if (key.compare("PORT_NUMBER") == 0) {
      return std::stol(line.substr(pos + 1));
    }
  }

  return INVALID_PORT_NUMBER;
}

Server::~Server() {
  close(accepted_fd_);
  close(socket_fd_);
}

void Server::Run() {
  ConnectToProblemDatabase(database_connector_);
  engine_.Prepare(database_connector_.GetConnection());
  Bind();

  while (true) {
    Listen();
    while (running_) {
      try {
        auto msg = Receive();
        Process(msg.GetArgs());
      } catch (const std::runtime_error &e) {
        std::string what(e.what());
        SendError(what);
      }
    }
  }
}

static inline void ConnectToProblemDatabase(DatabaseConnector &database_connector) {
  std::cout << "Connecting to Trainer DB..." << std::endl;

  constexpr int MAXIMUM_TRY_COUNT = 3;
  int try_count = 0;
  while (!database_connector.IsConnected()) {
    ++try_count; 

    auto user = GetUserName();
    auto password = GetUserPassword(user);

    if (!database_connector.Connect(user, password)) {
      if (try_count < MAXIMUM_TRY_COUNT)
        std::cout << "Sorry, try again." << '\n' << std::endl;
      else
        throw std::runtime_error("Database connection error");
    }
  }
  std::cout << "Connected!" << std::endl;
  std::cout << std::endl;
}

static inline std::string GetUserName() {
  std::string user;
  std::cout << "Enter Username: ";
  std::cin >> user;
  return user;
}

static inline std::string GetUserPassword(const std::string &user) {
  std::string password;
  std::cout << "Enter Password For " << user << ": ";

  HideUserInput();
  std::cin >> password;
  ShowUserInput();
  std::cout << std::endl;

  return password;
}

static inline void HideUserInput() {
  termios tty;
  tcgetattr(STDIN_FILENO, &tty);
  tty.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

static inline void ShowUserInput() {
  termios tty;
  tcgetattr(STDIN_FILENO, &tty);
  tty.c_lflag |= ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void Server::Bind() {
  auto host_addr = reinterpret_cast<struct sockaddr *>(&host_addr_);
  auto success = bind(socket_fd_, host_addr, sizeof(struct sockaddr));

  if (success != 0)
    std::runtime_error("Cannot bind address to the socket");

  listen(socket_fd_, 3);
}

void Server::Listen() {
  auto client_addr = reinterpret_cast<struct sockaddr *>(&client_addr_);
  accepted_fd_ = accept(socket_fd_, client_addr, &size_);
  running_ = true;
}

Message Server::Receive() {
  memset(static_cast<void *>(buffer_), 0, BUF_SIZE);

  auto recv_length = 0;
  while ((recv_length = recv(accepted_fd_, &buffer_, BUF_SIZE, 0)) == 0) {
    if (std::strcmp(strerror(errno), "Success") == 0)
      continue;
    else {
      recv_length = -1;
      break;
    }
  }

  if (recv_length == -1) {
    throw std::runtime_error(std::string("Receive Error : ") + strerror(errno));
  }

  return Message(buffer_);
}

void Server::Process(std::vector<std::string> args) {
  auto command = InterpretRequest(args[0]);

  switch (command) {
  case Command::RUN:
  case Command::DEBUG:
    SendResult(engine_.Run(std::stol(args[1]), command == Command::DEBUG));
    break;
  case Command::FIN_REQ:
    Send("ACK");
    break;
  case Command::FIN_ACK:
    close(accepted_fd_);
    running_ = false;
    break;
  case Command::UNKNOWN:
  default:
    throw std::runtime_error("Server received invalid command");
  }
}

static inline Command InterpretRequest(std::string request) {
  std::transform(request.begin(), request.end(), request.begin(), ::toupper);
  auto interpreted_command = Command::UNKNOWN;

  if (request.compare("RUN") == 0) {
    interpreted_command = Command::RUN;
  } else if (request.compare("DEBUG") == 0) {
    interpreted_command = Command::DEBUG;
  } else if (request.compare("FIN") == 0) {
    interpreted_command = Command::FIN_REQ;
  } else if (request.compare("ACK") == 0) {
    interpreted_command = Command::FIN_ACK;
  }

  return interpreted_command;
}

void Server::Send(std::string msg) {
  int msg_size = msg.size();
  std::vector<unsigned char> byte_array;

  for (std::size_t i = 0; i < sizeof(int); ++i) {
    byte_array.push_back(msg_size & 0xFF);
    msg_size >>= CHAR_BIT;
  }

  std::string header(byte_array.begin(), byte_array.end());

  send(accepted_fd_, header.c_str(), header.size(), 0);
  send(accepted_fd_, msg.c_str(), msg.size(), 0);
}

void Server::SendResult(std::string result) {
  std::string header = "0";
  Send(header + result);
}

void Server::SendError(std::string error) {
  std::string header = "1";
  Send(header + error);
}