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

find_package(Boost REQUIRED)
message(STATUS "Boost version: ${Boost_VERSION}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

option(BUILD_SOLUTION_ONLY "Build solution only" OFF)

if (NOT BUILD_SOLUTION_ONLY)
  add_subdirectory(src)
endif()
add_subdirectory(solutions)
