set(TRAINER_TEST_BINARY trainer_unit_test)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/tests)

file(GLOB TEST_SOURCE_FILES *.h *.cc)
set(TEST_SOURCE ${TEST_SOURCE_FILES})

add_executable(${TRAINER_TEST_BINARY} ${TEST_SOURCE})
target_link_libraries(${TRAINER_TEST_BINARY} 
  gtest_main
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
target_include_directories(${TRAINER_TEST_BINARY} PUBLIC ${CMAKE_SOURCE_DIR}/src/server)
