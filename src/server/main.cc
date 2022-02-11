#include "server.h"
#include <cassert>
#include <iostream>
#include <string>
#include <utility>

static constexpr int REQUIRED_ARGUMENT_COUNT = 2;
using UserInfo = std::pair<std::string, std::string>;

static inline UserInfo ParseDatabaseUserInfo(const char *const arg);
static inline void RunServer(const UserInfo &);

static inline void ExitFailure(const char *exception); 
static inline void ExitSuccess();

int main(int argc, char **args) {
  if (argc != REQUIRED_ARGUMENT_COUNT)
    ExitFailure("Wrong number of arguments: trsvr [username]/[password]");

  try {
    auto user_info = ParseDatabaseUserInfo(args[1]);
    RunServer(user_info); 
  } catch (const std::exception &e) {
    ExitFailure(e.what());
  }

  ExitSuccess();
}

static inline UserInfo ParseDatabaseUserInfo(const char *const arg) {
  std::string argument(arg);
  auto delimeter_pos = argument.find("/");
  auto username = argument.substr(0, delimeter_pos);
  auto password = argument.substr(delimeter_pos + 1);
  return std::make_pair(username, password);
}

static inline void RunServer(const UserInfo &user_info) {
  Server server;
  server.PrepareTrainerDatabase(user_info.first, user_info.second);
  server.Run();
}

static inline void ExitFailure(const char *exception) {
  std::cout << '\n' << "ERROR: " << exception << std::endl;
  std::cout << "SERVER ABORTED ABNORMALLY" << std::endl;
  exit(EXIT_FAILURE);
}

static inline void ExitSuccess() {
  std::cout << '\n' << "Bye" << std::endl;
  exit(EXIT_SUCCESS);
}