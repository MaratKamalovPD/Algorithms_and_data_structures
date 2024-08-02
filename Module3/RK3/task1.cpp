#include <vector>
#include <queue>
#include <cassert>
#include <sstream>
#include <set>
#include <iostream>
#include <limits.h>

struct IGraph
{
	virtual ~IGraph() {}

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const = 0;

	virtual std::vector<int> GetNextVertices(int vertex) const = 0;
	virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};



class ListGraph : public IGraph
{
public:
	ListGraph(int vertexCount);
	ListGraph(const IGraph& graph);

	virtual void AddEdge(int from, int to) override;
	virtual int VerticesCount() const override;
	virtual std::vector<int> GetNextVertices(int vertex) const override;
	virtual std::vector<int> GetPrevVertices(int vertex) const override;
	bool DFS(int vertex, std::vector<bool>& visited, int parent);
	int isTree();

private:
	std::vector<std::vector<int>> adjacency_list;
	std::vector<std::vector<int>> previous_adjacency_list;
};

ListGraph::ListGraph(int vertex_сount)
{
	adjacency_list.resize(vertex_сount);
	previous_adjacency_list.resize(vertex_сount);
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


bool ListGraph::DFS(int vertex, std::vector<bool>& visited, int parent)
{
	visited[vertex] = true;

	std::vector<int> edge_list = GetNextVertices(vertex);
	for (int i = 0; i < edge_list.size(); ++i)
	{
		if (!visited[edge_list[i]])
		{
			if (!DFS(edge_list[i], visited, vertex))
			{
				return false;
			}
		}
		else
		{
			if (edge_list[i] != parent)
			{
				return false;
			}
		}

	}
	return true;
}


int ListGraph::isTree()
{
	std::vector<bool> visited(VerticesCount());
	bool isTree = true;
	isTree = DFS(0, visited, -1);
	for (int i = 0; isTree && i < VerticesCount(); i++)
	{
		if (!visited[i])
		{
			isTree = false;
		}
	}

	if (isTree)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}




void Run(std::istream& input, std::ostream& output)
{
	int v = 0; // количество вершин
	int n = 0; // количество рёбер

	int v1 = 0; // первая вершина инцидентная вставляемому ребру
	int v2 = 0; // вторая вершина инцидентная вставляемому ребру

	input >> v;
	ListGraph g(v);
	input >> n;
	for (int i = 0; i < n; ++i)
	{
		input >> v1 >> v2;
		g.AddEdge(v1, v2);
		g.AddEdge(v2, v1);
	}

	output << g.isTree();
}

void TestSolution()
{
	{
		std::stringstream output;
		std::stringstream input;
		input << "3	2 0 1 0 2";
		Run(input, output);
		assert(output.str() == "1");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "4	2 0 1 0 2";
		Run(input, output);
		assert(output.str() == "0");
	}
}


int main()
{
	//TestSolution();
	Run(std::cin, std::cout);
}