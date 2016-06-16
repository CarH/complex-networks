#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "Graph.hpp"
#include "ComplexNetwork.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream inFile;
	ifstream inFileEdgesRemoved;
	string inFileName, datasetName, edgesRemovedSuffix;
	Graph origNet;
	Graph edgesRemovedGraph;
	ComplexNetwork *compNet;
	string filePath;




	int u, v;
	set<pair<int,int> > edgesRemoved;

	inFileName = argv[1];
	datasetName= argv[2];
	edgesRemovedSuffix="_edgesRemoved.links";


	int found = inFileName.find_last_of("/");
  	filePath =  inFileName.substr(0,found);


	string edgesRemovedFileName = filePath+"/"+datasetName+edgesRemovedSuffix;
	inFileEdgesRemoved.open(edgesRemovedFileName.c_str());
	if(inFileEdgesRemoved.is_open()){
		while (inFileEdgesRemoved >> u >> v) {
			edgesRemovedGraph.connectu(u,v);
		}

		inFileEdgesRemoved.close();

		edgesRemoved=edgesRemovedGraph.getEdgesInPairs();
	}else{
		cerr<<"ERROR: Could not open "<<edgesRemovedFileName<<endl;
		edgesRemoved.clear();
	}

	inFile.open(inFileName.c_str());
	if (inFile.is_open()) {
		while (inFile >> u >> v) {
			origNet.connectu(u,v);
		}
		
		//DEBUG
		set<pair<int,int> > origEdgesInPairs = origNet.getEdgesInPairs();
		for(set<pair<int,int> >::iterator it= edgesRemoved.begin();it!=edgesRemoved.end();it++){
			pair<int,int> p2 = pair<int,int>(it->second,it->first);
			if (origEdgesInPairs.count(*it)>0 || origEdgesInPairs.count(p2)>0){
				cerr<<"ERROR: edges removed overlap"<<endl;
				exit(EXIT_FAILURE);
			}
		}
		//FIM DEBUG
		compNet = new ComplexNetwork(origNet);
		
		cout<<"====ORIGINAL NET===="<<endl;
		cout<<"#Vertices: "<<origNet.getVerticesQnt()<<endl;
		cout<<"#Edges: "<<origNet.getEdgesQnt()<<endl;
		cout<<"AVG Degree: "<<origNet.getAvgDegree()<<endl;
		cout<<"Density = "<<origNet.getDensity()<<endl;
		cout<<"Global Clust() = " << compNet->globalClusteringCoefficient()<<endl;
		cerr<<"#Connected Components "<< origNet.getNumberOfConnectedComponents()<<endl;

		compNet->calculatePredictorsBuffers();
		// Generate reports to original network
		compNet->printVertexDegreeList("VertexDegreeList_"+datasetName);
		compNet->printDegreeDistribution("DegreeDistribution_"+datasetName);
		compNet->printDegreeHistogram("DegreeHistogram_"+datasetName);
		compNet->printLocalClustHistogram("LocalClustHistogram_"+datasetName);
		compNet->printPredictorsBuffer("Predictors_"+datasetName);

		
		//100 300 500 1000
		cout<<"JACCARD "<<endl;
		compNet->linkPrediction(PREDICTOR_JACCARD,edgesRemoved,100);
		cout<<endl;
		compNet->linkPrediction(PREDICTOR_JACCARD,edgesRemoved,300);
		cout<<endl;
		compNet->linkPrediction(PREDICTOR_JACCARD,edgesRemoved,500);
		cout<<endl;
		compNet->linkPrediction(PREDICTOR_JACCARD,edgesRemoved,1000);
		cout<<endl;
		cout<<"CN "<<endl;
		compNet->linkPrediction(PREDICTOR_CN,edgesRemoved,100);
		cout<<endl;
		compNet->linkPrediction(PREDICTOR_CN,edgesRemoved,300);
		cout<<endl;
		compNet->linkPrediction(PREDICTOR_CN,edgesRemoved,500);
		cout<<endl;
		compNet->linkPrediction(PREDICTOR_CN,edgesRemoved,1000);
		cout<<endl;
		cout<<"Adamic"<<endl;
		compNet->linkPrediction(PREDICTOR_ADAMIC_ADAR,edgesRemoved,100);
		cout<<endl;
		compNet->linkPrediction(PREDICTOR_ADAMIC_ADAR,edgesRemoved,300);
		cout<<endl;
		compNet->linkPrediction(PREDICTOR_ADAMIC_ADAR,edgesRemoved,500);
		cout<<endl;
		compNet->linkPrediction(PREDICTOR_ADAMIC_ADAR,edgesRemoved,1000);
		
		cout<<endl;

		inFile.close();
		delete compNet;
	}

	return 0;
}