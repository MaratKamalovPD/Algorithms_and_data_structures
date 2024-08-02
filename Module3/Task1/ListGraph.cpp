#include "ListGraph.h"

ListGraph::ListGraph(int vertex_ñount)
{
	adjacency_list.resize(vertex_ñount);
	previous_adjacency_list.resize(vertex_ñount);
}

ListGraph::ListGraph(const IGraph& graph)
{
	adjacency_list.resize(graph.VerticesCount());
	previous_adjacency_list.resize(graph.VerticesCount());
	for (int i = 0; i < graph.VerticesCount(); ++i) 
	{
		adjacency_list[i] = graph.GetNextVertices(i);
		previous_adjacency_list[i] = graph.GetPrevVertices(i);
	}
}

void ListGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < adjacency_list.size());
	assert(to >= 0 && to < adjacency_list.size());

	adjacency_list[from].push_back(to);
	previous_adjacency_list[to].push_back(from);
}

int ListGraph::VerticesCount() const
{
	return adjacency_list.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < adjacency_list.size());
	return adjacency_list[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < adjacency_list.size());
	return previous_adjacency_list[vertex];
}