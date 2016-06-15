#ifndef __COMPLEX_NETWORK_HPP__
#define __COMPLEX_NETWORK_HPP__
	
	// Forward declared dependencies

	// Included dependencies
	#include <algorithm>
	#include <iostream>
	#include <fstream>
	#include <vector>
	#include <string>
	#include <cmath>
	#include <map>
	#include <set>
	#include "Graph.hpp"
	
	#define PREDICTOR_CN 1
	#define PREDICTOR_ADAMIC_ADAR 2

	class ComparisonPredictors{
		public:
			bool operator() (const std::pair<std::pair<int,int>,double> &lhs,const std::pair<std::pair<int,int>,double> &rhs){
				return lhs.second > rhs.second;
			}
	};
	// class ComparisonAdamic : ComparisonPredictors{
	// 	public:
	// 		bool operator() (const std::pair<std::pair<int,int>,double> &lhs,const std::pair<std::pair<int,int>,double> &rhs){
	// 			return lhs.second > rhs.second;
	// 		}
	// };
	class ComplexNetwork
	{
		private:
			Graph *net;
			std::vector<double> triangles;
			std::vector<double> tripplets;
			std::map<int, std::vector<int> > degreeVerticesMap;
			std::map<int, double > localClusteringCoeffPerNode;
			std::map<double,std::vector<int> > localClusteringCoeffMap;

			void buildDegreeVerticesMap();
			void buildlocalClusteringCoeffPerNode();
			void buildlocalClusteringCoeffMap();
			// std::map<std::pair<int,int>,double> adamicAdar;//adamicAdar is alwyas >=0
			
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
			 * Common Neighbors for all pairs
			 * @param  u [description]
			 * @param  v [description]
			 * @return   vector with each pair of node and their CN 
			 */
			std::vector<std::pair<std::pair<int,int>,double> > CNAll();

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
			 * Adamic-Adar's Coefficient of all pairs
			 * @return   vector containing the coefficients of all pairs
			 */
			
			std::vector<std::pair<std::pair<int,int>,double> > adamicAdarAll();

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
			 * [linkPrediction description]
			 * @param predictor    Constant representing the predictor. 
			 * @param edgesToCheck edges removed when building training set.
			 * @param K  K represents that this method will compare edgesToCheck with the K top pairs
			 */
			void linkPrediction(int predictor,std::set<std::pair<int,int> > &edgesToCheck,int K);


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