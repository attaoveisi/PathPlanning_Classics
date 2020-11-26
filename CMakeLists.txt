cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE Debug)

project(PathPlanning VERSION 1.1.0)

set(sources GraphSearch/BreadthFirst/src/main.cpp)
set(include GraphSearch/BreadthFirst/include/BFS.cpp GraphSearch/BreadthFirst/include/BFS.hpp)
include_directories(GraphSearch/BreadthFirst/include)

add_executable(${PROJECT_NAME} ${sources} ${include})

#install(TARGETS ${PROJECT_NAME} DESTINATION bin)
#install(FILES main.cpp DESTINATION src)

#include(CTest)
#add_test("test1" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")

#include(CPack)