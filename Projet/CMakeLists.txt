cmake_minimum_required(VERSION 2.8)

project(deja_ro)


#set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -pg -Og -std=c++11 -ldl")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -Og ")

include_directories(include)

add_executable(
  ro_test
  ro_test.cpp
  src/tournee.cpp
)

#file(INSTALL res/ DESTINATION res/)
