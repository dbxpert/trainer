#include <cassert>
#include <iostream>
#include <string>
#include "server.h"

int main() {
  Server server;

  try {
    server.Run();
  } catch (const std::exception& e) {
    std::cout << '\n' << "ERROR: " << e.what() << std::endl; 
    std::cout << "SERVER ABORTED ABNORMALLY" << std::endl;
    return -1;
  }

  return 0;
}