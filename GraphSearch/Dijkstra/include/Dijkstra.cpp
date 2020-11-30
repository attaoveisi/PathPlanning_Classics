#include "Dijkstra.hpp"

namespace forwardsearch{
namespace Dijkstra{

/**
 * @brief Construct a new Graph:: Graph object
 * 
 * @param n_Vertices 
 */
Graph::Graph(const int n_Vertices, const int m_Vertices)
{
	this->n_Vertices = n_Vertices;
	this->m_Vertices = n_Vertices;
	for (int i=0; i < n_Vertices; i++){
		graph.push_back(std::vector<int>(m_Vertices,0));
	}
}

void Graph::addWeights(std::vector<int> graph_raws,int raw_number){
	for (int i = 0; i < graph_raws.size(); i++){
		graph.at(raw_number).at(i) = graph_raws.at(i);
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
		if (sptSet.at(v) == false && dist.at(v) <= min) {
			min = dist.at(v);
			min_index = v; 
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
	std::vector<int> dist(n_Vertices,INT_MAX);

	/**
	 * @brief Distance of source vertex from itself is always 0
	 */
	dist.at(source) = 0;

	/**
	 * @brief sptSet[i] will be true if vertex i is included in shortest
	 * path tree or shortest distance from source to i is finalized
	 * Initialize stpSet[] as false
	 */  
	std::vector<bool> sptSet(n_Vertices,false); 

	/**
	 * @brief Find shortest path for all vertices
	 */
	for (int i = 0; i < n_Vertices; i++) { 
		/**
		 * @brief Pick the minimum distance vertex from the set of vertices not
		 * yet processed. u is always equal to source in the first iteration.
		 */
		int u = minDistance(dist, sptSet); 
		//std::cout << u << std::endl; debug command
 
		/**
		 * @brief Mark the picked vertex as processed
		 */
		sptSet.at(u) = true; 

		/**
		 * @brief Update dist value of the adjacent vertices of the picked vertex.
		 */
		for (int v = 0; v < n_Vertices; v++) 
 
			/**
			 * @brief Update dist[v] only if is not in sptSet, there is an edge from 
			 * u to v, and total weight of path from source to v through u is 
			 * smaller than current value of dist[v] 
			 */
			if (!sptSet.at(v) && graph.at(u).at(v) && dist.at(u) != INT_MAX 
				&& dist.at(u) + graph.at(u).at(v) < dist.at(v)){
					dist.at(v) = dist.at(u) + graph.at(u).at(v);
				} 
	} 
	printSolution(dist);
} 

/**
 * @brief print the constructed distance array
 */
void Graph::printSolution(std::vector<int> dist){ 
	std::cout << std::endl;
	std::cout << "Distant array is constructed as:" << std::endl;
	std::cout << "Vertex" << '\t' << "Distance from Source" << std::endl; 
	for (int i = 0; i < n_Vertices; i++){
		std::cout << i << '\t' << dist.at(i) << std::endl; 
	}	
} 

void Graph::printGraph(){
	std::cout << "The graph structure is given as: " << std::endl;
	for (int i = 0; i<n_Vertices; i++){
		for(int j = 0; j<m_Vertices; j++){
			std::cout << graph.at(i).at(j) << " ";
		}
		std::cout << std::endl;
	}
}

} // Dijkstra
} // forwardsearch