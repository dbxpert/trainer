#include "worker.h"
#include "engine/engine.h"
#include <unistd.h>
#include <sys/socket.h>
#include <cstring>
#include <stdexcept>
#include <climits>

static const std::string RESULT_MESSAGE_HEADER = "0";
static const std::string ERROR_MESSAGE_HEADER = "1";
static const std::string ACK_MESSAGE = "ACK";

static inline std::string AddResultHeaderToReply(std::string message);
static inline std::string AddErrorHeaderToReply(std::string message);
static inline Message ReceiveMessageFromClient(const int);

Worker::Worker(const int accepted_fd, Engine &engine) 
    : accepted_fd_(accepted_fd),
      running_(true),
      engine_(engine) {}

Worker::~Worker() {
  close(accepted_fd_);
}

template <>
void Worker::Process<Command::RUN_SOLUTION>(const Message &message) {
  auto problem_number = std::stoi(message.GetCommandArgument());
  auto result = engine_.RunSolution(problem_number);
  SendReply(AddResultHeaderToReply(result));
}

static inline std::string AddResultHeaderToReply(std::string message) {
  return RESULT_MESSAGE_HEADER + message;
}

template <>
void Worker::Process<Command::PREPARE_DEBUG>(const Message &message) {
  auto problem_number = std::stoi(message.GetCommandArgument());
  engine_.PrepareDebug(problem_number);
  SendReply(ACK_MESSAGE);
}

template <>
void Worker::Process<Command::VERIFY_DEBUG>(const Message &message) {
  auto problem_number = std::stoi(message.GetCommandArgument());
  auto result = engine_.CheckResult(problem_number);
  SendReply(AddResultHeaderToReply(result));
}

template <>
void Worker::Process<Command::REQUEST_FIN>(const Message &message) {
  SendReply(ACK_MESSAGE);
}

template <>
void Worker::Process<Command::ACK_FIN>(const Message &message) {
  close(accepted_fd_);
  running_ = false;
}

void Worker::Run() {
  while (running_) {
    auto message = ReceiveMessageFromClient(accepted_fd_);
    try {
      ProcessRequest(message);
    } catch (const std::runtime_error &e) {
      std::string what(e.what());
      SendReply(AddErrorHeaderToReply(what));
    }
  }
}

static inline Message ReceiveMessageFromClient(const int accepted_fd) {
  constexpr std::size_t MESSAGE_BUFFER_SIZE = 1024;
  char message_buffer[MESSAGE_BUFFER_SIZE]{};
  
  memset(static_cast<void *>(message_buffer), 0, MESSAGE_BUFFER_SIZE);
 
  recv(accepted_fd, &message_buffer, MESSAGE_BUFFER_SIZE, 0);
  
  if (std::strcmp(strerror(errno), "Success") != 0)
    throw std::runtime_error(std::string("Receive Error : ") + strerror(errno));

  return Message(message_buffer);
}

void Worker::ProcessRequest(const Message &message) {
  switch (message.GetCommandType()) {
  case Command::RUN_SOLUTION:
    Process<Command::RUN_SOLUTION>(message);
    break;
  case Command::PREPARE_DEBUG:
    Process<Command::PREPARE_DEBUG>(message);
    break;
  case Command::VERIFY_DEBUG:
    Process<Command::VERIFY_DEBUG>(message);
    break;
  case Command::REQUEST_FIN:
    Process<Command::REQUEST_FIN>(message);
    break;
  case Command::ACK_FIN:
    Process<Command::ACK_FIN>(message);
    break;
  case Command::UNKNOWN:
  default:
    throw std::runtime_error("Server received invalid command");
  }
}

static inline std::string AddErrorHeaderToReply(std::string message) {
  return ERROR_MESSAGE_HEADER + message;
}

void Worker::SendReply(std::string message) {
  int msg_size = message.size();
  std::vector<unsigned char> byte_array;

  for (std::size_t i = 0; i < sizeof(int); ++i) {
    byte_array.push_back(msg_size & 0xFF);
    msg_size >>= CHAR_BIT;
  }

  std::string header(byte_array.begin(), byte_array.end());

  send(accepted_fd_, header.c_str(), header.size(), 0);
  send(accepted_fd_, message.c_str(), message.size(), 0);
}