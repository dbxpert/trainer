include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(solutions)
add_subdirectory(framework)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_executable(trsol ${CMAKE_CURRENT_SOURCE_DIR}/framework/main.cc)
target_link_directories(trsol PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_libraries(trsol solfrwk solutions rt pthread)
target_include_directories(trsol PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/solutions
  ${CMAKE_CURRENT_SOURCE_DIR}/framework
)
