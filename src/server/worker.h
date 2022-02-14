#ifndef EXECUTOR_TRAINER_WORKER_H_
#define EXECUTOR_TRAINER_WORKER_H_

#include "message.h"
#include <vector>
#include <string>

class Engine;

class Worker {
 public:
  Worker(const int accepted_fd, Engine &);
  ~Worker();

  void Run();

 private:
  template <Command>
  void Process(const Message &) {}

  void ProcessRequest(const Message &);
  void SendReply(std::string msg);

  int accepted_fd_;
  bool running_;
  Engine &engine_;
};

#endif /* EXECUTOR_TRAINER_WORKER_H_ */