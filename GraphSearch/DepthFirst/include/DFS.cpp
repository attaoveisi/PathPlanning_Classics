#include "DFS.hpp"

namespace forwardsearch{
namespace DFS{
Graph::Graph(int n_Vertices)
{
	this->n_Vertices = n_Vertices;
	for (int i=0; i!= n_Vertices; i++){
		adjacent.push_back(std::vector<int>{});
	}
}

void Graph::addEdge(int from, int to)
{
	adjacent[from].push_back(to); // Add to to from’s list.
}

void Graph::DFSUtil(int vertex, std::vector<bool> visited)
{
	/**
	 * @brief Mark the current node as visited and print it
	 * 
	 */
	visited[vertex] = true;
	std::cout << vertex << " ";

	for (auto i = adjacent[vertex].begin(); i != adjacent[vertex].end(); ++i){
		if (!visited[*i]){
			DFSUtil(*i, visited);
		}
	}
}

/**
 * @brief DFS traversal of the vertices reachable from v.
 * @brief It uses recursive DFSUtil()
 * 
 */
void Graph::DFS()
{
	/**
	 * @brief Mark all the vertices as not visited
	 * 
	 */
	std::vector<bool> visited;
	for (int i = 0; i < n_Vertices; i++){
		visited[i] = false;
	}

	/**
	 * @brief Call the recursive helper function to print DFS
	 * traversal starting from all vertices one by one
	 * 
	 */
	for (int i = 0; i < n_Vertices; i++){
		if (!visited[i]){
			DFSUtil(i, visited);
		}
	}
}
} //DFS
} //forwardsearch