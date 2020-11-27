#include "Dijkstra.hpp"

int Graph::minDistance(int dist[], bool sptSet[]) 
{ 
	// Initialize min value 
	int min = INT_MAX, min_index; 

	for (int v = 0; v < n_Vertices; v++) 
		if (sptSet[v] == false && dist[v] <= min) 
			min = dist[v], min_index = v; 

	return min_index; 
} 


void Graph::printSolution(int dist[]) 
{ 
	printf("Vertex \t\t Distance from Source\n"); 
	for (int i = 0; i < n_Vertices; i++) 
		printf("%d \t\t %d\n", i, dist[i]); 
} 


void Graph::dijkstra(int graph[n_Vertices][n_Vertices], int src) 
{ 
	/**
	 * @brief The output array. dist[i] will hold the shortest
	 * distance from src to i
	 */
	int dist[n_Vertices]; 

	/**
	 * @brief sptSet[i] will be true if vertex i is included in shortest
	 * path tree or shortest distance from src to i is finalized
	 */
	bool sptSet[n_Vertices];  

	/**
	 * @brief Initialize all distances as INFINITE and stpSet[] as false
	 */
	for (int i = 0; i < n_Vertices; i++) 
		dist[i] = INT_MAX, sptSet[i] = false; 

	/**
	 * @brief Distance of source vertex from itself is always 0
	 */
	dist[src] = 0; 

	/**
	 * @brief Find shortest path for all vertices
	 */
	for (int count = 0; count < n_Vertices - 1; count++) { 
		/**
		 * @brief Pick the minimum distance vertex from the set of vertices not
		 * yet processed. u is always equal to src in the first iteration.
		 */
		int u = minDistance(dist, sptSet); 
 
		/**
		 * @brief Mark the picked vertex as processed
		 */
		sptSet[u] = true; 

		/**
		 * @brief Update dist value of the adjacent vertices of the picked vertex.
		 */
		for (int v = 0; v < n_Vertices; v++) 
 
			/**
			 * @brief Update dist[v] only if is not in sptSet, there is an edge from 
			 * u to v, and total weight of path from src to v through u is 
			 * smaller than current value of dist[v] 
			 */
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
				&& dist[u] + graph[u][v] < dist[v]) 
				dist[v] = dist[u] + graph[u][v]; 
	} 
 
	/**
	 * @brief print the constructed distance array
	 */
	printSolution(dist); 
} 