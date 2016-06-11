#include "ComplexNetwork/include/ComplexNetwork.hpp"
using namespace std;

ComplexNetwork::ComplexNetwork(Graph &g) {
	this->net = new Graph();
	*(this->net) = g;
}
ComplexNetwork::~ComplexNetwork() {
	delete this->net;
}
int ComplexNetwork::CN(int u, int v) {
	std::vector<int> uNeighbors = this->net->getAdjList(u);
	std::vector<int> vNeighbors = this->net->getAdjList(v);
	int cnt=0;
	
	// To be able to perform binary_search
	sort(uNeighbors.begin(), uNeighbors.end());

	// Test if they are already connected => jaccardCoefficient = 0	
	if (binary_search(uNeighbors.begin(), uNeighbors.end(), v)) {
		return 0; ///// CHECK THIS SHIT
	}
	else {
		for (std::vector<int>::iterator it = vNeighbors.begin(); it != vNeighbors.end(); it++) {
			if (binary_search(uNeighbors.begin(), uNeighbors.end(), *it))
				cnt++;
		}
		return cnt;
	}
}

vector<int> ComplexNetwork::CN_Nodes(int u, int v) {
	std::vector<int> uNeighbors = this->net->getAdjList(u);
	std::vector<int> vNeighbors = this->net->getAdjList(v);
	std::vector<int> result;
	int cnt=0;
	
	// To be able to perform binary_search
	sort(uNeighbors.begin(), uNeighbors.end());

	// Test if they are already connected => jaccardCoefficient = 0	
	if (binary_search(uNeighbors.begin(), uNeighbors.end(), v)) {
		return result; ///// CHECK THIS SHIT
	}
	else {
		for (std::vector<int>::iterator it = vNeighbors.begin(); it != vNeighbors.end(); it++) {
			if (binary_search(uNeighbors.begin(), uNeighbors.end(), *it))
				result.push_back(*it);
		}
		return result;
	}
}

double ComplexNetwork::jaccardCoefficient(int u, int v) {
	return this->CN(u,v)/(double)(this->net->getAdjList(u).size() + this->net->getAdjList(v).size());
}

double ComplexNetwork::adamicAdarCoefficient(int u, int v){
	std::vector<int> commonNeighbors = this->CN_Nodes(u,v);
	double coefficient = 0;
	for(vector<int>::iterator it = commonNeighbors.begin();it!=commonNeighbors.end();it++){
		int degree=this->net->getDegree(*it);//Note to self: degree is never gonna be 0, because it is already a common neighbor
		coefficient+=1.0/(log10(degree));
	}
	return coefficient;
}