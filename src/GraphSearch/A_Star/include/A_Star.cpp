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

std::stack<Graph::Pair> Graph::tracePath(std::vector<std::vector<cell>> cellDetails, Pair dest) 
{ 
    std::cout << "The path is:" << std::endl;

    int row = dest.first; 
    int col = dest.second; 
    
    std::stack<Pair> Path; 

    while (!(cellDetails.at(row).at(col).parent_i == row  && cellDetails.at(row).at(col).parent_j == col )) 
    { 
        Path.push(std::make_pair(row, col));
        int temp_row = cellDetails.at(row).at(col).parent_i;
        int temp_col = cellDetails.at(row).at(col).parent_j;
        row = temp_row;
        col = temp_col;
    } 

    Path.push(std::make_pair(row, col));

    std::stack<Pair> Path_dummy = Path;

    while (!Path_dummy.empty()) 
    { 
        std::pair<int,int> p = Path_dummy.top(); 
        Path_dummy.pop(); 
        std::cout << " -> " << p.first << " , " << p.second << std::endl;
    } 
    return Path;
} 

void Graph::aStarSearch()
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

    void Graph::propagateSuccessor(int &i, int &j, const Pair dest, std::vector<std::vector<cell>> &cellDetails, const std::vector<std::vector<int>> graph, bool &foundDest){
        /**
         * @brief To store the 'g', 'h' and 'f' of the 8 successors
         *
         */
        double gNew, hNew, fNew;

        int ml_i = i;
        int ml_j = j;
        int mr_i = i;
        int mr_j = j;

        /**
         * @brief Cycle around all successors
         *
         */
        /**
         * @brief 1st Successor (North)
         */
        ml_i -= 1;
        generateSuccessor(ml_i, ml_j, mr_i, mr_j, dest, cellDetails, gNew, hNew, fNew, graph, foundDest);
        ml_i += 1;

        /**
         * @brief 2nd Successor (South)
         */
        ml_i += 1;
        generateSuccessor(ml_i, ml_j, mr_i, mr_j, dest, cellDetails, gNew, hNew, fNew, graph, foundDest);
        ml_i -= 1;

        /**
         * @brief 3rd Successor (East)
         */
        ml_j += 1;
        generateSuccessor(ml_i, ml_j, mr_i, mr_j, dest, cellDetails, gNew, hNew, fNew, graph, foundDest);
        ml_j -= 1;

        /**
         * @brief 4th Successor (West)
         */
        ml_j -= 1;
        generateSuccessor(ml_i, ml_j, mr_i, mr_j, dest, cellDetails, gNew, hNew, fNew, graph, foundDest);
        ml_j += 1;

        /**
         * @brief 5th Successor (North-East)
         */
        ml_i -= 1;
        ml_j += 1;
        generateSuccessor(ml_i, ml_j, mr_i, mr_j, dest, cellDetails, gNew, hNew, fNew, graph, foundDest);
        ml_i += 1;
        ml_j -= 1;

        /**
         * @brief 6th Successor (North-West)
         */
        ml_i -= 1;
        ml_j -= 1;
        generateSuccessor(ml_i, ml_j, mr_i, mr_j, dest, cellDetails, gNew, hNew, fNew, graph, foundDest);
        ml_i += 1;
        ml_j += 1;

        /**
         * @brief 7th Successor (South-East)
         */
        ml_i += 1;
        ml_j += 1;
        generateSuccessor(ml_i, ml_j, mr_i, mr_j, dest, cellDetails, gNew, hNew, fNew, graph, foundDest);
        ml_i -= 1;
        ml_j -= 1;

        /**
         * @brief 8th Successor (South-West)
         */
        ml_i += 1;
        ml_j -= 1;
        generateSuccessor(ml_i, ml_j, mr_i, mr_j, dest, cellDetails, gNew, hNew, fNew, graph, foundDest);
        ml_i -= 1;
        ml_j += 1;
    }

void Graph::generateSuccessor(int &ml_i, int &ml_j, int &mr_i, int &mr_j, const Pair dest, std::vector<std::vector<cell>> &cellDetails, double &gNew, double &hNew, double &fNew, const std::vector<std::vector<int>> graph, bool &foundDest){
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
            //assert((ml_i <= 0 && ml_i >= m_Row) && "Illegal row size");
            //assert((ml_j <= 0 && ml_j >= m_Col) && "Illegal column size");
            std::cout << "The destination cell is found" << std::endl;
            finalPath = tracePath(cellDetails, dest);
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

void Graph::addRows(std::vector<int> graph_raws,int raw_number){
    for (int i = 0; i < graph_raws.size(); i++){
        graph.at(raw_number).at(i) = graph_raws.at(i);
    }
}

void Graph::printGraph(){
	std::cout << "The graph structure is given as: " << std::endl;
	for (int i = 0; i<m_Row; i++){
		for(int j = 0; j<m_Col; j++){
			std::cout << graph.at(i).at(j) << " ";
		}
		std::cout << std::endl;
	}
}

void Graph::visMap(std::stack<Graph::Pair> Path){
    int pathLength = Path.size();
    for (int i = 0; i < m_Row; i++) {
        std::pair<int,int> pTop = Path.top();
        for (int j = 0; j < m_Col; j++) {
            if (graph.at(i).at(j)) {
                putchar(0xdb);
            } else {
                int b = 0;
                for (int k = 0; k < pathLength; k++) {
                    if (cellDetails.at(i).at(j).parent_i == pTop.first && cellDetails.at(i).at(j).parent_j == pTop.second){
                        ++b;
                    }
                }
                if(b) {
                    putchar('x');
                } else {
                    putchar('.');
                }
                Path.pop(); 
            }
        }
        putchar('\n');
    }
}

} // A_Star
} // forwardsearch