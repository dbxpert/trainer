#ifndef EXECUTOR_TRAINER_MESSAGE_H_
#define EXECUTOR_TRAINER_MESSAGE_H_

enum class Command {
  RUN_SOLUTION,
  PREPARE_DEBUG,
  VERIFY_DEBUG,
  REQUEST_FIN,
  ACK_FIN,
  UNKNOWN
};

class Message {
 public:
  explicit Message(const char *raw_message);
  ~Message() = default;

  const Command GetCommandType() const;
  const std::string &GetCommandArgument() const;

 private:
  Command command_type_;
  std::string argument_;
};

#endif /* EXECUTOR_TRAINER_MESSAGE_H_ */
