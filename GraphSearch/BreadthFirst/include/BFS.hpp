#ifndef BFS_HPP
#define BFS_HPP

#include<iostream> 
#include <list> 

using namespace std; 

/// @brief This class represents a directed graph using 
/// @brief adjacency list representation 
class Graph 
{ 
private:
	/// @param Vertices private parameter for No. of vertices 
	int Vertices; 

	/// @brief Pointer to an array containing adjacency lists 
	list<int> *adjacent; 
public: 
	/// @brief Constructor for accessing the private ... 
	/// @brief variable Vertices and initialization of adjacent list
	/// @param Vertices graph size (number of vertices)
	Graph(int Vertices); 


	/// @brief function to add an edge to the graph, namely adjacent object 
	/// @param v node v
	/// @param w adjacent node to v
	void addEdge(int v, int w); 

	/// @brief prints BFS traversal from a given source s 
	void BFS(int s); 
}; 


#endif // BFS_HPP