#include "server.h"
#include "worker.h"
#include <cstdlib> // for getenv
#include <cstring> // for memset
#include <fstream> // for ifstream
#include <iostream>

static constexpr unsigned int INVALID_PORT_NUMBER = UINT32_MAX;

static inline unsigned int GetPortFromConfig();
static inline void InitializeHostAddress(struct sockaddr_in &host_addr); 
static inline std::ifstream GetConfig();
static inline unsigned int SearchConfigForPortNumber(std::ifstream &config);
static inline unsigned int SearchLineForPortNumber(const std::string &line);
static inline void InitializeSocket(const int socket_fd);

Server::Server()
    : socket_fd_(socket(PF_INET, SOCK_STREAM, 0)),
      accepted_fd_(0),
      size_(sizeof(struct sockaddr_in)) {
  InitializeHostAddress(host_addr_);
  InitializeSocket(socket_fd_);
}

static inline void InitializeHostAddress(struct sockaddr_in &host_addr) {
  host_addr.sin_family = AF_INET;
  host_addr.sin_port = htons(GetPortFromConfig());
  host_addr.sin_addr.s_addr = 0;
  memset(&(host_addr.sin_zero), 0, 8);
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

static inline void InitializeSocket(const int socket_fd) {
  int iSetOption = 1;
  setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&iSetOption, sizeof(iSetOption));
}

Server::~Server() {
  close(accepted_fd_);
  close(socket_fd_);
}

void Server::PrepareTrainerDatabase(const std::string &username, const std::string &password) {
  std::cout << '\n' << "Connecting to Trainer DB..." << std::endl;

  if (!database_connector_.Connect(username, password))
    throw std::runtime_error("Database connection error");

  std::cout << "Connected!" << '\n' << std::endl;

  engine_.PrepareTables(database_connector_.GetConnection());
}

void Server::Run() {
  Bind();

  while (true) {
    auto accepted_fd = Listen();
    Worker worker(accepted_fd, engine_);
    worker.Run();
  }
}

void Server::Bind() {
  auto host_addr = reinterpret_cast<struct sockaddr *>(&host_addr_);
  auto success = bind(socket_fd_, host_addr, sizeof(struct sockaddr));

  if (success != 0)
    std::runtime_error("Cannot bind address to the socket");

  listen(socket_fd_, 3);
}

const int Server::Listen() {
  auto client_addr = reinterpret_cast<struct sockaddr *>(&client_addr_);
  auto accepted_fd = accept(socket_fd_, client_addr, &size_);
  return accepted_fd;
}
