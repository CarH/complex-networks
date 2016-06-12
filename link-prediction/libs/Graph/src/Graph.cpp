#include "Graph/include/Graph.hpp"

using namespace std;
Graph::Graph() {
	this->numEdges=0;
}
Graph::~Graph() {}
void Graph::connect(int u, int v) {
	this->adjList[u].insert(v);
	this->vertices.insert(u);
	this->vertices.insert(v);
}
void Graph::connectu(int u, int v) {
	this->connect(u,v);
	this->connect(v,u);
	this->numEdges++;
}
int Graph::getDegree(int u) {
	return this->adjList[u].size();
}
double Graph::getDensity() {
	double numPossibleEdges = (this->vertices.size()*(this->vertices.size()-1))/2;
	return (double) this->numEdges / numPossibleEdges;
}
double Graph::getAvgDegree() {
	int degCnt=0;
	for (int i=0; i<N; i++) {
		if (!(this->adjList[i].empty())) {
			degCnt += this->adjList[i].size();
		}
	}
	return degCnt/(double)this->vertices.size();
}
std::set<int> Graph::getAdjList(int u) {
	return this->adjList[u];
}
std::set<int> Graph::getVertices(){
	return this->vertices;
}
int Graph::getVerticesQnt(){
	return this->vertices.size();
}
int Graph::getEdgesQnt(){
	int count=0;
	for(set<int>::iterator it=this->vertices.begin();it!=this->vertices.end();it++){
		count+=this->getDegree(*it);
	}
	return count/2;
}


Graph Graph::removeVerticesLowDegree(int d){
	set<int> verticesToRemove;
	for(set<int>::iterator it=this->vertices.begin();it!=this->vertices.end();it++){
		if(this->getDegree(*it)<=d){
			verticesToRemove.insert(*it);
		}
	}
	Graph resultingGraph = *(this); //espero que esteja fazendo uma copia, e nao referenciando
	for(set<int>::iterator it=verticesToRemove.begin();it!=verticesToRemove.end();it++){
		int v=*it;
		resultingGraph.adjList[v].clear();
		resultingGraph.vertices.erase(v);
		for(set<int>::iterator it2=this->vertices.begin();it2!=this->vertices.end();it2++){
			resultingGraph.adjList[*it2].erase(v);
		}
		
	}
	resultingGraph.numEdges = resultingGraph.getEdgesQnt();
	return resultingGraph;
}
