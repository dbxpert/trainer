#include <algorithm> // for upper
#include <cstdlib> // for getenv
#include <cstring> // for memset
#include <cctype> // for upper
#include <fstream> // for ifstream
#include <stdexcept>
#include "server.h"
#include "run_test.h"

static inline unsigned int SearchLineForPortNumber(const std::string &line) {
  auto pos = line.find("=");
  if (pos != std::string::npos) {
    auto key = line.substr(0, pos);
    if (key.compare("PORT_NUMBER") == 0) {
      return std::stol(line.substr(pos + 1));
    }
  }
  
  return UINT32_MAX;
}

static inline unsigned int GetPortFromConfig() {
  auto trainer_home = std::string(std::getenv("TRAINER_HOME"));
  auto config_path = trainer_home + "client/config/trainer.cfg";
  std::ifstream config(config_path);

  if (!config.is_open()) {
    throw std::runtime_error("Cannot open file: " + config_path);
  }

  std::string line;
  unsigned int port_number = UINT32_MAX;
  while (getline(config, line)) {
    port_number = SearchLineForPortNumber(line);
  }

  if (port_number == UINT32_MAX) {
    throw std::runtime_error("Cannot find option PORT_NUMBER");
  }

  return port_number;
}

Server::Server() 
  : running_(true),
    socket_fd_(socket(PF_INET, SOCK_STREAM, 0)),
    accepted_fd_(0),
    size_(sizeof(struct sockaddr_in)) {
  host_addr_.sin_family = AF_INET;
  host_addr_.sin_port = htons(GetPortFromConfig());
  host_addr_.sin_addr.s_addr = 0;
  memset(&(host_addr_.sin_zero), 0, 8);
  int iSetOption = 1;

  setsockopt(socket_fd_, SOL_SOCKET, SO_REUSEADDR, (char*)&iSetOption,
      sizeof(iSetOption));
}

Server::~Server() {
 close(accepted_fd_);
 close(socket_fd_);
}

void Server::Run() {
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

static inline std::string Upper(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(), ::toupper);
  return str;
}

void Server::Process(std::vector<std::string> args) {
    auto command = Upper(args[0]);

    if (command.compare("RUN")) {
      auto problem = std::stol(args[1]);
      auto result = RunTest(problem);
      Send(result);
    } else if (command.compare("TERMINATE")) {
      running_ = false;
    } else {
      Send("0Server received invalid command");
    }
}

void Server::Send(std::string msg) {
  int msg_size = msg.size();
  std::vector<unsigned char> byte_array;

  for (int i = 0; i < sizeof(int); ++i) {
    byte_array.push_back(msg_size & 0xFF);     
    msg_size >>= CHAR_BIT;
  }
  
  std::string header(byte_array.begin(), byte_array.end());

  send(accepted_fd_, header.c_str(), header.size(), 0);
  send(accepted_fd_, msg.c_str(), msg.size(), 0);
}

