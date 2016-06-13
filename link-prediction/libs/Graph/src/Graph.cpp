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
	if (!this->adjList[u].count(v) && !this->adjList[v].count(u)) {
		this->connect(u,v);
		this->connect(v,u);
		this->numEdges++;
	}
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
	for (set<int>::iterator vit = this->vertices.begin(); vit != this->vertices.end(); vit++) {
		degCnt += this->adjList[*vit].size();
	}
	return degCnt/(double)this->vertices.size();
}
std::set<int> Graph::getAdjList(int u) {
	return this->adjList[u];
}
std::set<int> Graph::getVertices(){
	return this->vertices;
}
int Graph::getTotalVertices() {
	return this->vertices.size();
}