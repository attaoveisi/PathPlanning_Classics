#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

// A C++ program for Dijkstra's single source shortest path algorithm. 
// The program is for adjacency matrix representation of the graph 

#include <limits.h> 
#include <stdio.h> 

// Dijkstra
class Graph{
public:
	/**
	 * @brief A utility function to find the vertex with minimum distance value, from
	 * the set of vertices not yet included in shortest path tree
	 */
	int minDistance(int dist[], bool sptSet[]);

	/**
	 * @brief A utility function to print the constructed distance array
	 */
	void Graph::printSolution(int dist[]);

	/**
	 * @brief Function that implements Dijkstra's single source shortest path algorithm
	 * for a graph represented using adjacency matrix representation
	 */
	void dijkstra(int graph[n_Vertices][n_Vertices], int src) 

private:
	/**
	 * @brief number of vertices for DFS in the graph
	 */
	int n_Vertices;
}

#endif // DIJKSTRA_HPP