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