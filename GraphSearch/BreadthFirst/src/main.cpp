/// @brief Program to print BFS traversal from a given 
/// @brief source vertex. BFS(int s) traverses vertices 
/// @brief reachable from s. 
#include "BFS.hpp"

/// @brief Driver program to test methods of graph class 
int main() 
{ 
	/// @brief Create a graph given in the above diagram 
	Graph g(5); 
	g.addEdge(0, 1); 
	g.addEdge(0, 2); 
	g.addEdge(1, 2); 
	g.addEdge(2, 0); 
	g.addEdge(2, 3); 
	g.addEdge(3, 3); 
	g.addEdge(3, 4); 
	g.addEdge(4, 0);

	int start_v = 2;

	cout << "Following is Breadth First Traversal "
		 << "(starting from vertex " << start_v << ")" << endl; 
	g.BFS(start_v); 

	return 0; 
} 

