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

	/**
	 * @brief Description of the Grid- 
	 * 1--> The cell is not blocked
	 * 0--> The cell is blocked
	 * 
	 */
	forwardsearch::A_Star::Graph m_Graph(n_Row,n_Col);

	int grid[ROW][COL] = 
	{ 
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, 
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 }, 
		{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 }, 
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 }, 
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 }, 
		{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 }, 
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 }, 
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, 
		{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } 
	}; 

	// Source is the left-most bottom-most corner 
	Pair src = make_pair(8, 0); 

	// Destination is the left-most top-most corner 
	Pair dest = make_pair(0, 0); 

	aStarSearch(grid, src, dest); 

	return(0); 
}