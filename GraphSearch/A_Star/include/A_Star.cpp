#include "A_Star.hpp"

namespace forwardsearch{
namespace A_Star{

double Graph::calculateHValue(int row, int col, Pair dest) 
{ 
    /**
     * @brief Return using the distance formula 
     * 
     */
    return ((double)sqrt ((row-dest.first)*(row-dest.first) 
                        + (col-dest.second)*(col-dest.second))); 
} 

void Graph::tracePath(std::vector<std::vector<cell>> cellDetails, Pair dest) 
{ 
    std::cout << "The path is:" << std::endl;

    int row = dest.first; 
    int col = dest.second; 

    std::stack<Pair> Path; 

    while (!(cellDetails.at(row).at(col).parent_i == row 
            && cellDetails.at(row).at(col).parent_j == col )) 
    { 
        Path.push(std::make_pair(row, col)); 
        row = cellDetails.at(row).at(col).parent_i; 
        col = cellDetails.at(row).at(col).parent_j; 
    } 

    Path.push(std::make_pair(row, col)); 
    while (!Path.empty()) 
    { 
        std::pair<int,int> p = Path.top(); 
        Path.pop(); 
        std::cout << " -> " << p.first << " , " << p.second << std::endl;
    } 
} 

void Graph::aStarSearch(Pair src, Pair dest) 
{ 
    /**
     * @brief Check for boundary conditions
     * 
     */
    graphCheck(graph, src, dest);

    /**
     * @brief Construct a new init Src object
     * 
     */
    initSrc(src);

	while (!openList.empty()) 
	{ 
		pPair p = *openList.begin(); 

		/**
		 * @brief  Remove this vertex from the open list
		 * 
		 */
		openList.erase(openList.begin()); 

		/**
		 * @brief add the vertex to the closed list
		 * 
		 */
		int i = p.second.first; 
		int j = p.second.second; 
		closedList.at(i).at(j) = true; 
	
        propagateSuccessor(i, j, dest, cellDetails, graph, foundDest);		
	} 

    /**
     * @brief When the destination cell is not found and the open 
     * list is empty, then we conclude that we failed to 
     * reach the destiantion cell. This may happen when the 
     * there is no way to destination cell (due to blockages)
     * 
     */
	if (foundDest == false) {
        std::cout << "Failed to find the Destination Cell" << std::endl; 
    }
} 

void Graph::generateSuccessor(int ml_i, int mr_i, int ml_j, int mr_j, Pair dest, std::vector<std::vector<cell>> &cellDetails, double &gNew, double &hNew, double &fNew, std::vector<std::vector<int>> graph, bool &foundDest){
    /**
     * @brief Construct a new if object
     * Only process this cell if this is a valid one 
     */
    if (isValid(ml_i, ml_j) == true) 
    { 
        /**
         * @brief If the destination cell is the same as the current successor 
         * If the successor is already on the closed list or if it is blocked, then ignore it. Else do the following
         * 
         */
        if (isDestination(ml_i, ml_j, dest) == true) 
        { 
            /**
             * @brief Set the Parent of the destination cell
             * 
             */
            cellDetails.at(ml_i).at(ml_j).parent_i = mr_i; 
            cellDetails.at(ml_i).at(ml_j).parent_j = mr_j; 
            std::cout << "The destination cell is found" << std::endl;
            tracePath (cellDetails, dest); 
            foundDest = true; 
            return; 
        }else if (closedList.at(ml_i).at(ml_j) == false && isUnBlocked(graph, ml_i, ml_j) == true) 
        { 
            gNew = cellDetails.at(mr_i).at(mr_j).g + 1.0; 
            hNew = calculateHValue(ml_i, ml_j, dest); 
            fNew = gNew + hNew; 

            /**
             * @brief If it isn’t on the open list, add it to the open list. Make the current square 
             * the parent of this square. Record the f, g, and h costs of the square cell 
             * OR
             * If it is on the open list already, check to see if this path to that square is better, 
             * using 'f' cost as the measure. 
             * 
             */
            if (cellDetails.at(ml_i).at(ml_j).f == FLT_MAX || cellDetails.at(ml_i).at(ml_j).f > fNew) 
            { 
                openList.insert(std::make_pair(fNew, std::make_pair(ml_i, ml_j))); 

                /**
                 * @brief Update the details of this cell 
                 * 
                 */
                cellDetails.at(ml_i).at(ml_j).f = fNew; 
                cellDetails.at(ml_i).at(ml_j).g = gNew; 
                cellDetails.at(ml_i).at(ml_j).h = hNew; 
                cellDetails.at(ml_i).at(ml_j).parent_i = mr_i; 
                cellDetails.at(ml_i).at(ml_j).parent_j = mr_j; 
            } 
        } 
    } 
}

void Graph::propagateSuccessor(int i, int j, Pair dest, std::vector<std::vector<cell>> &cellDetails, std::vector<std::vector<int>> graph, bool &foundDest){
    /**
     * @brief To store the 'g', 'h' and 'f' of the 8 successors 
     * 
     */
    double gNew, hNew, fNew; 

    /**
     * @brief Cycle around all successors 
     * 
     */
    //----------- 1st Successor (North) ------------ 
    generateSuccessor(i-1, j, i, j, dest, cellDetails, gNew, hNew, fNew, graph, foundDest);
    
    //----------- 2nd Successor (South) ------------
    generateSuccessor(i+1, j, i, j, dest, cellDetails, gNew, hNew, fNew, graph, foundDest); 

    //----------- 3rd Successor (East) ------------ 
    generateSuccessor(i, j+1, i, j, dest, cellDetails, gNew, hNew, fNew, graph, foundDest); 

    //----------- 4th Successor (West) ------------ 
    generateSuccessor(i, j-1, i, j, dest, cellDetails, gNew, hNew, fNew, graph, foundDest); 

    //----------- 5th Successor (North-East) ------------ 
    generateSuccessor(i-1, j+1, i, j, dest, cellDetails, gNew, hNew, fNew, graph, foundDest); 
    
    //----------- 6th Successor (North-West) ------------ 
    generateSuccessor(i-1, j-1, i, j, dest, cellDetails, gNew, hNew, fNew, graph, foundDest); 

    //----------- 7th Successor (South-East) ------------ 
    generateSuccessor(i+1, j+1, i, j, dest, cellDetails, gNew, hNew, fNew, graph, foundDest); 

    //----------- 8th Successor (South-West) ------------ 
    generateSuccessor(i+1, j-1, i, j, dest, cellDetails, gNew, hNew, fNew, graph, foundDest);
}

void Graph::addRows(std::vector<int> graph_raws,int raw_number){
    for (int i = 0; i < graph_raws.size(); i++){
        graph.at(raw_number).at(i) = graph_raws.at(i);
    }
}

} // Dijkstra
} // forwardsearch