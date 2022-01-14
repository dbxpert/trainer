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

static constexpr unsigned int INVALID_PORT_NUMBER = UINT32_MAX;

enum class Command { RUN, TERMINATE, UNKNOWN };

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

static inline std::ifstream GetConfig() {
  auto trainer_home = std::string(std::getenv("TRAINER_HOME"));
  auto config_path = trainer_home + "/client/config/trainer.cfg";
  std::ifstream config(config_path);

  if (!config.is_open()) {
    throw std::runtime_error("Cannot open file: " + config_path);
  }
  return config;
}

static inline unsigned int GetPortFromConfig() {
  auto config = GetConfig();
  return SearchConfigForPortNumber(config);
}

Server::Server()
    : running_(true), socket_fd_(socket(PF_INET, SOCK_STREAM, 0)), accepted_fd_(0), size_(sizeof(struct sockaddr_in)) {
  host_addr_.sin_family = AF_INET;
  host_addr_.sin_port = htons(GetPortFromConfig());
  host_addr_.sin_addr.s_addr = 0;
  memset(&(host_addr_.sin_zero), 0, 8);
  int iSetOption = 1;

  setsockopt(socket_fd_, SOL_SOCKET, SO_REUSEADDR, (char *)&iSetOption, sizeof(iSetOption));
}

Server::~Server() {
  close(accepted_fd_);
  close(socket_fd_);
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

static inline std::string GetUserPassword() {
  std::string password;
  std::cout << "Enter Password: ";

  HideUserInput();
  std::cin >> password;
  ShowUserInput();
  std::cout << std::endl;

  return password;
}

static inline std::string GetUserName() {
  std::string user;
  std::cout << "Enter Username: ";
  std::cin >> user;
  return user;
}

static inline void ConnectToProblemDatabase(DatabaseConnector &database_connector) {
  if (!database_connector.IsConnected()) {
    auto user = GetUserName();
    auto password = GetUserPassword();
    if (database_connector.Connect(user, password))
      throw std::runtime_error("Database connection error");
  }
}

void Server::Run() {
  ConnectToProblemDatabase(database_connector_);
  engine_.Prepare(database_connector_.GetConnection());
  Listen();

  while (running_) {
    auto msg = Receive();
    Process(msg.GetArgs());
  }
}

void Server::Listen() {
  auto host_addr = reinterpret_cast<struct sockaddr *>(&host_addr_);
  auto success = bind(socket_fd_, host_addr, sizeof(struct sockaddr));

  if (success != 0)
    std::runtime_error("Cannot bind address to the socket");

  listen(socket_fd_, 3);

  auto client_addr = reinterpret_cast<struct sockaddr *>(&client_addr_);
  accepted_fd_ = accept(socket_fd_, client_addr, &size_);
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

static inline Command InterpretRequest(std::string request) {
  std::transform(request.begin(), request.end(), request.begin(), ::toupper);
  auto interpreted_command = Command::UNKNOWN;

  if (request.compare("RUN")) {
    interpreted_command = Command::RUN;
  } else if (request.compare("TERMINATE")) {
    interpreted_command = Command::TERMINATE;
  }

  return interpreted_command;
}

void Server::Process(std::vector<std::string> args) {
  auto command = InterpretRequest(args[0]);

  switch (command) {
  case Command::RUN:
    Send(engine_.Run(std::stol(args[1])));
    break;
  case Command::TERMINATE:
    running_ = false;
    break;
  case Command::UNKNOWN:
  default:
    Send("0Server received invalid command");
    break;
  }
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