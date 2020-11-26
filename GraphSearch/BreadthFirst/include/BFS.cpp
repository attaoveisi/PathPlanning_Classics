#include "BFS.hpp"

Graph::Graph(int Vertices) 
{ 
	this->Vertices = Vertices; 
	adjacent = new list<int>[Vertices]; 
} 

void Graph::addEdge(int v, int w) 
{ 
	adjacent[v].push_back(w); // Add w to v’s list. 
} 

void Graph::BFS(int s) 
{ 
	/// @brief Mark all the vertices as not visited 
	bool *visited = new bool[Vertices]; 
	for(int j = 0; j < Vertices; j++){
		visited[j] = false;
	} 

	/// @brief Create a queue for BFS 
	list<int> queue; 

	/// @brief Mark the current (start) node as visited and enqueue it 
	visited[s] = true; 
	queue.push_back(s); 

	/// @brief 'i' will be used to get all adjacent 
	/// @brief vertices of a vertex 
	list<int>::iterator i; 

	while(!queue.empty()) 
	{ 
		/// @brief Dequeue a vertex from queue and print it 
		s = queue.front(); 
		cout << s << " "; 
		queue.pop_front(); 

		/// @brief Get all adjacent vertices of the dequeued vertex s.
		/// @brief If a adjacent has not been visited, ...
		/// @brief then mark it visited and enqueue it 
		for (i = adjacent[s].begin(); i != adjacent[s].end(); ++i) 
		{ 
			if (!visited[*i]) 
			{ 
				visited[*i] = true; 
				queue.push_back(*i); 
			} 
		} 
	} 
} 