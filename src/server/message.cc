#include "message.h"
#include <string>
#include <sstream>
#include <vector>
#include <cassert>

static constexpr std::size_t MAX_COMMAND_COUNT = static_cast<std::size_t>(Command::UNKNOWN);
static inline const std::string CommandToString(Command command) noexcept {
  switch (command) {
    case Command::RUN_SOLUTION:
      return "RUN_SOLUTION";
    case Command::PREPARE_DEBUG:
      return "PREPARE_DEBUG";
    case Command::VERIFY_DEBUG:
      return "VERIFY_DEBUG";
    case Command::REQUEST_FIN:
      return "REQUEST_FIN";
    case Command::ACK_FIN:
      return "ACK_FIN";
    default:
      return "UNKNOWN";
  }
}

static inline std::vector<std::string> ParseMessage(const char *raw_message) {
  std::istringstream stream(raw_message);

  std::string argument;
  std::vector<std::string> result;
  char separator = ',';

  while (getline(stream, argument, separator)) {
    result.push_back(argument);
  }

  return result;
}

static inline Command InterpretCommandType(const std::string &command) {
  std::vector<std::string> command_vector;
  for (std::size_t i = 0; i < MAX_COMMAND_COUNT; ++i) {
    command_vector.push_back(CommandToString(static_cast<Command>(i)));
  }

  Command result = Command::UNKNOWN;
  for (std::size_t i = 0; i < MAX_COMMAND_COUNT; ++i) {
    if (command.compare(command_vector[i].c_str()) == 0)
      result = static_cast<Command>(i);
  }

  return result;
}

Message::Message(const char *raw_message) {
  auto parsed_message = ParseMessage(raw_message);

  assert(!parsed_message.empty());

  command_type_ = InterpretCommandType(parsed_message[0]);
  argument_ = parsed_message.size() > 1 ? parsed_message[1] : "";
}

const Command Message::GetCommandType() const {
  return command_type_;
}

const std::string &Message::GetCommandArgument() const {
  return argument_;
}