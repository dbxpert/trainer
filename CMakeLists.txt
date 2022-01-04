cmake_minimum_required(VERSION 3.0.0)
set(PROJ_NAME "trainer")
set(PROJ_VERSION "3.0.0")
project(${PROJ_NAME} VERSION ${PROJ_VERSION})

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  )
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(LIBRARY_NAME_PREFIX trainer) 

add_subdirectory(src)
