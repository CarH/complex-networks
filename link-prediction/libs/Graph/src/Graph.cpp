#include "Graph/include/Graph.hpp"

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
