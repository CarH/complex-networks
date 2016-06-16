#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__
	
	// Dependencies
	#include <vector>
	#include <set> 
	#include <cstdlib>
	#include <cmath>
	#include <climits>
	#include <algorithm>
	#include <fstream>
	#include <string>
	#include <iostream>
	
	const int N = 20000;
	class ComparisonDegree{
		public:
			bool operator() (const std::pair<int,int> &lhs,const std::pair<int,int> &rhs){
				return lhs.second > rhs.second;
			}
	};

	class Graph {
		private:
			int v;
			int maxDegree;
			int numEdges;
			std::set<int> vertices; // Segestoes sao bem vindas aqui
			std::set<int> adjList[N];
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
			int getTotalVertices();
			double getDensity();
			void createVertex(int u);
			double getAvgDegree();
			std::set<int> getAdjList(int u);
			std::set<int> getVertices();

			/**
			 * Remove Verticer with degree lower or equal than d
			 * @param  d degree
			 * @return   The new graph without the vertices with degree lower or equal than d
			 */
			Graph removeVerticesLowDegree(int d=0);

			Graph removeEdgesFromHighDegreeVertices(int numEdges=1,int topNDegrees=3);
			
			int getVerticesQnt();
			int getEdgesQnt();


			Graph getEdgeSample(double percentage,std::set<std::pair<int,int> > &edgesRemoved);

			void writeToFile(std::string fileName);

			int getMaxDegree();
	};
#endif