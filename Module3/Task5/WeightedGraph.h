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

    // ���������� ����� �� from � to.
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
    WeightedListGraph GetMST(); // ��� this ���������� ����������� �������� ������ � ���� ��������� ������ WeightedListGraph
    std::vector<int> DFS(); // ���������� ������ ������ � ������� ������ � �������
    size_t GetMSTWeight(); // ���������� ����� ����� ���� ������������ ��������� ������
    float GetWeight(int from, int to) const; // ���������� ��� ����� �� ������� from � ������� to


private:
    std::vector <std::vector <std::pair<int, float>>> adjacency_list; // first - ����������� �������, second - ��� �����
    std::vector <std::vector <std::pair<int, float>>> previous_adjacency_list; // first - ����������� �������, second - ��� �����
    void DFS_Private(int vertex, std::vector<bool>& visited, std::vector<int>& vertex_list); // ��������������� ������� ��� ������� "std::vector<int> DFS();" ��� ������������ ������
};

#endif