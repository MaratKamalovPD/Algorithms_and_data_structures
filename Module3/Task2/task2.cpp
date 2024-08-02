// Задача 2. Количество различных путей(3 балла)
// Обязательная задача
// Дан невзвешенный неориентированный граф.В графе может быть несколько кратчайших путей между какими - то вершинами.Найдите количество различных кратчайших путей между заданными вершинами.
// Требования: сложность O(V + E).
// Формат ввода.
// v : кол - во вершин(макс. 50000),
// n : кол - во ребер(макс. 200000),
// n пар реберных вершин,
// пара вершин u, w для запроса.
// Формат вывода.
// Количество кратчайших путей от u к w.

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

int FindCoutOfMinPaths(const IGraph& graph, int vertex, int stop)
{
	std::vector<bool> visited(graph.VerticesCount(), false);
	std::vector<int> shortest_path_count(graph.VerticesCount(), 0); // массив количеств кратчайших расстояний до каждой вершины
	std::set<int> wave_set_write; // множество вершин в предыдущей "волне"
	std::set<int> wave_set_intermediate; // во процессе отладки стало понятно, что write слишком рано затирает read, поэтому было нужно промежуточное множество
	std::set<int> wave_set_read; // множество вершин в текущей "волне" 
	shortest_path_count[vertex] = 1;
	std::queue<int> bfs_queue;

	bfs_queue.push(vertex);

	wave_set_intermediate.insert(vertex);
	bfs_queue.push(-1); // -1 - маркер перехода к вершинам новой "волны"

	visited[vertex] = true;
	while ((bfs_queue.size() > 0))
	{
		int current = bfs_queue.front();
		if (current == -1) // когда из очереди достаётся -1, то происходит переход к новой "волне"
		{
			bfs_queue.push(-1); // и тут же снова закидываем -1 в очередь
			wave_set_read = wave_set_intermediate; // множеству вершин предыдущей "волны" присваивается значение промежуточного буфера
			wave_set_intermediate = wave_set_write; // множество вершин текущей "волны" записывается в промежуточный буфер
			wave_set_write.clear(); // очищаем множество вершин текущей "волны" 
			bfs_queue.pop();
			current = bfs_queue.front();
			if (current == -1) // если в очереди больше нет вершин, а только -1  
			{
				break;
			}
		}
		bfs_queue.pop();
		std::vector<int> adjacency_list = graph.GetNextVertices(current);
		for (int i = 0; i < adjacency_list.size(); ++i)
		{
			if (wave_set_read.count(adjacency_list[i])) // если в множестве вершин предыдущей "волны" есть вершина из списка смежности текущей вершины
			{
				shortest_path_count[current] += shortest_path_count[adjacency_list[i]]; // то увеличиваем счётчик количества кратчайших путей до соответствующей вершины
			}
			if (!visited[adjacency_list[i]])
			{
				bfs_queue.push(adjacency_list[i]);
				wave_set_write.insert(adjacency_list[i]); // добавляем в множество вершин текущей "волны" очередную вершины  
				visited[adjacency_list[i]] = true;
			}
		}
	}
	return shortest_path_count[stop];
}

class ListGraph : public IGraph
{
public:
	ListGraph(int vertexCount);
	ListGraph(const IGraph& graph);

	virtual void AddEdge(int from, int to) override;
	virtual int VerticesCount() const override;
	virtual std::vector<int> GetNextVertices(int vertex) const override;
	virtual std::vector<int> GetPrevVertices(int vertex) const override;

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


void Run(std::istream& input, std::ostream& output)
{
	int v = 0; // количество вершин
	int n = 0; // количество рёбер

	int v1 = 0; // первая вершина инцидентная вставляемому ребру
	int v2 = 0; // вторая вершина инцидентная вставляемому ребру

	int u = 0; // начальная вершина
	int w = 0; // конечная вершина

	input >> v;
	ListGraph g(v);
	input >> n;
	for (int i = 0; i < n; ++i)
	{
		input >> v1 >> v2;
		g.AddEdge(v1, v2);
		g.AddEdge(v2, v1);
	}
	input >> u >> w;
	output << FindCoutOfMinPaths(g, u, w);
}

void TestSolution()
{
	{
		std::stringstream output;
		std::stringstream input;
		input << "8 15 0 1 0 7 0 3 1 2 1 3 7 3 7 5 3 2 3 4 3 5 2 4 4 5 2 6 4 6 5 6 0 6";
		Run(input, output);
		assert(output.str() == "5");
	}

	{
		std::stringstream output;
		std::stringstream input;
		input << "4 5 0 1 0 2 1 2 1 3 2 3 0 3";
		Run(input, output);
		assert(output.str() == "2");
	}
}


int main()
{
	//TestSolution();
	Run(std::cin, std::cout);
}