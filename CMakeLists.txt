cmake_minimum_required(VERSION 3.0.0)
set(PROJ_NAME "trainer")
set(PROJ_VERSION "3.0.0")
project(${PROJ_NAME} VERSION ${PROJ_VERSION})

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 20)

option(BUILD_UNIT_TESTS "Build unit test" OFF)

if (BUILD_UNIT_TESTS)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()

set(LIBRARY_NAME_PREFIX trainer) 

add_subdirectory(src)
