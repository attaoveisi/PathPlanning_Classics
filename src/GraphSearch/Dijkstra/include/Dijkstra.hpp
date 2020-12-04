#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP
  
/** 
 * @brief A C++ program for Dijkstra's single source shortest path algorithm.
 * @brief The program is for adjacency matrix representation of the graph
   @author Atta Oveisi
   @date Nov 2020
 */

#include <limits> 
#include <stdio.h> 
#include <iostream>
#include <vector>
#include <typeinfo>

namespace forwardsearch{
namespace Dijkstra{

/**
 * @brief Graph class represents a directed graph
 * @brief using weighted adjacency list representation
 * 
 */
template<class T>
class Graph{
private:
	/**
	 * @brief number of vertices for DFS in the graph
	 * 
	 */
	const int n_Vertices;
	const int m_Vertices;

	/**
	 * @brief Graph architechture 
	 * 
	 */
	std::vector<std::vector<T>> graph;
public:
	/**
	 * @brief explicit constructor
	 * 
	 */
	Graph(const int n_Vertices, const int m_Vertices); // Constructor

	/**
	 * @brief Fill out data in the graph raws
	 * 
	 */
	void addWeights(std::vector<T> graph_raws, int raw_number);

	/**
	 * @brief A utility function to find the vertex with minimum distance value, from
	 * the set of vertices not yet included in shortest path tree
	 * 
	 */
	T minDistance(std::vector<T> dist, std::vector<bool> sptSet);

	/**
	 * @brief A utility function to print the constructed distance array
	 * 
	 */
	void printSolution(std::vector<T> dist);

	/**
	 * @brief A utility function to print the graph
	 * 
	 */
	void printGraph();

	/**
	 * @brief Function that implements Dijkstra's single source shortest path algorithm
	 * for a graph represented using adjacency matrix representation
	 * 
	 */
	void dijkstra(int source);

	/**
	 * @brief Gets two variables of template type and compares them
	 * 
	 * @param f1 
	 * @param f2 
	 * @return true 
	 * @return false 
	 */
	bool templateCompare(T f1, T f2) const;
};
} // Dijkstra
} // forwardsearch

#endif // DIJKSTRA_HPP