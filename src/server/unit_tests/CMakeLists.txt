set(TRAINER_TEST_BINARY trainer_unit_test)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/tests)

file(GLOB_RECURSE TEST_SOURCE_FILES LIST_DIRECTORIES false *.h *.cc)
set(TEST_SOURCE ${TEST_SOURCE_FILES})

add_executable(${TRAINER_TEST_BINARY} ${TEST_SOURCE})
target_link_libraries(${TRAINER_TEST_BINARY} server gtest_main)
target_include_directories(${TRAINER_TEST_BINARY} PUBLIC ${CMAKE_SOURCE_DIR}/src/server)
