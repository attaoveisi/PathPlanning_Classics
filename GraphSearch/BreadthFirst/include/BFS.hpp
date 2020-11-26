#ifndef BFS_HPP
#define BFS_HPP

/** 
 * @brief Program to print BFS traversal from a given 
 *  @brief source vertex. BFS(int s) traverses vertices
 * @brief Detailed description follows here.

    
    @author Atta Oveisi
    @date Nov 2020
 */


#include<iostream> 
#include <list> 

using namespace std; 

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
	 * @brief Pointer to an array containing adjacency lists
	 */
	list<int> *adjacent; 

public: 

	/** 
	 * @brief Constructor for accessing the private ... 
	 * @brief variable Vertices and initialization of adjacent list
	 * @param Vertices graph size (number of vertices)
	 */
	Graph(int Vertices);
	~Graph(); 

	/** 
	 * @brief function to add an edge to the graph, namely adjacent object
	 * @param v: node v
	 * @param w: adjacent node to v
	 */
	void addEdge(int v, int w); 

	/** 
	 * @brief prints BFS traversal from a given source s 
	 */
	void BFS(int s); 
}; 


#endif // BFS_HPP