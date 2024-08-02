#include <iostream>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"

void TestSolution()
{
	{
		std::stringstream output;
		ListGraph g(9);
		g.AddEdge(0, 1);
		g.AddEdge(0, 2);
		g.AddEdge(0, 3);
		g.AddEdge(1, 6);
		g.AddEdge(2, 3);
		g.AddEdge(2, 4);
		g.AddEdge(4, 3);
		g.AddEdge(4, 7);
		g.AddEdge(5, 7);
		g.AddEdge(5, 8);
		g.AddEdge(6, 5);
		g.AddEdge(6, 8);
		g.AddEdge(7, 8);
		
		BFS(g, 0, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "0 1 2 3 6 4 5 8 7 ");

		output.str("");
		BFS(g, 1, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "1 6 5 8 7 ");

		output.str("");
		BFS(g, 2, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "2 3 4 7 8 ");

		output.str("");
		BFS(g, 3, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "3 ");

		MatrixGraph g1(g);
		output.str("");
		BFS(g1, 0, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "0 1 2 3 6 4 5 8 7 ");

		SetGraph g2(g);
		output.str("");
		BFS(g2, 0, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "0 1 2 3 6 4 5 8 7 ");

		ArcGraph g3(g);
		output.str("");
		BFS(g3, 0, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "0 1 2 3 6 4 5 8 7 ");
	}

	{
		std::stringstream output;
		MatrixGraph g(9);
		g.AddEdge(0, 1);
		g.AddEdge(0, 2);
		g.AddEdge(0, 3);
		g.AddEdge(1, 6);
		g.AddEdge(2, 3);
		g.AddEdge(2, 4);
		g.AddEdge(4, 3);
		g.AddEdge(4, 7);
		g.AddEdge(5, 7);
		g.AddEdge(5, 8);
		g.AddEdge(6, 5);
		g.AddEdge(6, 8);
		g.AddEdge(7, 8);

		BFS(g, 0, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "0 1 2 3 6 4 5 8 7 ");

		output.str("");
		BFS(g, 1, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "1 6 5 8 7 ");

		output.str("");
		BFS(g, 2, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "2 3 4 7 8 ");

		output.str("");
		BFS(g, 3, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "3 ");

		ListGraph g1(g);
		output.str("");
		BFS(g1, 0, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "0 1 2 3 6 4 5 8 7 ");

		SetGraph g2(g);
		output.str("");
		BFS(g2, 0, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "0 1 2 3 6 4 5 8 7 ");

		ArcGraph g3(g);
		output.str("");
		BFS(g3, 0, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "0 1 2 3 6 4 5 8 7 ");
	}

	{
		std::stringstream output;
		SetGraph g(9);
		g.AddEdge(0, 1);
		g.AddEdge(0, 2);
		g.AddEdge(0, 3);
		g.AddEdge(1, 6);
		g.AddEdge(2, 3);
		g.AddEdge(2, 4);
		g.AddEdge(4, 3);
		g.AddEdge(4, 7);
		g.AddEdge(5, 7);
		g.AddEdge(5, 8);
		g.AddEdge(6, 5);
		g.AddEdge(6, 8);
		g.AddEdge(7, 8);

		BFS(g, 0, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "0 1 2 3 6 4 5 8 7 ");

		output.str("");
		BFS(g, 1, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "1 6 5 8 7 ");

		output.str("");
		BFS(g, 2, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "2 3 4 7 8 ");

		output.str("");
		BFS(g, 3, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "3 ");

		MatrixGraph g1(g);
		output.str("");
		BFS(g1, 0, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "0 1 2 3 6 4 5 8 7 ");

		ListGraph g2(g);
		output.str("");
		BFS(g2, 0, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "0 1 2 3 6 4 5 8 7 ");

		ArcGraph g3(g);
		output.str("");
		BFS(g3, 0, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "0 1 2 3 6 4 5 8 7 ");
	}

	{
		std::stringstream output;
		ArcGraph g(9);
		g.AddEdge(0, 1);
		g.AddEdge(0, 2);
		g.AddEdge(0, 3);
		g.AddEdge(1, 6);
		g.AddEdge(2, 3);
		g.AddEdge(2, 4);
		g.AddEdge(4, 3);
		g.AddEdge(4, 7);
		g.AddEdge(5, 7);
		g.AddEdge(5, 8);
		g.AddEdge(6, 5);
		g.AddEdge(6, 8);
		g.AddEdge(7, 8);

		BFS(g, 0, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "0 1 2 3 6 4 5 8 7 ");

		output.str("");
		BFS(g, 1, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "1 6 5 8 7 ");

		output.str("");
		BFS(g, 2, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "2 3 4 7 8 ");

		output.str("");
		BFS(g, 3, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "3 ");

		MatrixGraph g1(g);
		output.str("");
		BFS(g1, 0, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "0 1 2 3 6 4 5 8 7 ");

		SetGraph g2(g);
		output.str("");
		BFS(g2, 0, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "0 1 2 3 6 4 5 8 7 ");

		ListGraph g3(g);
		output.str("");
		BFS(g3, 0, output, [](int vertex, std::ostream& output) {output << vertex << " "; });
		assert(output.str() == "0 1 2 3 6 4 5 8 7 ");
	}
}

int main()
{
	TestSolution();

	return 0;
}