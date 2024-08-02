#include "ArcGraph.h"

ArcGraph::ArcGraph(int vertex_ñount)
{
	edge_vector.resize(vertex_ñount);
}

ArcGraph::ArcGraph(const IGraph& graph)
{
	edge_vector.resize(graph.VerticesCount());
	for (int i = 0; i < graph.VerticesCount(); ++i)
	{
		for (int j = 0; j < graph.GetNextVertices(i).size(); ++j)
		{
			std::pair<int, int> edge_to_insert;
			edge_to_insert.first = i;
			edge_to_insert.second = graph.GetNextVertices(i)[j];
			edge_vector.push_back(edge_to_insert);
		}
	}
}

void ArcGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < edge_vector.size());
	assert(to >= 0 && to < edge_vector.size());
	std::pair<int, int> edge_to_insert;
	
	edge_to_insert.first = from;
	edge_to_insert.second = to;
	
	edge_vector.push_back(edge_to_insert);
	
}

int ArcGraph::VerticesCount() const
{
	return edge_vector.size();
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < edge_vector.size());
	std::vector<int> result_vector;
	for (int i = 0; i < edge_vector.size(); ++i)
	{
		if (edge_vector[i].first == vertex)
		{
			result_vector.push_back(edge_vector[i].second);
		}
	}
	return result_vector;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < edge_vector.size());
	std::vector<int> result_vector;
	for (int i = 0; i < edge_vector.size(); ++i)
	{
		if (edge_vector[i].second == vertex)
		{
			result_vector.push_back(edge_vector[i].first);
		}
	}
	return result_vector;
}