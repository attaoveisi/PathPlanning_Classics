/// @brief Program to print BFS traversal from a given 
/// @brief source vertex. BFS(int s) traverses vertices 
/// @brief reachable from s. 
#include "BFS.hpp"

/// @brief Driver program to test methods of graph class 
int main() 
{ 
	/// @brief Create a graph given in the above diagram 
	int nVertices = 5;
	Graph m_Graph(nVertices); 
	m_Graph.addEdge(0, 1); 
	m_Graph.addEdge(0, 2); 
	m_Graph.addEdge(1, 2); 
	m_Graph.addEdge(2, 0); 
	m_Graph.addEdge(2, 3); 
	m_Graph.addEdge(3, 3); 
	m_Graph.addEdge(3, 4); 
	m_Graph.addEdge(4, 0);

	int start_v = 2;

	cout << "Following is Breadth First Traversal "
		 << "(starting from vertex " << start_v << ")" << endl; 
	m_Graph.BFS(start_v); 

	return 0; 
} 

