#include "WeightedGraph.h"

WeightedListGraph::WeightedListGraph(int vertex_ñount)
{
    adjacency_list.resize(vertex_ñount);
}

void WeightedListGraph::AddEdge(int from, int to, float weight)
{
    assert(from >= 0 && from < adjacency_list.size());
    assert(to >= 0 && to < adjacency_list.size());
    std::pair<int, float> pair_to_pushback;
    pair_to_pushback.first = to;
    pair_to_pushback.second = weight;
    adjacency_list[from].push_back(pair_to_pushback);
}

int WeightedListGraph::VerticesCount() const
{
    return adjacency_list.size();
}

std::vector<std::pair<int, float>> WeightedListGraph::GetNextVertices(int vertex) const
{
    assert(vertex >= 0 && vertex < adjacency_list.size());
    return adjacency_list[vertex];
}

std::vector<std::pair<int, float>> WeightedListGraph::GetPrevVertices(int vertex) const
{
    assert(vertex >= 0 && vertex < adjacency_list.size());
    return previous_adjacency_list[vertex];
}

float WeightedListGraph::GetWeight(int from, int to) const
{
    assert(from >= 0 && from < adjacency_list.size());
    assert(to >= 0 && to < adjacency_list.size());
    for (int i = 0; i < adjacency_list[from].size(); ++i)
    {
        if (adjacency_list[from][i].first == to)
        {
            return adjacency_list[from][i].second;
        }
    }
    return -1;
}


WeightedListGraph WeightedListGraph::GetMST()
{
    std::vector <int> distance;
    distance.resize(VerticesCount(), INT_MAX);
    int from = 0;
    distance[from] = 0;
    std::vector <int> parent;
    parent.resize(VerticesCount(), -1);
    std::vector<bool> vertex_in_MST;
    vertex_in_MST.resize(VerticesCount(), false);

    std::set<std::pair<int, int>> priority_queue;
    priority_queue.insert(std::make_pair(distance[from], from));

    while (!priority_queue.empty())
    {
        std::pair<int, int> min_element = *priority_queue.begin();
        int vertex = min_element.second;
        priority_queue.erase(min_element);

        if (vertex_in_MST[vertex])
        {
            continue;
        }
        vertex_in_MST[vertex] = true;

        std::vector<std::pair<int, float>> edge_list = GetNextVertices(vertex);
        for (int i = 0; i < edge_list.size(); ++i)
        {
            std::pair<int, int> iteration_pair = edge_list[i]; // first - vertex, second - weight
            if ((vertex_in_MST[iteration_pair.first] == false) && (distance[iteration_pair.first] > iteration_pair.second))
            {
                distance[iteration_pair.first] = iteration_pair.second;
                priority_queue.insert(std::make_pair(distance[iteration_pair.first], iteration_pair.first));
                parent[iteration_pair.first] = vertex;
            }
        }
    }
    WeightedListGraph mst(VerticesCount());

    for (int i = 1; i < VerticesCount(); ++i)
    {
        mst.AddEdge(parent[i], i, GetWeight(parent[i], i));
        mst.AddEdge(i, parent[i], GetWeight(parent[i], i));
    }
    return mst;

}

size_t WeightedListGraph::GetMSTWeight()
{
    std::vector <float> distance;
    distance.resize(VerticesCount(), INT_MAX);
    int from = 0;
    distance[from] = 0;
    std::vector <int> parent;
    parent.resize(VerticesCount(), -1);
    std::vector<bool> vertex_in_MST;
    vertex_in_MST.resize(VerticesCount(), false);

    std::set<std::pair<int, float>> priority_queue;
    priority_queue.insert(std::make_pair(distance[from], from));

    while (!priority_queue.empty())
    {
        std::pair<int, float> min_element = *priority_queue.begin();
        int vertex = min_element.second;
        priority_queue.erase(min_element);

        if (vertex_in_MST[vertex])
        {
            continue;
        }
        vertex_in_MST[vertex] = true;

        std::vector<std::pair<int, float>> edge_list = GetNextVertices(vertex);
        for (int i = 0; i < edge_list.size(); ++i)
        {
            std::pair<int, float> iteration_pair = edge_list[i]; // first - vertex, second - weight
            if ((vertex_in_MST[iteration_pair.first] == false) && (distance[iteration_pair.first] > iteration_pair.second))
            {
                distance[iteration_pair.first] = iteration_pair.second;
                priority_queue.insert(std::make_pair(distance[iteration_pair.first], iteration_pair.first));
                parent[iteration_pair.first] = vertex;
            }
        }
    }
    WeightedListGraph mst(VerticesCount());
    float weight = 0;
    for (int i = 1; i < VerticesCount(); ++i)
    {
        weight += GetWeight(parent[i], i);

    }
    return weight;
}

std::vector<int> WeightedListGraph::DFS()
{
    std::vector<bool> visited(VerticesCount(), false);
    std::vector<int> vertex_list;
    vertex_list.push_back(0);
    DFS_Private(0, visited, vertex_list);

    return vertex_list;
}

void WeightedListGraph::DFS_Private(int vertex, std::vector<bool>& visited, std::vector<int>& vertex_list)
{
    visited[vertex] = true;

    std::vector<std::pair<int, float>> edge_list = GetNextVertices(vertex);
    for (int i = 0; i < edge_list.size(); ++i)
    {
        if (!visited[edge_list[i].first])
        {
            vertex_list.push_back(edge_list[i].first);
            DFS_Private(edge_list[i].first, visited, vertex_list);
        }
    }
}