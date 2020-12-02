#ifndef A_STAR_HPP
#define A_STAR_HPP
  
/** 
 * @brief A C++ program for A* shortest path algorithm.
 * @brief The program is for adjacency matrix representation of the graph
   @author Atta Oveisi
   @date Dec 2020
 */

#include <limits> 
#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <deque>
#include <set>
#include <cfloat>
#include <cassert>
#include <stdio.h> 

namespace forwardsearch{
namespace A_Star{

class Graph{
private:

    const int m_Row;
    const int m_Col; 

	/**
	 * @brief Graph architechture 
	 * 
	 */
	std::vector<std::vector<int>> graph;

	/**
	 * @brief A structure to hold the neccesary parameters
	 * 
	 */
	struct cell 
	{ 
		/**
		 * @brief Construct a new cell stuct object
		 * 
		 * @param parent_i 
		 * @param parent_j 
		 * @param f 
		 * @param g 
		 * @param h 
		 */
		cell(int parent_i = -1, int parent_j = -1, double f = FLT_MAX, double g = FLT_MAX, double h = FLT_MAX):
		parent_i(parent_i), parent_j(parent_j), f(f), g(g), h(h) {}

		/**
		 * @brief Row and Column index of its parent
		 * that 0 <= i <= m_Row-1 & 0 <= j <= m_Col-1 
		 * 
		 */
		int parent_i, parent_j; 

		/**
		 * @brief f = g + h
		 * 
		 */
		double f, g, h; 
	}; 

	/**
	 * @brief Declare a 2D array of structure to hold the details of that cell 
	 * 
	 */
	std::vector<std::vector<cell>> cellDetails;

	/**
	 * @brief Create a closed list and initialise it to false which means that no cell has been included yet
	 * This closed list is implemented as a boolean 2D array 
	 * 
	 */
	std::deque<std::deque<bool>> closedList;
	 
    /**
     * @brief Reset the foundDest flag
     * 
     */
	bool foundDest{false}; 

public:

	/**
	 * @brief Fill out data in the graph raws
	 * 
	 */
	void addRows(std::vector<int> graph_raws, int raw_number);

	/**
     * @brief Creating a shortcut for pair
     * 
     */
    using Pair = std::pair<int,int>;

    /**
     * @brief Creating a shortcut for pair of double and pair
     * 
     */
    using pPair = std::pair<double, std::pair<int,int>>;

	/**
	 * @brief make the source and destination vertices fixed
	 * 
	 */
	const Pair src;
	const Pair dest;

	/**
	 * @brief Create an open list having information as 
	 * <f, <i, j>> where f = g + h, and i, j are the row and column index of that cell
	 * Note that 0 <= i <= m_Row-1 & 0 <= j <= m_Col-1 
	 */
	std::set<pPair> openList; 

	/**
	 * @brief Construct a new a_star object
	 * 
	 */
	Graph(const int row, const int col, const Pair src, const Pair dest):
	m_Row(row), m_Col(col), src(src), dest(dest)
	{
		//this->m_Row = row;
		//this->m_Col = col;
		for (int i = 0; i < row; i++){
		graph.push_back(std::vector<int>(col,0));
		}

		for (int i = 0; i < row; i++){
		closedList.push_back(std::deque<bool>(col,false));
		}

		/**
		 * @brief Declare a 2D array of structure to hold the details of that cell 
		 * 
		 */
		cell m_Cell;
		for (int i = 0; i < row; i++){
			cellDetails.push_back(std::vector<cell>(col,m_Cell));
		}
	}

	/**
	 * @brief A Utility Function to check whether given cell (row, col) 
	 * is a valid cell or not.
	 * 
	 * @param row 
	 * @param col 
	 * @return true if row number and column number is in range 
	 * @return false 
	 */
	bool isValid(int row, int col)
	{ 
		/**
		 * @brief Returns true if row number and column number is in range 
		 * 
		 */
		return (row >= 0) && (row < m_Row) && 
			(col >= 0) && (col < m_Col); 
	} 

	/**
	 * @brief A Utility Function to check whether the given cell is
	 * blocked or not
	 * 
	 * @param graph 
	 * @param row 
	 * @param col 
	 * @return true if the cell is not blocked else false
	 * @return false 
	 */
	bool isUnBlocked(std::vector<std::vector<int>> graph, int row, int col) 
	{ 
		if (graph.at(row).at(col) == 1) {
			return true; 
		}else{
			return false; 
		}
	} 

	/**
	 * @brief A Utility Function to check whether destination cell has been reached or not
	 * 
	 * @param row 
	 * @param col 
	 * @param dest 
	 * @return true 
	 * @return false 
	 */
	bool isDestination(int row, int col, Pair dest) 
	{ 
		if (row == dest.first && col == dest.second){
			return true; 
		}else{
			return false;
		}	 
	} 

	/**
	 * @brief A Utility Function to calculate the 'h' heuristics. 
	 * 
	 * @param row 
	 * @param col 
	 * @param dest 
	 * @return double 
	 */
	double calculateHValue(int row, int col, Pair dest); 

	/**
	 * @brief A Utility Function to trace the path from the source to destination 
	 * 
	 * @param cellDetails 
	 * @param dest 
	 */
	std::stack<Pair> tracePath(std::vector<std::vector<cell>> cellDetails, Pair dest); 

	/**
	 * @brief The main function to find the shortest path between
	 * a given source cell to a destination cell according
	 * to A* Search Algorithm 
	 * 
	 * @param src 
	 * @param dest 
	 */
	void aStarSearch();

	/**
	 * @brief A utility function that for checking the boundary functions
	 * 
	 */
	void graphCheck(std::vector<std::vector<int>> graph, Pair src, Pair dest){
		/**
		 * @brief If the source is out of range
		 * 
		 */
		if (isValid (src.first, src.second) == false) 
		{ 
			std::cout << "Source is invalid" << std::endl;
			return; 
		} 

		/**
		 * @brief If the destination is out of range 
		 * 
		 */
		if (isValid (dest.first, dest.second) == false) 
		{ 
			std::cout << "Destination is invalid" << std::endl;
			return; 
		} 

		/**
		 * @brief Either the source or the destination is blocked 
		 * 
		 */
		if (isUnBlocked(graph, src.first, src.second) == false || 
				isUnBlocked(graph, dest.first, dest.second) == false) 
		{ 
			std::cout << "Source or the destination is blocked" << std::endl;
			return; 
		} 

		/**
		 * @brief If the destination cell is the same as source cell 
		 * 
		 */
		if (isDestination(src.first, src.second, dest) == true) 
		{ 
			std::cout << "We are already at the destination" << std::endl;
			return; 
		} 
	}

	/**
     * @brief Initialize for the given source (src)
     * 
     */
	void initSrc(Pair src){
		int i = src.first;
		int j = src.second; 
		cellDetails.at(i).at(j).f = 0.0; 
		cellDetails.at(i).at(j).g = 0.0; 
		cellDetails.at(i).at(j).h = 0.0; 
		cellDetails.at(i).at(j).parent_i = i; 
		cellDetails.at(i).at(j).parent_j = j;
		openList.insert(std::make_pair(0.0, std::make_pair(i, j)));
	} 

	/**
	 * @brief Generating all the 8 successor of this cell 
	 * 
	 *   	 N.W  N N.E 
	 *			\ | / 
	 *          \ | / 
	 *		W----Cell----E 
	 *			/ | \ 
	 *		    / | \ 
	 *		  S.W S S.E
	 * 
	 */
	void generateSuccessor(int &m1_i, int &mr_i, int &m1_j, int &mr_j, const Pair dest, std::vector<std::vector<cell>> &cellDetails, double &gNew, double &hNew, double &fNew, const std::vector<std::vector<int>> graph, bool &foundDest);


	/**
	 * @brief Cell--> Popped Cell (i, j) 
	 *  ================================
 	 *	N --> North	 (i-1, j) 
	 *	S --> South	 (i+1, j) 
	 *	E --> East	 (i, j+1) 
	 *	W --> West		 (i, j-1) 
	 *	N.E--> North-East (i-1, j+1) 
	 *	N.W--> North-West (i-1, j-1) 
	 *	S.E--> South-East (i+1, j+1) 
	 * 	S.W--> South-West (i+1, j-1)
	 * =================================
	 * 
	 * @param i 
	 * @param j 
	 * @param dest 
	 * @param cellDetails 
	 * @param graph 
	 * @param foundDest 
	 */
	void propagateSuccessor(int &i, int &j, const Pair dest, std::vector<std::vector<cell>> &cellDetails, const std::vector<std::vector<int>> graph, bool &foundDest);

	/**
	 * @brief A utility function to print the graph
	 * 
	 */
	void printGraph();

	/**
	 * @brief Visualize the map
	 * 
	 */
	void visMap(std::stack<Graph::Pair> Path);

};

} // A_STAR
} // forwardsearch

#endif // A_STAR_HPP
