#ifndef __COMPLEX_NETWORK_HPP__
#define __COMPLEX_NETWORK_HPP__
	
	// Forward declared dependencies
	// class Graph;

	// Included dependencies
	#include <algorithm>
	#include "Graph.hpp"

	class ComplexNetwork
	{
		private:
			Graph *net;
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
	};

#endif