#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include "Graph.hpp"
#include "ComplexNetwork.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream inFile;
	string inFileName, datasetName;
	Graph origNet;
	Graph verticPreprocGraph;
	Graph edgesPreProcGraph;
	int u, v,vertexMin,numEdges,topNDegrees;
	bool considerConCom;
	stringstream sStream;

	inFileName = argv[1];
	datasetName= argv[2];
	vertexMin = atoi(argv[3]);	
	numEdges = atoi(argv[4]);
	topNDegrees = atoi(argv[5]);
	inFile.open(inFileName.c_str());
	srand(time(NULL));
	string consid;
	if (inFile.is_open()) {
		while (inFile >> u >> v) {
			origNet.connectu(u,v);
		}
		cerr<<endl<<"====ORIGINAL NET===="<<endl;
		cerr<<"#Vertices: "<<origNet.getVerticesQnt()<<endl;
		cerr<<"#Edges: "<<origNet.getEdgesQnt()<<endl;
		cerr<<"Degree(2290) = " << origNet.getDegree(2290)<<endl;
		cerr<<"Density = "<<origNet.getDensity()<<endl;
		cerr<<"AVG Degree: "<<origNet.getAvgDegree()<<endl;
		cerr<<"#Connected Components "<< origNet.getNumberOfConnectedComponents()<<endl;
		
		

		verticPreprocGraph = origNet.removeVerticesLowDegree(vertexMin);

		verticPreprocGraph.writeToFile(datasetName+"_PreProc_Vert_"+".links");
		
		cerr<<endl<<"====PREPROC VERTICE===="<<endl;
		cerr<<"#Vertices: "<<verticPreprocGraph.getVerticesQnt()<<endl;
		cerr<<"#Edges: "<<verticPreprocGraph.getEdgesQnt()<<endl;
		cerr<<"Degree(2290) = " << verticPreprocGraph.getDegree(2290)<<endl;
		cerr<<"Density = "<<verticPreprocGraph.getDensity()<<endl;
		cerr<<"AVG Degree: "<<verticPreprocGraph.getAvgDegree()<<endl;
		cerr<<"#Connected Components "<< verticPreprocGraph.getNumberOfConnectedComponents()<<endl;
		cout<<endl;
		edgesPreProcGraph = origNet.removeEdgesFromHighDegreeVertices(numEdges,topNDegrees);
		cerr<<endl<<"====PREPROC ARESTA===="<<endl;
		cerr<<"#Vertices: "<<edgesPreProcGraph.getVerticesQnt()<<endl;
		cerr<<"#Edges: "<<edgesPreProcGraph.getEdgesQnt()<<endl;
		cerr<<"Degree(2290) = " << edgesPreProcGraph.getDegree(2290)<<endl;
		cerr<<"Density = "<<edgesPreProcGraph.getDensity()<<endl;
		cerr<<"AVG Degree: "<<edgesPreProcGraph.getAvgDegree()<<endl;
		cerr<<"#Connected Components "<< edgesPreProcGraph.getNumberOfConnectedComponents()<<endl;
		edgesPreProcGraph.writeToFile(datasetName+"_PreProc_Edge_"+".links");
	
		cout<<endl;

		
		inFile.close();

	}

	return 0;
}