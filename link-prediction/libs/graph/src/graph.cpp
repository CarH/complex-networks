#include "graph/include/graph.hpp"

Graph::Graph() {
	this->numEdges=0;
}
Graph::~Graph() {}
void Graph::connect(int u, int v) {
	this->adjList[u].push_back(v);
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
