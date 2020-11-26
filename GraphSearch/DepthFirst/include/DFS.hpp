#ifndef DFS_HPP
#define DFS_HPP

/** 
 * @brief C++ program to print DFS traversal from
 * @brief a given vertex in a given graph

    
    @author Atta Oveisi
    @date Nov 2020
 */

#include <iostream> 
#include <list> 

namespace forwardsearch{
namespace DFS{

/**
 * @brief Graph class represents a directed graph
 * @brief using adjacency list representation
 * 
 */
class Graph {

private:
	/**
	 * @brief number of vertices for DFS
	 * 
	 */
	int n_Vertices; 

	/**
	 * @brief Pointer to an array containing adjacency lists
	 * 
	 */
	std::list<int>* adjacent;

	/**
	 * @brief A recursive function used by DFS
	 * 
	 */
	void DFSUtil(int v, bool visited[]);

public:
	Graph(int n_Vertices); // Constructor
 
	/**
	 * @brief function to add an edge to graph
	 * 
	 */
	void addEdge(int v, int w);

	/**
	 * @brief DFS traversal of the vertices reachable from v
	 * 
	 */
	void DFS(int v);
};
} // DFS
} // forwardsearch

#endif // DFS_HPP