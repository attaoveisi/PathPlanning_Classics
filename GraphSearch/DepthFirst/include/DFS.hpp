#ifndef DFS_HPP
#define DFS_HPP

/** 
 * @brief C++ program to print DFS traversal from
 * @brief a given vertex in a given graph

    
    @author Atta Oveisi
    @date Nov 2020
 */

#include <iostream> 
#include <vector> 

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
	 * @brief Adjacent list of vectors for all vertices
	 * 
	 */
	std::vector<std::vector<int>> adjacent;

	/**
	 * @brief A recursive function used by DFS
	 * 
	 */
	void DFSUtil(int vertex, std::vector<bool> visited);

public:
	Graph(int n_Vertices); // Constructor
 
	/**
	 * @brief function to add an edge to graph
	 * 
	 */
	void addEdge(int from, int to);

	/**
	 * @brief DFS traversal of the vertices reachable from v
	 * 
	 */
	void DFS();

	/** 
	 * @brief prints frontier vertex  
	 */
	void print_quene(int vertex);
	void print_quene();
};
} // DFS
} // forwardsearch

#endif // DFS_HPP