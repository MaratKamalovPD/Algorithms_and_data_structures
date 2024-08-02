#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "IGraph.h"

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

#endif