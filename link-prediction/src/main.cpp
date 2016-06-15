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
		
		cout<<"====ORIGINAL NET===="<<endl;
		cout<<"#Vertices: "<<origNet.getVerticesQnt()<<endl;
		cout<<"#Edges: "<<origNet.getEdgesQnt()<<endl;
		// cout<<"Degree(2290) = " << origNet.getDegree(2290)<<endl;
		cout<<"AVG Degree: "<<origNet.getAvgDegree()<<endl;
		cout<<"Density = "<<origNet.getDensity()<<endl;
		// cout<<"Commmon Neighbors (2090, 2025): "<< compNet->CN(2090,2025)<<endl;
		// cout<<"Adamic-Adar (2090,2025): "<<compNet->adamicAdarCoefficient(2090,2025)<<endl;
		// cout<<"Local Clust.(2290) = " << compNet->localClusteringCoefficient(2290)<<endl;
		cout<<"Global Clust() = " << compNet->globalClusteringCoefficient()<<endl;


		// Generate reports to original network
		compNet->printVertexDegreeList("VertexDegreeList_"+datasetName);
		compNet->printDegreeDistribution("DegreeDistribution_"+datasetName);
		compNet->printDegreeHistogram("DegreeHistogram_"+datasetName);
		compNet->printLocalClustHistogram("LocalClustHistogram_"+datasetName);

		
		// cout<<"Common Neighbors Node(2090,2025): "
		
		// // preProcessNetLowDegree = origNet.removeVerticesLowDegree(1);
		// preProcessNetLowDegree = origNet.removeEdgesFromHighDegreeVertices(10,5);
		// // preProcessNetLowDegree.writeToFile(datasetName+"_PreProc.links");
		// compNetPreProc = new ComplexNetwork(preProcessNetLowDegree);
		// cout<<endl<<"====PREPROC NET===="<<endl;
		// cout<<"#Vertices: "<<preProcessNetLowDegree.getVerticesQnt()<<endl;
		// cout<<"#Edges: "<<preProcessNetLowDegree.getEdgesQnt()<<endl;
		// cout<<"Degree(2290) = " << preProcessNetLowDegree.getDegree(2290)<<endl;
		// cout<<"Density = "<<preProcessNetLowDegree.getDensity()<<endl;
		// cout<<"AVG Degree: "<<preProcessNetLowDegree.getAvgDegree()<<endl;
		// cout<<"Commmon Neighbors (2090, 2025): "<< compNetPreProc->CN(2090,2025)<<endl;
		// cout<<"Adamic-Adar (2090,2025): "<<compNetPreProc->adamicAdarCoefficient(2090,2025)<<endl;
		// cout<<"Local Clust.(2290) = " << compNetPreProc->localClusteringCoefficient(2290)<<endl;
		// cout<<"Global Clust.() = " << compNetPreProc->globalClusteringCoefficient()<<endl;

		// set<pair<int,int> > edgesRemoved;
		// trainingGraph = origNet.getEdgeSample(0.9,edgesRemoved);
		// // trainingGraph.writeToFile(datasetName+"_TrainingSample.links");
		// trainingNet = new ComplexNetwork(trainingGraph);
		// cout<<endl<<"====TRAINING NET===="<<endl;
		// cout<<"#Removed Edges: "<<edgesRemoved.size()<<endl;
		// cout<<"#Vertices: "<<trainingGraph.getVerticesQnt()<<endl;
		// cout<<"#Edges: "<<trainingGraph.getEdgesQnt()<<endl;
		// cout<<"Degree(2290) = " << trainingGraph.getDegree(2290)<<endl;
		// cout<<"Density = "<<trainingGraph.getDensity()<<endl;
		// cout<<"AVG Degree: "<<trainingGraph.getAvgDegree()<<endl;
		// cout<<"Commmon Neighbors (2090, 2025): "<< trainingNet->CN(2090,2025)<<endl;
		// cout<<"Adamic-Adar (2090,2025): "<<trainingNet->adamicAdarCoefficient(2090,2025)<<endl;
		// cout<<"Local Clust.(2290) = " << trainingNet->localClusteringCoefficient(2290)<<endl;
		// cout<<"Global Clust.() = " << trainingNet->globalClusteringCoefficient()<<endl;

		// // trainingNet->linkPrediction(PREDICTOR_ADAMIC_ADAR,edgesRemoved,100);
		// // trainingNet->linkPrediction(PREDICTOR_CN,edgesRemoved,10);
		cout<<endl;

		inFile.close();
		delete compNet;
		// delete compNetPreProc;
		// delete trainingNet;
	}

	return 0;
}