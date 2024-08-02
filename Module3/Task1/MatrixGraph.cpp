#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int vertex_ñount)
{
	adjacency_maxtrix.resize(vertex_ñount);
	for (size_t i = 0; i < vertex_ñount; i++)
	{
		adjacency_maxtrix[i].resize(vertex_ñount);
	}
}

MatrixGraph::MatrixGraph(const IGraph& graph)
{
	adjacency_maxtrix.resize(graph.VerticesCount());
	for (int i = 0; i < graph.VerticesCount(); ++i)
	{
		std::vector<bool> vector_to_add;
		vector_to_add.resize(graph.VerticesCount());
		for (int j = 0; j < graph.GetNextVertices(i).size(); ++j)
		{
			vector_to_add[graph.GetNextVertices(i)[j]] = true;
		}
		adjacency_maxtrix[i] = vector_to_add;
	}
}

void MatrixGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < adjacency_maxtrix.size());
	assert(to >= 0 && to < adjacency_maxtrix.size());

	adjacency_maxtrix[from][to] = true;
}

int MatrixGraph::VerticesCount() const
{
	return adjacency_maxtrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < adjacency_maxtrix.size());
	std::vector<int> result_vector;
	for (int i = 0; i < adjacency_maxtrix.size(); ++i)
	{
		if (adjacency_maxtrix[vertex][i])
		{
			result_vector.push_back(i);
		}
	}
	return result_vector;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < adjacency_maxtrix.size());
	std::vector<int> result_vector;
	for (int i = 0; i < adjacency_maxtrix.size(); ++i)
	{
		if (adjacency_maxtrix[i][vertex])
		{
			result_vector.push_back(i);
		}
	}
	return result_vector;
}