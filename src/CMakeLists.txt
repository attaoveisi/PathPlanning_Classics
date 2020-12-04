cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE Debug)

project(PathPlanning VERSION 1.1.0)

#set(sources_DFS GraphSearch/DepthFirst/src/test_DFS.cpp)
#set(sources_BFS GraphSearch/BreadthFirst/src/test_BFS.cpp)
#set(sources_Dijkstra GraphSearch/Dijkstra/src/test_Dijkstra.cpp)
set(sources_A_Star GraphSearch/A_Star/src/test_A_Star.cpp)

#set(include_DFS GraphSearch/DepthFirst/include/DFS.cpp GraphSearch/DepthFirst/include/DFS.hpp)
#set(include_BFS GraphSearch/BreadthFirst/include/BFS.cpp GraphSearch/BreadthFirst/include/BFS.hpp)
#set(include_Dijkstra GraphSearch/Dijkstra/include/Dijkstra.cpp GraphSearch/Dijkstra/include/Dijkstra.hpp)
set(include_A_Star GraphSearch/A_Star/include/A_Star.cpp GraphSearch/A_Star/include/A_Star.hpp)


#set(additional_dirs_BFS GraphSearch/BreadthFirst/include)
#set(additional_dirs_DFS GraphSearch/DepthFirst/include)
#set(additional_dirs_Dijkstra GraphSearch/Dijkstra/include)
set(additional_dirs_A_Star GraphSearch/A_Star/include)


#include_directories(${additional_dirs_DFS})
#include_directories(${additional_dirs_BFS})
#include_directories(${additional_dirs_Dijkstra})
include_directories(${additional_dirs_A_Star})


#add_executable(${PROJECT_NAME} ${sources_DFS} ${include_DFS})
#add_executable(${PROJECT_NAME} ${sources_BFS} ${include_BFS})
#add_executable(${PROJECT_NAME} ${sources_Dijkstra} ${include_Dijkstra})
add_executable(${PROJECT_NAME} ${sources_A_Star} ${include_A_Star})


#install(TARGETS ${PROJECT_NAME} DESTINATION bin)
#install(FILES main.cpp DESTINATION src)

#include(CTest)
#add_test("test1" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")

#include(CPack)