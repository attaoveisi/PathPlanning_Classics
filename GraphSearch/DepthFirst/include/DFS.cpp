#include "DFS.hpp"

namespace forwardsearch{
namespace DFS{
Graph::Graph(int n_Vertices)
{
	this->n_Vertices = n_Vertices;
	adjacent = new std::list<int>[n_Vertices];
}

void Graph::addEdge(int v, int w)
{
	adjacent[v].push_back(w); // Add w to v’s list.
}

void Graph::DFSUtil(int v, bool visited[])
{
	/**
	 * @brief Mark the current node as visited and print it
	 * 
	 */
	visited[v] = true;
	std::cout << v << " ";

	/**
	 * @brief Recur for all the vertices adjacent to this vertex
	 * 
	 */
	std::list<int>::iterator i;
	for (i = adjacent[v].begin(); i != adjacent[v].end(); ++i)
		if (!visited[*i])
			DFSUtil(*i, visited);
}

/**
 * @brief DFS traversal of the vertices reachable from v.
 * @brief It uses recursive DFSUtil()
 * 
 */
void Graph::DFS(int v)
{
	/**
	 * @brief Mark all the vertices as not visited
	 * 
	 */
	bool* visited = new bool[n_Vertices];
	for (int i = 0; i < n_Vertices; i++)
		visited[i] = false;

	/**
	 * @brief Call the recursive helper function
	 * @brief to print DFS traversal
	 * 
	 */
	DFSUtil(v, visited);
}
} //DFS
} //forwardsearch