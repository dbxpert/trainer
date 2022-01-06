include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# include tibero client libraries
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_subdirectory(server)
add_subdirectory(solution)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable(trainer ${CMAKE_CURRENT_SOURCE_DIR}/server/main.cc)
target_link_libraries(trainer
  server
  tbcli
  clialloc
  tbcliin
  common
  mio
  datatype
  tbmsg
  tbstr
  clientcommon
  env_client
)
target_include_directories(trainer PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/server 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

option(BUILD_UNIT_TESTS "Build unit test" OFF)

if (BUILD_UNIT_TESTS)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  add_subdirectory(tests)
endif()
