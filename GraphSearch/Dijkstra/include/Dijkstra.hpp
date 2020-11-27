#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP
  
/** 
 * @brief A C++ program for Dijkstra's single source shortest path algorithm.
 * @brief The program is for adjacency matrix representation of the graph
   @author Atta Oveisi
   @date Nov 2020
 */

#include <limits.h> 
#include <stdio.h> 
#include <iostream>
#include <vector>

namespace forwardsearch{
namespace Dijkstra{

/**
 * @brief Graph class represents a directed graph
 * @brief using weighted adjacency list representation
 * 
 */
class Graph{
private:
	/**
	 * @brief number of vertices for DFS in the graph
	 * 
	 */
	int n_Vertices;
	int m_Vertices;

	/**
	 * @brief Graph architechture 
	 * 
	 */
	std::vector<std::vector<int>> graph;
public:
	/**
	 * @brief explicit constructor
	 * 
	 */
	Graph(int n_Vertices, int m_Vertices); // Constructor

	/**
	 * @brief Fill out data in the graph
	 * 
	 */
	

	/**
	 * @brief A utility function to find the vertex with minimum distance value, from
	 * the set of vertices not yet included in shortest path tree
	 * 
	 */
	int minDistance(std::vector<int> dist, std::vector<bool> sptSet);

	/**
	 * @brief A utility function to print the constructed distance array
	 * 
	 */
	void printSolution(std::vector<int> dist);

	/**
	 * @brief Function that implements Dijkstra's single source shortest path algorithm
	 * for a graph represented using adjacency matrix representation
	 * 
	 */
	void dijkstra(int source);
};
} // Dijkstra
} // forwardsearch

#endif // DIJKSTRA_HPP