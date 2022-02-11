#ifndef EXECUTOR_TRAINER_SERVER_H_
#define EXECUTOR_TRAINER_SERVER_H_

#include "database_connector.h"
#include "engine/engine.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

class Server {
 public:
  Server();
  ~Server();

  void PrepareTrainerDatabase(const std::string &, const std::string &);
  void Run();

 private:
  void Bind();
  const int Listen();
  
  int socket_fd_;
  int accepted_fd_;
  socklen_t size_;
  struct sockaddr_in host_addr_;
  struct sockaddr_in client_addr_;

  DatabaseConnector database_connector_;
  Engine engine_;
};

#endif /* EXECUTOR_TRAINER_SERVER_H_ */