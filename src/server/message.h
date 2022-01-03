#ifndef EXECUTOR_TRAINER_MESSAGE_H_
#define EXECUTOR_TRAINER_MESSAGE_H_

#include <string>
#include <vector>
#include <sstream>

class Message {
  public:
    using arguement_type = std::vector<std::string>;

    Message() = default;
    explicit Message(char* msg) : msg_(msg) { Parse(); };
    ~Message() = default;

    arguement_type GetArgs() { return args_; }

  private:
    void Parse() {
      std::istringstream s(msg_);
      std::string arg;
      char separator = ',';

      while (getline(s, arg, separator)) {
        args_.push_back(arg);
      }
    }

    std::string msg_;
    arguement_type args_;
};


#endif /* EXECUTOR_TRAINER_MESSAGE_H_ */
