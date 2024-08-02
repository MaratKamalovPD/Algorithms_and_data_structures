#include "SetGraph.h"

SetGraph::SetGraph(int vertex_ñount)
{
	vector_of_sets.resize(vertex_ñount);
	prev_vector_of_sets.resize(vertex_ñount);
}

SetGraph::SetGraph(const IGraph& graph)
{
	vector_of_sets.resize(graph.VerticesCount());
	prev_vector_of_sets.resize(graph.VerticesCount());
	for (int i = 0; i < graph.VerticesCount(); ++i)
	{
		std::set<int> set_to_add;
		for (int j = 0; j < graph.GetNextVertices(i).size(); ++j)
		{
			set_to_add.insert(graph.GetNextVertices(i)[j]);
		}
		vector_of_sets[i] = set_to_add;
	}
}

void SetGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < vector_of_sets.size());
	assert(to >= 0 && to < vector_of_sets.size());

	vector_of_sets[from].insert(to);
	prev_vector_of_sets[to].insert(from);

}

int SetGraph::VerticesCount() const
{
	return vector_of_sets.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < vector_of_sets.size());
	std::vector<int> result_vector;
	for (int elem : vector_of_sets[vertex])
	{
		result_vector.push_back(elem);
	}
	return result_vector;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < vector_of_sets.size());
	std::vector<int> result_vector;
	for (int elem : prev_vector_of_sets[vertex])
	{
		result_vector.push_back(elem);
	}
	return result_vector;
}