// Driver program to test above function 
int main() 
{ 
	/* Description of the Grid- 
	1--> The cell is not blocked 
	0--> The cell is blocked */
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