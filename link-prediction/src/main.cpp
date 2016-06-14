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
	string inFileName, datasetName;
	Graph origNet;
	Graph preProcessNetLowDegree;
	Graph trainingGraph;
	ComplexNetwork *compNet;
	ComplexNetwork *compNetPreProc;
	ComplexNetwork *trainingNet;
	int u, v;

	inFileName = argv[1];
	datasetName= argv[2];
	inFile.open(inFileName.c_str());
	if (inFile.is_open()) {
		while (inFile >> u >> v) {
			origNet.connectu(u,v);
		}
		
		compNet = new ComplexNetwork(origNet);
		
		cerr<<"====ORIGINAL NET===="<<endl;
		cerr<<"#Vertices: "<<origNet.getVerticesQnt()<<endl;
		cerr<<"#Edges: "<<origNet.getEdgesQnt()<<endl;
		cerr<<"Degree(2290) = " << origNet.getDegree(2290)<<endl;
		cerr<<"Density = "<<origNet.getDensity()<<endl;
		cerr<<"AVG Degree: "<<origNet.getAvgDegree()<<endl;
		cerr<<"Commmon Neighbors (2090, 2025): "<< compNet->CN(2090,2025)<<endl;
		cerr<<"Adamic-Adar (2090,2025): "<<compNet->adamicAdarCoefficient(2090,2025)<<endl;
		cerr<<"Local Clust.(2290) = " << compNet->localClusteringCoefficient(2290)<<endl;
		cerr<<"Global Clust.() = " << compNet->globalClusteringCoefficient()<<endl;


		// Generate reports to original network
		compNet->printVertexDegreeList("VertexDegreeList_"+datasetName);
		compNet->printDegreeDistribution("DegreeDistribution_"+datasetName);
		compNet->printDegreeHistogram("DegreeHistogram_"+datasetName);

		
		// cerr<<"Common Neighbors Node(2090,2025): "
		
		// preProcessNetLowDegree = origNet.removeVerticesLowDegree(1);
		preProcessNetLowDegree = origNet.removeEdgesFromHighDegreeVertices(10,5);
		compNetPreProc = new ComplexNetwork(preProcessNetLowDegree);
		cerr<<endl<<"====PREPROC NET===="<<endl;
		cerr<<"#Vertices: "<<preProcessNetLowDegree.getVerticesQnt()<<endl;
		cerr<<"#Edges: "<<preProcessNetLowDegree.getEdgesQnt()<<endl;
		cerr<<"Degree(2290) = " << preProcessNetLowDegree.getDegree(2290)<<endl;
		cerr<<"Density = "<<preProcessNetLowDegree.getDensity()<<endl;
		cerr<<"AVG Degree: "<<preProcessNetLowDegree.getAvgDegree()<<endl;
		cerr<<"Commmon Neighbors (2090, 2025): "<< compNetPreProc->CN(2090,2025)<<endl;
		cerr<<"Adamic-Adar (2090,2025): "<<compNetPreProc->adamicAdarCoefficient(2090,2025)<<endl;
		cerr<<"Local Clust.(2290) = " << compNetPreProc->localClusteringCoefficient(2290)<<endl;
		cerr<<"Global Clust.() = " << compNetPreProc->globalClusteringCoefficient()<<endl;

		set<pair<int,int> > edgesRemoved;
		trainingGraph = origNet.getEdgeSample(0.9,edgesRemoved);
		trainingNet = new ComplexNetwork(trainingGraph);
		cerr<<endl<<"====TRAINING NET===="<<endl;
		cerr<<"#Removed Edges: "<<edgesRemoved.size()<<endl;
		cerr<<"#Vertices: "<<trainingGraph.getVerticesQnt()<<endl;
		cerr<<"#Edges: "<<trainingGraph.getEdgesQnt()<<endl;
		cerr<<"Degree(2290) = " << trainingGraph.getDegree(2290)<<endl;
		cerr<<"Density = "<<trainingGraph.getDensity()<<endl;
		cerr<<"AVG Degree: "<<trainingGraph.getAvgDegree()<<endl;
		cerr<<"Commmon Neighbors (2090, 2025): "<< trainingNet->CN(2090,2025)<<endl;
		cerr<<"Adamic-Adar (2090,2025): "<<trainingNet->adamicAdarCoefficient(2090,2025)<<endl;
		cerr<<"Local Clust.(2290) = " << trainingNet->localClusteringCoefficient(2290)<<endl;
		cerr<<"Global Clust.() = " << trainingNet->globalClusteringCoefficient()<<endl;

		// trainingNet->linkPrediction(PREDICTOR_ADAMIC_ADAR,edgesRemoved,100);
		// trainingNet->linkPrediction(PREDICTOR_CN,edgesRemoved,10);
		cout<<endl;

		inFile.close();
		delete compNet;
		delete compNetPreProc;
		delete trainingNet;
	}

	return 0;
}