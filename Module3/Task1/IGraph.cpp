#include <vector>
#include <queue>
#include <cassert>

#include "IGraph.h"

void BFS(const IGraph& graph, int vertex, std::ostream& output, void (*visit)(int v, std::ostream& output))
{
	std::vector<bool> visited(graph.VerticesCount(), false);
	std::queue<int> bfs_queue;
	bfs_queue.push(vertex);
	visited[vertex] = true;
	while (bfs_queue.size() > 0)
	{
		int current = bfs_queue.front();
		bfs_queue.pop();
		visit(current, output);
		std::vector<int> adjacency_list = graph.GetNextVertices(current);
		for (int i = 0; i < adjacency_list.size(); ++i) 
		{
			if (!visited[adjacency_list[i]])
			{
				bfs_queue.push(adjacency_list[i]);
				visited[adjacency_list[i]] = true;
			}
		}
	}
}

