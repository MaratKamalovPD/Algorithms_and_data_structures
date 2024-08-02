// ��������� �������� ����� �������� ������� ����� ��������.
// ����������: ����� ������ O((N + M)logN), ��� N - ���������� �������, M - ��������� ����� ����� ����.
// ������ ������� ������.
// ������ ������ �������� ����� N � ���������� �������.
// ������ ������ �������� ����� M - ���������� �����.
// ������ ��������� ������ �������� �������� ������(������, ����, ����� � ����).
// ��������� ������ �������� �������(������ � ���� ����� �������).
// ������ �������� ������.
// ������� ����� ������ ��������� ��������


#include <vector>
#include <queue>
#include <cassert>
#include <sstream>
#include <set>
#include <iostream>
#include <limits.h>

struct WeightedIGraph
{
    virtual ~WeightedIGraph() {}

    // ���������� ����� �� from � to.
    virtual void AddEdge(int from, int to, int weight) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const = 0;
    virtual std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const = 0;
};

class WeightedListGraph : public WeightedIGraph
{
public:
    WeightedListGraph(int vertexCount);

    virtual void AddEdge(int from, int to, int weight) override;
    virtual int VerticesCount() const override;
    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override;
    virtual std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const override;
    int GetPathByDijkstraAlg(int from, int to);

private:
    std::vector <std::vector <std::pair<int, int>>> adjacency_list; // first - ����������� �������, second - ��� �����
    std::vector <std::vector <std::pair<int, int>>> previous_adjacency_list; // first - ����������� �������, second - ��� �����
    std::vector <int> distance;

};

WeightedListGraph::WeightedListGraph(int vertex_�ount)
{
    adjacency_list.resize(vertex_�ount);
}

void WeightedListGraph::AddEdge(int from, int to, int weight)
{
    assert(from >= 0 && from < adjacency_list.size());
    assert(to >= 0 && to < adjacency_list.size());
    adjacency_list[from].push_back(std::make_pair(to, weight));
}

int WeightedListGraph::VerticesCount() const
{
    return adjacency_list.size();
}

std::vector<std::pair<int, int>> WeightedListGraph::GetNextVertices(int vertex) const
{
    assert(vertex >= 0 && vertex < adjacency_list.size());
    return adjacency_list[vertex];
}

std::vector<std::pair<int, int>> WeightedListGraph::GetPrevVertices(int vertex) const
{
    assert(vertex >= 0 && vertex < adjacency_list.size());
    return previous_adjacency_list[vertex];
}

int WeightedListGraph::GetPathByDijkstraAlg(int from, int to)
{
    distance.resize(VerticesCount(), INT_MAX);
    distance[from] = 0;

    std::set<std::pair<int, int>> priority_queue;
    priority_queue.insert(std::make_pair(distance[from], from));

    while (!priority_queue.empty())
    {
        std::pair<int, int> min_element = *priority_queue.begin();
        int vertex = min_element.second;
        priority_queue.erase(min_element);
        std::vector<std::pair<int, int>> edge_list = GetNextVertices(vertex);
        for (int i = 0; i < edge_list.size(); ++i)
        {
            std::pair<int, int> iteration_pair = edge_list[i];
            if (distance[iteration_pair.first] > distance[vertex] + iteration_pair.second)
            {
                if (distance[vertex] != INT_MAX)
                {
                    priority_queue.erase(std::make_pair(distance[vertex], vertex));
                }
                distance[iteration_pair.first] = distance[vertex] + iteration_pair.second;
                priority_queue.insert(std::make_pair(iteration_pair.second, iteration_pair.first));
            }
        }
    }
    return distance[to];
}


int main()
{
    int N = 0; // ���������� ������
    int M = 0; // ���������� ����

    int v1 = 0; // ������ ������� ����������� ������������ �����
    int v2 = 0; // ������ ������� ����������� ������������ �����
    int weight = 0; // ��� ����� ����� ��������� v1 � v2

    int u = 0; // ��������� �������
    int w = 0; // �������� �������

    std::cin >> N;
    WeightedListGraph g(N);
    std::cin >> M;
    for (int i = 0; i < M; ++i)
    {
        std::cin >> v1 >> v2 >> weight;
        g.AddEdge(v1, v2, weight);
        g.AddEdge(v2, v1, weight);

    }
    std::cin >> u >> w;

    std::cout << g.GetPathByDijkstraAlg(u, w);
}

