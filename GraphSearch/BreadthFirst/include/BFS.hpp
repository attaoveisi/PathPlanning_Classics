#ifndef BFS_HPP
#define BFS_HPP

/** 
 * @brief Program to print BFS traversal from a given 
 * @brief source vertex. BFS(int s) traverses vertices
 * @brief Detailed description follows here.

    
    @author Atta Oveisi
    @date Nov 2020
 */


#include <iostream> 
#include <vector> 

namespace forwardsearch{
namespace BFS{
/** 
 * @brief This class represents a directed graph using adjacency list representation
 */
class Graph 
{ 
private:
	/** 
	 * @param Vertices private parameter for No. of vertices
	 */
	int Vertices; 

	/** 
	 * @brief a vector of vectors containing adjacency lists
	 */
	std::vector<std::vector<int>> adjacent; 

public: 

	/** 
	 * @brief Constructor for accessing the private ... 
	 * @brief variable Vertices and initialization of adjacent list
	 * @param Vertices graph size (number of vertices)
	 */
	Graph(int Vertices);

	/** 
	 * @brief function to add an edge to the graph, namely adjacent object
	 * @param from: node from
	 * @param to: adjacent node to from
	 */
	void addEdge(int from, int to); 

	/** 
	 * @brief BFS traversal from a given source s 
	 */
	void BFS(int s); 

	/** 
	 * @brief prints frontier vertex  
	 */
	void print_quene(int vortex);
	void print_quene();
}; 
} // BFS
} // forwardsearch

#endif // BFS_HPP