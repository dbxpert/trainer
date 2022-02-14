set(TRAINER_TEST_BINARY trtest)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

file(GLOB TEST_SOURCE_FILES *.h *.cc)
set(TEST_SOURCE ${TEST_SOURCE_FILES})

add_executable(${TRAINER_TEST_BINARY} ${TEST_SOURCE})
target_link_directories(${TRAINER_TEST_BINARY} PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_libraries(${TRAINER_TEST_BINARY} PRIVATE 
  gtest_main
  trserver
  trengine
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
  rt
  pthread
)
target_include_directories(${TRAINER_TEST_BINARY} PRIVATE
  ${CMAKE_SOURCE_DIR}/src/server
  ${CMAKE_SOURCE_DIR}/src/engine
)
