#include "Dijkstra.hpp"

namespace forwardsearch{
namespace Dijkstra{

/**
 * @brief Construct a new Graph:: Graph object
 * 
 * @param n_Vertices 
 */
Graph::Graph(int n_Vertices, int m_Vertices)
{
	this->n_Vertices = n_Vertices;
	this->m_Vertices = n_Vertices;
	for (int i=0; i < n_Vertices; i++){
		graph.push_back(std::vector<int>(m_Vertices,0));
	}
}


int Graph::minDistance(std::vector<int> dist, std::vector<bool> sptSet) 
{ 
	/**
	 * @brief Initialize min value 
	 * @return min_index
	 */
	int min = INT_MAX, min_index; 

	for (int v = 0; v < n_Vertices; v++) {
		if (sptSet[v] == false && dist[v] <= min) {
			min = dist[v], min_index = v; 
		}
	}
	return min_index; 
} 

void Graph::dijkstra(int source) 
{ 
	/**
	 * @brief The output array. dist[i] will hold the shortest
	 * distance from source to i
	 * Initialize all distances as INFINITE 
	 */
	std::vector<int> dist(INT_MAX,n_Vertices);

	/**
	 * @brief sptSet[i] will be true if vertex i is included in shortest
	 * path tree or shortest distance from source to i is finalized
	 * Initialize stpSet[] as false
	 */  
	std::vector<bool> sptSet(false,n_Vertices);

	/**
	 * @brief Distance of source vertex from itself is always 0
	 */
	dist[source] = 0; 

	/**
	 * @brief Find shortest path for all vertices
	 */
	for (int i = 0; i < n_Vertices - 1; i++) { 
		/**
		 * @brief Pick the minimum distance vertex from the set of vertices not
		 * yet processed. u is always equal to source in the first iteration.
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
			 * u to v, and total weight of path from source to v through u is 
			 * smaller than current value of dist[v] 
			 */
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
				&& dist[u] + graph[u][v] < dist[v]) 
				dist[v] = dist[u] + graph[u][v]; 
	} 
} 

/**
 * @brief print the constructed distance array
 */
void Graph::printSolution(std::vector<int> dist){ 
	std::cout << "Vertex" << '\t' << "Distance from Source" << std::endl; 
	for (int i = 0; i < n_Vertices; i++){
		std::cout << i << '\t' << dist[i] << std::endl; 
	}	
} 

} // Dijkstra
} // forwardsearch