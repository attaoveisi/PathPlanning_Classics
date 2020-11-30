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
	forwardsearch::Dijkstra::Graph<int> m_Graph(n_Vertices,n_Vertices);
	m_Graph.addWeights({ 0, 4, 0, 0, 0, 0, 0, 8, 0 }, 0);
	m_Graph.addWeights({ 4, 0, 8, 0, 0, 0, 0, 11, 0 }, 1);
	m_Graph.addWeights({ 0, 8, 0, 7, 0, 4, 0, 0, 2 }, 2);
	m_Graph.addWeights({ 0, 0, 7, 0, 9, 14, 0, 0, 0 }, 3);
	m_Graph.addWeights({ 0, 0, 0, 9, 0, 10, 0, 0, 0 }, 4);
	m_Graph.addWeights({ 0, 0, 4, 14, 10, 0, 2, 0, 0 }, 5);
	m_Graph.addWeights({ 0, 0, 0, 0, 0, 2, 0, 1, 6 }, 6);
	m_Graph.addWeights({ 8, 11, 0, 0, 0, 0, 1, 0, 7 }, 7);
	m_Graph.addWeights({ 0, 0, 2, 0, 0, 0, 6, 7, 0 }, 8);

	m_Graph.printGraph();

	int start_node = 0; // source
	m_Graph.dijkstra(start_node); 

	return 0; 
} 
