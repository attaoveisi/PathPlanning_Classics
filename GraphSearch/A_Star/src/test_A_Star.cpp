#include "A_Star.hpp"

/**
 * @brief Driver program to test A*-graph search algorithm
 * 
 * @return 0 if ends 
 */
 
int main() 
{ 
	/**
	 * @brief Graph dimension
	 * 
	 */
	int n_Row = 9;
	int n_Col = 10;

	// Source is the left-most bottom-most corner 
	forwardsearch::A_Star::Graph::Pair src = std::make_pair(8, 0); 

	// Destination is the left-most top-most corner 
	forwardsearch::A_Star::Graph::Pair dest = std::make_pair(0, 0); 

	/**
	 * @brief Description of the Grid- 
	 * 1--> The cell is not blocked
	 * 0--> The cell is blocked
	 * 
	 */
	forwardsearch::A_Star::Graph m_Graph(n_Row,n_Col);

	m_Graph.addRows({ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, 0);
	m_Graph.addRows({ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 }, 1);
	m_Graph.addRows({ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 }, 2);
	m_Graph.addRows({ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 }, 3);
	m_Graph.addRows({ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 }, 4);
	m_Graph.addRows({ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 }, 5);
	m_Graph.addRows({ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 }, 6);
	m_Graph.addRows({ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, 7);
	m_Graph.addRows({ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }, 8);

	/**
	 * @brief prove that the entry is correct
	 * 
	 */
	m_Graph.printGraph();
	

	m_Graph.aStarSearch(src, dest); 

	return(0); 
}