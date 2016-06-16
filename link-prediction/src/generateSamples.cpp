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
	Graph trainingGraph;
	Graph edgesRemovedGraph;
	int u, v,samplesNumber;
	bool considerConCom;
	stringstream sStream;

	inFileName = argv[1];
	datasetName= argv[2];	
	samplesNumber = atoi(argv[3]);
	considerConCom = atoi(argv[4]);
	inFile.open(inFileName.c_str());
	srand(time(NULL));
	string consid;
	consid = (considerConCom) ? "_keepCompConex":"";
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
		set<pair<int,int> > edgesRemoved;
		for(int i=0;i<samplesNumber;i++){
			sStream.clear();
			sStream.str("");
			sStream.precision(3);
			sStream.setf(ios::fixed);
			sStream<<i;
			edgesRemoved.clear();
			trainingGraph = origNet.getEdgeSample(0.9,edgesRemoved,considerConCom);
			edgesRemovedGraph = Graph();
			for(set<pair<int,int> >::iterator it=edgesRemoved.begin();it!=edgesRemoved.end();it++){
				edgesRemovedGraph.connectu(it->first,it->second);
			}
			trainingGraph.writeToFile(datasetName+"_TrainingSample_"+sStream.str()+consid+".links");
			edgesRemovedGraph.writeToFile(datasetName+"_TrainingSample_"+sStream.str()+consid+"_edgesRemoved.links");
			cerr<<endl<<"====TRAINING NET===="<<endl;
			cerr<<"#Removed Edges: "<<edgesRemoved.size()<<endl;
			cerr<<"#Vertices: "<<trainingGraph.getVerticesQnt()<<endl;
			cerr<<"#Edges: "<<trainingGraph.getEdgesQnt()<<endl;
			cerr<<"Degree(2290) = " << trainingGraph.getDegree(2290)<<endl;
			cerr<<"Density = "<<trainingGraph.getDensity()<<endl;
			cerr<<"AVG Degree: "<<trainingGraph.getAvgDegree()<<endl;
			cerr<<"#Connected Components "<< trainingGraph.getNumberOfConnectedComponents()<<endl;

			// trainingNet->linkPrediction(PREDICTOR_ADAMIC_ADAR,edgesRemoved,100);
			// trainingNet->linkPrediction(PREDICTOR_CN,edgesRemoved,10);
			cout<<endl;

		}
		
		inFile.close();

	}

	return 0;
}