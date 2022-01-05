#include <cassert>
#include <iostream>
#include "server.h"

int main() {
  Server server;

  try {
    server.Run();
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
    return -1;
  }

  return 0;
}