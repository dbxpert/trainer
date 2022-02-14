include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(engine)
add_subdirectory(server)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(TRAINER_BINARY_NAME trsvr)
add_executable(${TRAINER_BINARY_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/server/main.cc)
target_link_directories(${TRAINER_BINARY_NAME} PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_libraries(${TRAINER_BINARY_NAME} PRIVATE
  trserver
  trengine
  tbcli
  tbcliin
  common
  mio
  rt
  pthread
)
target_include_directories(${TRAINER_BINARY_NAME} PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}/server 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/engine
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  )
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(tests)
