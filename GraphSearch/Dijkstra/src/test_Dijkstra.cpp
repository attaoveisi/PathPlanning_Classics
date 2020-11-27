#include "Dijkstra.hpp"
/**
* @brief Program to print Dijkstra traversal from a given 
* (single) source vertex. 
*/
int main() 
{ 
	int n_Vertices = 9;
	/**
	 * @brief Let us create the example graph discussed above
	 */ 
	forwardsearch::Dijkstra::Graph m_graph(n_Vertices,n_Vertices);

	m_Graph.dijkstra(m_Graph, 0); 

	return 0; 
} 
