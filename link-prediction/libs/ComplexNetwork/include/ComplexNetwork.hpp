#ifndef __COMPLEX_NETWORK_HPP__
#define __COMPLEX_NETWORK_HPP__
	
// Forward declared dependencies

// Included dependencies
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include "Graph.hpp"

class ComplexNetwork
{
	private:
		Graph *net;
		std::map<int, std::vector<int> > degreeVerticesMap;
		void buildDegreeVerticesMap();
	public:
		ComplexNetwork(Graph &g);
		~ComplexNetwork();
		/**
		 * Common Neighbors
		 * @param  u [description]
		 * @param  v [description]
		 * @return   the number of common neighbors between u and v
		 */
		int CN(int u, int v);

		/**
		 * Jaccard's Coefficient
		 * @param  u [description]
		 * @param  v [description]
		 * @return   (# of common neighbors between u an v) / (SUM of # neighbors of u AND v)
		 */
		double jaccardCoefficient(int u, int v);

		/**
		 * Common Neighbors Nodes
		 * @param  u [description]
		 * @param  v [description]
		 * @return   the index of common neighbors
		 */
		std::set<int> CN_Nodes(int u, int v);

		/**
		 * Adamic-Adar's Coefficient
		 * @param  u [description]
		 * @param  v [description]
		 * @return   SUM (1/(# degree of common neighbor))
		 */
		
		double adamicAdarCoefficient(int u, int v);

		/**
		 * Local Clustering Coefficient
		 * @param  u [description]
		 * @return   #triangles/#tripplets
		 */
		
		double localClusteringCoefficient(int u);

		/**
		 * Global Clustering Coefficient
		 * @param  u [description]
		 * @return   3*#triangles/#tripplets
		 */
		
		double globalClusteringCoefficient();

		/**
		 * Number of tripplets that vertex u participates
		 * @param  u [description]
		 * @return   (1/2)*degree(u)*(degree(u)-1)
		 */
		int getTrippletsNumber(int u);
		/**
		 * Number of tripplets that vertex u participates
		 * @param  u [description]
		 * @return  # triangles
		 */
		int getTrianglesNumber(int u);

		/**
		 * @return map < degree, frequency >
		 */
		std::map<int, int> getDegreeHistogram();
		
		/**
		 * @return map < degree, percentage >
		 */
		std::map<int, float> getDegreeDistribution();

		std::map<int, int> getVertexDegreeList();

		void printVertexDegreeList();

		void printVertexDegreeList(std::string filename, std::string suffix=std::string("out"));

		void printDegreeDistribution();

		void printDegreeDistribution(std::string filename, std::string suffix=std::string("out"));

		void printDegreeHistogram();

		void printDegreeHistogram(std::string filename, std::string suffix=std::string("out"));
};

#endif