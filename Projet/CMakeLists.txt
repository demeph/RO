cmake_minimum_required(VERSION 2.8)

project(deja_ro)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lglpk -lm")
#set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -std=c++11")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Ofast -std=c++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -Og ")

include_directories(include)

add_executable(
  ro_test
  ro_test.cpp
  src/regroupement.cpp
  src/donnees.cpp
  src/chrono.cpp
  src/probleme.cpp
  src/glpkwrapper.cpp
)

target_link_libraries(ro_test glpk)

file(INSTALL full_valgrind DESTINATION . )
file(INSTALL data DESTINATION . )
