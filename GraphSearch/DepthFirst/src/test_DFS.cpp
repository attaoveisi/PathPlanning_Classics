#include "DFS.hpp"
/**
* @brief Program to print DFS traversal from a given 
* @brief source vertex. DFS(int s) traverses vertices 
* @brief reachable from a start node. 
*/
int main()
{
	/** 
	 * @brief Create a graph given in the above diagram 
	 */
    int nVertices = 5;
	forwardsearch::DFS::Graph m_Graph(nVertices);

	/** 
	 * @brief Define the graph structure 
	 */
	m_Graph.addEdge(0, 1);
	m_Graph.addEdge(0, 2);
	m_Graph.addEdge(1, 2);
	m_Graph.addEdge(2, 0);
	m_Graph.addEdge(2, 3);
	m_Graph.addEdge(3, 3);
    m_Graph.addEdge(3, 4);

    int start_v = 2;

	std::cout << "The Depth First Search (DFS) Traversal"
			" (starting from vertex " << start_v << ")" << std::endl;

	m_Graph.DFS();

	return 0;
}
