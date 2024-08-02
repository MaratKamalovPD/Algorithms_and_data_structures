#ifndef SETGRAPH_H
#define SETGRAPH_H

#include "IGraph.h"
#include <set>

class SetGraph : public IGraph
{
public:
	SetGraph(int vertexCount);
	SetGraph(const IGraph& graph);

	virtual void AddEdge(int from, int to) override;
	virtual int VerticesCount() const override;
	virtual std::vector<int> GetNextVertices(int vertex) const override;
	virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
	std::vector<std::set<int>> vector_of_sets; 
	std::vector<std::set<int>> prev_vector_of_sets;
};

#endif
