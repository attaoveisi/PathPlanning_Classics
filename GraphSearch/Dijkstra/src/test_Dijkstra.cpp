#include "Dijkstra.hpp"
#include "Dijkstra.cpp"
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
	/*
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
	*/

	forwardsearch::Dijkstra::Graph<float> m_Graph(n_Vertices,n_Vertices);
	m_Graph.addWeights({ 0.0, 4.31, 0.0, 0.0, 0.0, 0.0, 0.0, 8.31, 0.1 }, 0);
	m_Graph.addWeights({ 4.31, 0.0, 8.31, 0.0, 0.0, 0.0, 0.0, 11.31, 0.12 }, 1);
	m_Graph.addWeights({ 0.0, 8.31, 0.0, 7.31, 0.0, 4.31, 0.0, 0.0, 2.23 }, 2);
	m_Graph.addWeights({ 0.0, 0.0, 7.31, 0.0, 9.31, 14.31, 0.0, 0.0, 0.98 }, 3);
	m_Graph.addWeights({ 0.0, 0.0, 0.0, 9.31, 0.0, 10.0, 0.0, 0.0, 0.65 }, 4);
	m_Graph.addWeights({ 0.0, 0.0, 4.31, 14.31, 10.0, 0.0, 2.31, 0.0, 0.33 }, 5);
	m_Graph.addWeights({ 0.0, 0.0, 0.0, 0.0, 0.0, 2.31, 0.0, 1.31, 6.87 }, 6);
	m_Graph.addWeights({ 8.31, 11.31, 0.0, 0.0, 0.0, 0.0, 1.31, 0.0, 7.52 }, 7);
	m_Graph.addWeights({ 0.0, 0.0, 2.31, 0.0, 0.0, 0.0, 6.31, 7.31, 0.11 }, 8);

	m_Graph.printGraph();

	int start_node = 0; // source
	m_Graph.dijkstra(start_node); 

	return 0; 
} 
