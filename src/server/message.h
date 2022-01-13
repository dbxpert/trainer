#ifndef EXECUTOR_TRAINER_MESSAGE_H_
#define EXECUTOR_TRAINER_MESSAGE_H_

#include <sstream>
#include <string>
#include <vector>

class Message {
 public:
  explicit Message(char *msg) : msg_(msg) { Parse(); };
  ~Message() = default;

  const std::vector<std::string> &GetArgs() const { return args_; }

 private:
  void Parse() {
    std::istringstream s(msg_);
    std::string arg;
    char separator = ',';

    while (getline(s, arg, separator)) {
      args_.push_back(arg);
    }
  }

  const std::string msg_;
  std::vector<std::string> args_;
};

#endif /* EXECUTOR_TRAINER_MESSAGE_H_ */