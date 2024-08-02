#ifndef IGRAPH_H
#define IGRAPH_H


#include <vector>
#include <queue>
#include <cassert>
#include <sstream>

struct IGraph 
{
	virtual ~IGraph() {}

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const = 0;

	virtual std::vector<int> GetNextVertices(int vertex) const = 0;
	virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

void BFS(const IGraph& graph, int vertex, std::ostream& output, void (*visit)(int v, std::ostream& output));

#endif