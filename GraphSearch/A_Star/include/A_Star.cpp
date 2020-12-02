#include "A_Star.hpp"

namespace forwardsearch{
namespace A_Star{

double Graph::calculateHValue(int m_Row, int m_Col, Pair dest) 
{ 
    /**
     * @brief Return using the distance formula 
     * 
     */
    return ((double)sqrt ((m_Row-dest.first)*(m_Row-dest.first) 
                        + (m_Col-dest.second)*(m_Col-dest.second))); 
} 

void Graph::tracePath(std::vector<std::vector<cell>> cellDetails, Pair dest) 
{ 
    std::cout << "The path is:" << std::endl;

    int m_Row = dest.first; 
    int m_Col = dest.second; 

    std::stack<Pair> Path; 

    while (!(cellDetails.at(m_Row).at(m_Col).parent_i == m_Row 
            && cellDetails.at(m_Row).at(m_Col).parent_j == m_Col )) 
    { 
        Path.push(std::make_pair(m_Row, m_Col)); 
        m_Row = cellDetails.at(m_Row).at(m_Col).parent_i; 
        m_Col = cellDetails.at(m_Row).at(m_Col).parent_j; 
    } 

    Path.push(std::make_pair(m_Row, m_Col)); 
    while (!Path.empty()) 
    { 
        std::pair<int,int> p = Path.top(); 
        Path.pop(); 
        std::cout << " -> " << p.first << " , " << p.second << std::endl;
    } 
} 

void Graph::aStarSearch(std::vector<std::vector<int>> graph, Pair src, Pair dest) 
{ 
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


	/* 
	Create an open list having information as- 
	<f, <i, j>> 
	where f = g + h, 
	and i, j are the m_Row and m_Column index of that cell 
	Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
	This open list is implenented as a set of pair of pair.*/
	set<pPair> openList; 

	// Put the starting cell on the open list and set its 
	// 'f' as 0 
	openList.insert(make_pair (0.0, make_pair (i, j))); 

	// We set this boolean value as false as initially 
	// the destination is not reached. 
	bool foundDest = false; 

	while (!openList.empty()) 
	{ 
		pPair p = *openList.begin(); 

		// Remove this vertex from the open list 
		openList.erase(openList.begin()); 

		// Add this vertex to the closed list 
		i = p.second.first; 
		j = p.second.second; 
		closedList[i][j] = true; 
	
	/* 
		Generating all the 8 successor of this cell 

			N.W N N.E 
			\ | / 
			\ | / 
			W----Cell----E 
				/ | \ 
			/ | \ 
			S.W S S.E 

		Cell-->Popped Cell (i, j) 
		N --> North	 (i-1, j) 
		S --> South	 (i+1, j) 
		E --> East	 (i, j+1) 
		W --> West		 (i, j-1) 
		N.E--> North-East (i-1, j+1) 
		N.W--> North-West (i-1, j-1) 
		S.E--> South-East (i+1, j+1) 
		S.W--> South-West (i+1, j-1)*/

		// To store the 'g', 'h' and 'f' of the 8 successors 
		double gNew, hNew, fNew; 

		//----------- 1st Successor (North) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid(i-1, j) == true) 
		{ 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i-1, j, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i-1][j].parent_i = i; 
				cellDetails[i-1][j].parent_j = j; 
				printf ("The destination cell is found\n"); 
				tracePath (cellDetails, dest); 
				foundDest = true; 
				return; 
			} 
			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i-1][j] == false && 
					isUnBlocked(graph, i-1, j) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.0; 
				hNew = calculateHValue (i-1, j, dest); 
				fNew = gNew + hNew; 

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//			 OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i-1][j].f == FLT_MAX || 
						cellDetails[i-1][j].f > fNew) 
				{ 
					openList.insert( make_pair(fNew, 
											make_pair(i-1, j))); 

					// Update the details of this cell 
					cellDetails[i-1][j].f = fNew; 
					cellDetails[i-1][j].g = gNew; 
					cellDetails[i-1][j].h = hNew; 
					cellDetails[i-1][j].parent_i = i; 
					cellDetails[i-1][j].parent_j = j; 
				} 
			} 
		} 

		//----------- 2nd Successor (South) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid(i+1, j) == true) 
		{ 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i+1, j, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i+1][j].parent_i = i; 
				cellDetails[i+1][j].parent_j = j; 
				printf("The destination cell is found\n"); 
				tracePath(cellDetails, dest); 
				foundDest = true; 
				return; 
			} 
			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i+1][j] == false && 
					isUnBlocked(graph, i+1, j) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.0; 
				hNew = calculateHValue(i+1, j, dest); 
				fNew = gNew + hNew; 

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//			 OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i+1][j].f == FLT_MAX || 
						cellDetails[i+1][j].f > fNew) 
				{ 
					openList.insert( make_pair (fNew, make_pair (i+1, j))); 
					// Update the details of this cell 
					cellDetails[i+1][j].f = fNew; 
					cellDetails[i+1][j].g = gNew; 
					cellDetails[i+1][j].h = hNew; 
					cellDetails[i+1][j].parent_i = i; 
					cellDetails[i+1][j].parent_j = j; 
				} 
			} 
		} 

		//----------- 3rd Successor (East) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid (i, j+1) == true) 
		{ 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i, j+1, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i][j+1].parent_i = i; 
				cellDetails[i][j+1].parent_j = j; 
				printf("The destination cell is found\n"); 
				tracePath(cellDetails, dest); 
				foundDest = true; 
				return; 
			} 

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i][j+1] == false && 
					isUnBlocked (graph, i, j+1) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.0; 
				hNew = calculateHValue (i, j+1, dest); 
				fNew = gNew + hNew; 

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//			 OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i][j+1].f == FLT_MAX || 
						cellDetails[i][j+1].f > fNew) 
				{ 
					openList.insert( make_pair(fNew, 
										make_pair (i, j+1))); 

					// Update the details of this cell 
					cellDetails[i][j+1].f = fNew; 
					cellDetails[i][j+1].g = gNew; 
					cellDetails[i][j+1].h = hNew; 
					cellDetails[i][j+1].parent_i = i; 
					cellDetails[i][j+1].parent_j = j; 
				} 
			} 
		} 

		//----------- 4th Successor (West) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid(i, j-1) == true) 
		{ 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i, j-1, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i][j-1].parent_i = i; 
				cellDetails[i][j-1].parent_j = j; 
				printf("The destination cell is found\n"); 
				tracePath(cellDetails, dest); 
				foundDest = true; 
				return; 
			} 

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i][j-1] == false && 
					isUnBlocked(graph, i, j-1) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.0; 
				hNew = calculateHValue(i, j-1, dest); 
				fNew = gNew + hNew; 

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//			 OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i][j-1].f == FLT_MAX || 
						cellDetails[i][j-1].f > fNew) 
				{ 
					openList.insert( make_pair (fNew, 
										make_pair (i, j-1))); 

					// Update the details of this cell 
					cellDetails[i][j-1].f = fNew; 
					cellDetails[i][j-1].g = gNew; 
					cellDetails[i][j-1].h = hNew; 
					cellDetails[i][j-1].parent_i = i; 
					cellDetails[i][j-1].parent_j = j; 
				} 
			} 
		} 

		//----------- 5th Successor (North-East) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid(i-1, j+1) == true) 
		{ 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i-1, j+1, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i-1][j+1].parent_i = i; 
				cellDetails[i-1][j+1].parent_j = j; 
				printf ("The destination cell is found\n"); 
				tracePath (cellDetails, dest); 
				foundDest = true; 
				return; 
			} 

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i-1][j+1] == false && 
					isUnBlocked(graph, i-1, j+1) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.414; 
				hNew = calculateHValue(i-1, j+1, dest); 
				fNew = gNew + hNew; 

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//			 OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i-1][j+1].f == FLT_MAX || 
						cellDetails[i-1][j+1].f > fNew) 
				{ 
					openList.insert( make_pair (fNew, 
									make_pair(i-1, j+1))); 

					// Update the details of this cell 
					cellDetails[i-1][j+1].f = fNew; 
					cellDetails[i-1][j+1].g = gNew; 
					cellDetails[i-1][j+1].h = hNew; 
					cellDetails[i-1][j+1].parent_i = i; 
					cellDetails[i-1][j+1].parent_j = j; 
				} 
			} 
		} 

		//----------- 6th Successor (North-West) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid (i-1, j-1) == true) 
		{ 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination (i-1, j-1, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i-1][j-1].parent_i = i; 
				cellDetails[i-1][j-1].parent_j = j; 
				printf ("The destination cell is found\n"); 
				tracePath (cellDetails, dest); 
				foundDest = true; 
				return; 
			} 

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i-1][j-1] == false && 
					isUnBlocked(graph, i-1, j-1) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.414; 
				hNew = calculateHValue(i-1, j-1, dest); 
				fNew = gNew + hNew; 

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//			 OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i-1][j-1].f == FLT_MAX || 
						cellDetails[i-1][j-1].f > fNew) 
				{ 
					openList.insert( make_pair (fNew, make_pair (i-1, j-1))); 
					// Update the details of this cell 
					cellDetails[i-1][j-1].f = fNew; 
					cellDetails[i-1][j-1].g = gNew; 
					cellDetails[i-1][j-1].h = hNew; 
					cellDetails[i-1][j-1].parent_i = i; 
					cellDetails[i-1][j-1].parent_j = j; 
				} 
			} 
		} 

		//----------- 7th Successor (South-East) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid(i+1, j+1) == true) 
		{ 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i+1, j+1, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i+1][j+1].parent_i = i; 
				cellDetails[i+1][j+1].parent_j = j; 
				printf ("The destination cell is found\n"); 
				tracePath (cellDetails, dest); 
				foundDest = true; 
				return; 
			} 

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i+1][j+1] == false && 
					isUnBlocked(graph, i+1, j+1) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.414; 
				hNew = calculateHValue(i+1, j+1, dest); 
				fNew = gNew + hNew; 

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//			 OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i+1][j+1].f == FLT_MAX || 
						cellDetails[i+1][j+1].f > fNew) 
				{ 
					openList.insert(make_pair(fNew, 
										make_pair (i+1, j+1))); 

					// Update the details of this cell 
					cellDetails[i+1][j+1].f = fNew; 
					cellDetails[i+1][j+1].g = gNew; 
					cellDetails[i+1][j+1].h = hNew; 
					cellDetails[i+1][j+1].parent_i = i; 
					cellDetails[i+1][j+1].parent_j = j; 
				} 
			} 
		} 

		//----------- 8th Successor (South-West) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid (i+1, j-1) == true) 
		{ 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i+1, j-1, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i+1][j-1].parent_i = i; 
				cellDetails[i+1][j-1].parent_j = j; 
				printf("The destination cell is found\n"); 
				tracePath(cellDetails, dest); 
				foundDest = true; 
				return; 
			} 

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i+1][j-1] == false && 
					isUnBlocked(graph, i+1, j-1) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.414; 
				hNew = calculateHValue(i+1, j-1, dest); 
				fNew = gNew + hNew; 

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//			 OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i+1][j-1].f == FLT_MAX || 
						cellDetails[i+1][j-1].f > fNew) 
				{ 
					openList.insert(make_pair(fNew, 
										make_pair(i+1, j-1))); 

					// Update the details of this cell 
					cellDetails[i+1][j-1].f = fNew; 
					cellDetails[i+1][j-1].g = gNew; 
					cellDetails[i+1][j-1].h = hNew; 
					cellDetails[i+1][j-1].parent_i = i; 
					cellDetails[i+1][j-1].parent_j = j; 
				} 
			} 
		} 
	} 

	// When the destination cell is not found and the open 
	// list is empty, then we conclude that we failed to 
	// reach the destiantion cell. This may happen when the 
	// there is no way to destination cell (due to blockages) 
	if (foundDest == false) 
		printf("Failed to find the Destination Cell\n"); 

} 


} // Dijkstra
} // forwardsearch