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
