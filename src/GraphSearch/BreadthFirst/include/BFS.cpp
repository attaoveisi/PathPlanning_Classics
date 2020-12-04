#include "BFS.hpp"

namespace forwardsearch{
namespace BFS{
Graph::Graph(int Vertices) 
{ 
	this->Vertices = Vertices; 
	for(int i=0;i!=Vertices;i++){
		adjacent.push_back(std::vector<int>{});
	}
} 


void Graph::addEdge(int from, int to) 
{ 
	adjacent[from].push_back(to); // Add to to from. 
} 

void Graph::BFS(int s) 
{ 
	/** 
	 * @brief Mark all the vertices as not visited 
	 */
	std::vector<bool> visited; 
	for(int j = 0; j < Vertices; j++){
		visited.push_back(false);
	} 

	/** 
	 * @brief Create a queue for BFS 
	 */
	std::vector<int> queue; 

	/** 
	 * @brief Mark the current (start) node as visited and enqueue it 
	 */
	visited[s] = true; 
	queue.push_back(s); 	

	while(!queue.empty()) 
	{   
		/** 
		 * @brief Dequeue a vertex from queue and print it 
		 */
		s = queue.front(); 
		print_quene(s);
		queue.erase(queue.begin()); 
		/** 
		 * @brief Get all adjacent vertices of the dequeued vertex s.
		 * @brief If a adjacent has not been visited, ...
		 * @brief then mark it visited and enqueue it
		 */
		for (auto i = adjacent[s].begin(); i != adjacent[s].end(); ++i) 
		{ 
			if (!visited[*i]) 
			{ 
				visited[*i] = true; 
				queue.push_back(*i); 
			} 
		} 
	} 
	print_quene();
} 

void Graph::print_quene(int vortex){
	std::cout << vortex << " "; 
}

void Graph::print_quene(){
	std::cout << std::endl; 
}
} // BFS
} // forwardsearch