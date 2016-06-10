#include <vector>
#include <set> 

#ifndef __GRAPH_H__
	#define __GRAPH_H__
		const int N = 20000;
		class Graph {
			private:
				int v;
				int numEdges;
				std::set<int> vertices; // Segestoes sao bem vindas aqui
				std::vector<int> adjList[N];
			public:
				Graph();
				~Graph();
				/**
				 * Creates an edge in the direction u->v
				 * @param u source
				 * @param v destination
				 */
				void connect(int u, int v);

				/**
				 * Create an edge in both directions - undirected graphs
				 * @param u vertice to be connected
				 * @param v vertice to be connected
				 */
				void connectu(int u, int v);
				int getDegree(int u);
				double getDensity();
				double getAvgDegree();
		};
	#endif