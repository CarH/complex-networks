#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Graph.hpp"
#include "ComplexNetwork.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream inFile;
	string inFileName;
	Graph origNet;
	int u, v;

	inFileName = argv[1];
	inFile.open(inFileName.c_str());
	if (inFile.is_open()) {
		while (inFile >> u >> v) {
			// cerr << u << " -> " << v << "\n";
			origNet.connectu(u,v);
		}
		cerr<<"Degree(2290) = " << origNet.getDegree(2290)<<endl;
		cerr<<"Density = "<<origNet.getDensity()<<endl;
		cerr<<"AVG Degree: "<<origNet.getAvgDegree()<<endl;
		// cerr<<"Commmon Neighbors (2090, 2025): "<<
		inFile.close();
	}

	return 0;
}