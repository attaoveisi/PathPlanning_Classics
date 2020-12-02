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

namespace forwardsearch{
namespace A_Star{

class Graph{
private:

    const int ROW;
    const int COL; 

    /**
     * @brief Creating a shortcut for pair
     * 
     */
    using Pair = std::pair<int,int>;

// Creating a shortcut for pair<int, pair<int, int>> type
    /**
     * @brief Creating a shortcut for pair of double and pair
     * 
     */
    using pPair = std::pair<double, std::pair<int,int>>;

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
		 * that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
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

public:
	/**
	 * @brief Construct a new a_star object
	 * 
	 */
	Graph(const int m_Row, const int m_Col):
	ROW(m_Row), COL(m_Col)
	{
		//this->ROW = m_Row;
		//this->COL = m_Col;
		for (int i = 0; i < m_Row; i++){
		graph.push_back(std::vector<int>(m_Col,0));
		}

		for (int i = 0; i < m_Row; i++){
		closedList.push_back(std::deque<bool>(m_Col,false));
		}

		/**
		 * @brief Initialising the parameters of the starting node 
		 * 
		 */
		cell m_Cell;
		for (int i = 0; i < m_Row; i++){
			cellDetails.push_back(std::vector<cell>(m_Col,m_Cell));
		}
	}

	/**
	 * @brief A Utility Function to check whether given cell (m_Row, m_Col) 
	 * is a valid cell or not.
	 * 
	 * @param m_Row 
	 * @param m_Col 
	 * @return true if m_Row number and m_Column number is in range 
	 * @return false 
	 */
	bool isValid(int m_Row, int m_Col)
	{ 
		/**
		 * @brief Returns true if row number and column number is in range 
		 * 
		 */
		return (m_Row >= 0) && (m_Row < ROW) && 
			(m_Col >= 0) && (m_Col < COL); 
	} 

	/**
	 * @brief A Utility Function to check whether the given cell is
	 * blocked or not
	 * 
	 * @param graph 
	 * @param m_Row 
	 * @param m_Col 
	 * @return true if the cell is not blocked else false
	 * @return false 
	 */
	bool isUnBlocked(std::vector<std::vector<int>> graph, int m_Row, int m_Col) 
	{ 
		if (graph.at(m_Row).at(m_Col) == 1) {
			return true; 
		}else{
			return false; 
		}
	} 

	/**
	 * @brief A Utility Function to check whether destination cell has been reached or not
	 * 
	 * @param m_Row 
	 * @param m_Col 
	 * @param dest 
	 * @return true 
	 * @return false 
	 */
	bool isDestination(int m_Row, int m_Col, Pair dest) 
	{ 
		if (m_Row == dest.first && m_Col == dest.second){
			return true; 
		}else{
			return false;
		}	 
	} 

	/**
	 * @brief A Utility Function to calculate the 'h' heuristics. 
	 * 
	 * @param m_Row 
	 * @param m_Col 
	 * @param dest 
	 * @return double 
	 */
	double calculateHValue(int m_Row, int m_Col, Pair dest); 

	/**
	 * @brief A Utility Function to trace the path from the source to destination 
	 * 
	 * @param cellDetails 
	 * @param dest 
	 */
	void tracePath(std::vector<std::vector<cell>> cellDetails, Pair dest); 

	/**
	 * @brief The main function to find the shortest path between
	 * a given source cell to a destination cell according
	 * to A* Search Algorithm 
	 * 
	 * @param graph 
	 * @param src 
	 * @param dest 
	 */
	void aStarSearch(std::vector<std::vector<int>> graph, Pair src, Pair dest);

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
};

} // A_STAR
} // forwardsearch

#endif // A_STAR_HPP
