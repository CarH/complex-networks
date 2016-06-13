#include "ComplexNetwork/include/ComplexNetwork.hpp"
using namespace std;

ComplexNetwork::ComplexNetwork(Graph &g) {
	this->net = new Graph();
	*(this->net) = g;
	buildDegreeVerticesMap();
}
ComplexNetwork::~ComplexNetwork() {
	delete this->net;
}
int ComplexNetwork::CN(int u, int v) {
	std::set<int> uNeighbors = this->net->getAdjList(u);
	std::set<int> vNeighbors = this->net->getAdjList(v);
	int cnt=0;
	
	for (std::set<int>::iterator it = vNeighbors.begin(); it != vNeighbors.end(); it++)
		if (uNeighbors.count(*it)!=0)
			cnt++;
	
	return cnt;
}
 
set<int> ComplexNetwork::CN_Nodes(int u, int v) {
	// std::vector<int> uNeighbors = this->net->getAdjList(u);
	// std::vector<int> vNeighbors = this->net->getAdjList(v);
	std::set<int> uNeighbors = this->net->getAdjList(u);
	std::set<int> vNeighbors = this->net->getAdjList(v);
	std::set<int> result;
	
	// To be able to perform binary_search
	// sort(uNeighbors.begin(), uNeighbors.end());

	// Test if they are already connected => jaccardCoefficient = 0	
	// if (binary_search(uNeighbors.begin(), uNeighbors.end(), v)) {
	
	for (std::set<int>::iterator it = vNeighbors.begin(); it != vNeighbors.end(); it++) {
		// if (binary_search(uNeighbors.begin(), uNeighbors.end(), *it))
		if (uNeighbors.count(*it)!=0)
			result.insert(*it);
	}
	return result;


}

double ComplexNetwork::jaccardCoefficient(int u, int v) {
	if (this->net->getAdjList(u).count(v))
		return 0; /// We want to avoid create links between nodes already connected
	return this->CN(u,v)/(double)(this->net->getAdjList(u).size() + this->net->getAdjList(v).size());
}

void ComplexNetwork::buildDegreeVerticesMap() {
	if (this->degreeVerticesMap.empty()) {
		set<int> vertices = this->net->getVertices();
		for (std::set<int>::iterator vit = vertices.begin(); vit != vertices.end(); vit++) {
			this->degreeVerticesMap[this->net->getDegree(*vit)].push_back(*vit);
		}
	}
}

std::map<int, int> ComplexNetwork::getDegreeHistogram() {
	std::map<int, int> degreeHistogram;
	if (!this->degreeVerticesMap.empty()) {
		for (std::map<int, std::vector<int> >::iterator it=this->degreeVerticesMap.begin(); it != this->degreeVerticesMap.end(); it++) {
			degreeHistogram[it->first] = it->second.size();
		}
	}
	return degreeHistogram;
}

std::map<int, float> ComplexNetwork::getDegreeDistribution() {
	map<int, float> degreeDist;
	if (!this->degreeVerticesMap.empty()) {
		for (std::map<int, std::vector<int> >::iterator it=this->degreeVerticesMap.begin(); it != this->degreeVerticesMap.end(); it++) {
			degreeDist[it->first] = it->second.size()/(float)this->net->getTotalVertices();
		}
	}
	return degreeDist;
}

std::map<int, int> ComplexNetwork::getVertexDegreeList() {
	std::map<int, int> vertexDegreeList;
	if (!this->degreeVerticesMap.empty()) {
		set<int> vertices = this->net->getVertices();
		for (std::set<int>::iterator vit = vertices.begin(); vit != vertices.end(); vit++) {
			vertexDegreeList[*vit] = this->net->getDegree(*vit);
		}
	}
	return vertexDegreeList;
}

void ComplexNetwork::printVertexDegreeList() {
	map<int, int> list = getVertexDegreeList();
	for (map<int, int>::iterator it = list.begin(); it != list.end(); it++)
		cout << it->first << " " << it->second << "\n";
}

void ComplexNetwork::printVertexDegreeList(std::string filename, std::string suffix) {
	ofstream outFile;
	string outFilename = filename + "." + suffix;
	map<int, int> list = getVertexDegreeList();

	outFile.open(outFilename.c_str());
	if (outFile.is_open()) {
		for (map<int, int>::iterator it = list.begin(); it != list.end(); it++)
			outFile << it->first << " " << it->second << "\n";
		outFile.close();
	}
	else {
		cerr << "ERROR: Output File could not be created: " << outFilename << "\n";
	}
}

void ComplexNetwork::printDegreeDistribution() {
	map<int, float> list = getDegreeDistribution();
	for (map<int, float>::iterator it = list.begin(); it != list.end(); it++)
		cout << it->first << " " << it->second << "\n";
}

void ComplexNetwork::printDegreeDistribution(std::string filename, std::string suffix) {
	ofstream outFile;
	map<int, float> list = getDegreeDistribution();
	string outFilename = filename + "." + suffix;

	outFile.open(outFilename.c_str());
	if (outFile.is_open()) {
		for (map<int, float>::iterator it = list.begin(); it != list.end(); it++)
			outFile << it->first << " " << it->second << "\n";
		outFile.close();
	}
	else {
		cerr << "ERROR: Output File could not be created: " << outFilename << "\n";
	}
}

void ComplexNetwork::printDegreeHistogram() {
	map<int, int> list = getDegreeHistogram();
	for (map<int, int>::iterator it = list.begin(); it != list.end(); it++)
		cout << it->first << " " << it->second << "\n";
}

void ComplexNetwork::printDegreeHistogram(std::string filename, std::string suffix) {
	ofstream outFile;
	map<int, int> list = getDegreeHistogram();
	string outFilename = filename + "." + suffix;

	outFile.open(outFilename.c_str());
	if (outFile.is_open()) {
		for (map<int, int>::iterator it = list.begin(); it != list.end(); it++)
			outFile << it->first << " " << it->second << "\n";
		outFile.close();
	}
	else {
		cerr << "ERROR: Output File could not be created: " << outFilename << "\n";
	}
}


double ComplexNetwork::adamicAdarCoefficient(int u, int v){
	std::set<int> commonNeighbors = this->CN_Nodes(u,v);
	commonNeighbors.erase(u);
	commonNeighbors.erase(v);
	double coefficient = 0;
	for(set<int>::iterator it = commonNeighbors.begin();it!=commonNeighbors.end();it++){
		int degree=this->net->getDegree(*it);//Note to self: degree is never gonna be 0, because it is already a common neighbor
		coefficient+=1.0/(log10(degree));
	}
	return coefficient;
}
int ComplexNetwork::getTrippletsNumber(int u){
	int degree = this->net->getDegree(u);
	return (degree*(degree-1))/2;
}

int ComplexNetwork::getTrianglesNumber(int u){
	int counter=0;
	set<int> uNeighbors = this->net->getAdjList(u);
	vector<int> intersection;
	//sejam i e j vizinhos de u, checar se eles estao ligados
	for(set<int>::iterator itI=uNeighbors.begin();itI!=uNeighbors.end();itI++){
		int i = *itI;
		intersection.clear();
		set<int> iNeighbors = this->net->getAdjList(i);
		// set_intersection(iNeighbors.begin(),iNeighbors.end(),uNeighbors.begin(),uNeighbors.end(),intersection.begin());
		// counter+=intersection.size()-2;//aqui esta contando duas vezes //retira 2 pq u esta contando
		for(set<int>::iterator itJ=itI;itJ!=uNeighbors.end();itJ++){//pegando outros vizinhos de u
			int j = *itJ;
			// if(binary_search(iNeighbors.begin(), iNeighbors.end(),j)){//checa se j eh vizinho de i
			if(iNeighbors.count(j)>0){//checa se j eh vizinho de i
				counter++;
			}
		}	
	}
	return counter;
	// return counter/2;

}

double ComplexNetwork::localClusteringCoefficient(int u){
	int triangles = this->getTrianglesNumber(u);
	int tripplets = this->getTrippletsNumber(u);
	return (tripplets!=0) ? ((double)triangles)/((double) tripplets):0;
}
double ComplexNetwork::globalClusteringCoefficient(){
	
	double localTriangles=0;
	double localTripplets=0;
	set<int> vertices = this->net->getVertices();
	for(set<int>::iterator it = vertices.begin();it!=vertices.end();it++){
		localTriangles += this->getTrianglesNumber(*it);//3*(getTrianglesNumber/3)
		localTripplets += this->getTrippletsNumber(*it);
		
	}
	return localTriangles/localTripplets;
}