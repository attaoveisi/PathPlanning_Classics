/// @brief Program to print BFS traversal from a given 
/// @brief source vertex. BFS(int s) traverses vertices 
/// @brief reachable from s. 
#include<iostream> 
#include <list> 

using namespace std; 

/// @brief This class represents a directed graph using 
/// @brief adjacency list representation 
class Graph 
{ 
private:
	/// @param Vertices private parameter for No. of vertices 
	int Vertices; 

	/// @brief Pointer to an array containing adjacency lists 
	list<int> *adjacent; 
public: 
	/// @brief Constructor for accessing the private ... 
	/// @brief variable Vertices and initialization of adjacent list
	/// @param Vertices graph size (number of vertices)
	Graph(int Vertices); 


	/// @brief function to add an edge to the graph, namely adjacent object 
	/// @param v size
	/// @param w size
	void addEdge(int v, int w); 

	/// @brief prints BFS traversal from a given source s 
	void BFS(int s); 
}; 

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

	/// @brief Mark the current node as visited and enqueue it 
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

/// @brief Driver program to test methods of graph class 
int main() 
{ 
	/// @brief Create a graph given in the above diagram 
	Graph g(4); 
	g.addEdge(0, 1); 
	g.addEdge(0, 2); 
	g.addEdge(1, 2); 
	g.addEdge(2, 0); 
	g.addEdge(2, 3); 
	g.addEdge(3, 3); 

	int start_v = 2;

	cout << "Following is Breadth First Traversal "
		<< "(starting from vertex " << start_v << ")" << endl; 
	g.BFS(start_v); 

	return 0; 
} 

