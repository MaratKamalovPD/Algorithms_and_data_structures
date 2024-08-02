#ifndef WEIGHTGRAPH_H
#define WEIGHTGRAPH_H

#include <vector>
#include <queue>
#include <cassert>
#include <sstream>
#include <set>
#include <iostream>
#include <limits.h>
#include <random>
#include <string>
#include <iomanip>
#include <cmath>


struct WeightedIGraph
{
    virtual ~WeightedIGraph() {}

    // ƒобавление ребра от from к to.
    virtual void AddEdge(int from, int to, float weight) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<std::pair<int, float>> GetNextVertices(int vertex) const = 0;
    virtual std::vector<std::pair<int, float>> GetPrevVertices(int vertex) const = 0;
};

class WeightedListGraph : public WeightedIGraph
{
public:
    WeightedListGraph(int vertexCount);

    virtual void AddEdge(int from, int to, float weight) override;
    virtual int VerticesCount() const override;
    virtual std::vector<std::pair<int, float>> GetNextVertices(int vertex) const override;
    virtual std::vector<std::pair<int, float>> GetPrevVertices(int vertex) const override;
    WeightedListGraph GetMST(); // дл€ this возвращает минимальное остовное дерево в виде структуры данных WeightedListGraph
    std::vector<int> DFS(); // возвращает вектор вершин в пор€дке обхода в глубину
    size_t GetMSTWeight(); // возвращает сумму весов рЄбер минимального остовного дерева
    float GetWeight(int from, int to) const; // возвращает вес ребра из вершины from в вершину to


private:
    std::vector <std::vector <std::pair<int, float>>> adjacency_list; // first - инцидентна€ вершина, second - вес ребра
    std::vector <std::vector <std::pair<int, float>>> previous_adjacency_list; // first - инцидентна€ вершина, second - вес ребра
    void DFS_Private(int vertex, std::vector<bool>& visited, std::vector<int>& vertex_list); // вспомогательна€ функци€ дл€ функции "std::vector<int> DFS();" дл€ рекурсивного вызова
};

#endif