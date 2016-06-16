#include "Graph/include/Graph.hpp"
using namespace std;

using namespace std;
Graph::Graph() {
	this->numEdges=0;
	this->maxDegree=-INT_MAX;
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

int Graph::getMaxDegree() {
	for (set<int>::iterator vit = this->vertices.begin(); vit != this->vertices.end(); vit++) {
		this->maxDegree = ((int)this->adjList[*vit].size() > this->maxDegree) ? this->adjList[*vit].size() : this->maxDegree;
	}
	return this->maxDegree;
}

double Graph::getDensity() {
	double numPossibleEdges = (this->vertices.size()*(this->vertices.size()-1))/2;
	return (double) this->numEdges / numPossibleEdges;
}
double Graph::getAvgDegree() {
	int degCnt=0;
	for (set<int>::iterator vit = this->vertices.begin(); vit != this->vertices.end(); vit++) {
		degCnt += this->adjList[*vit].size();
		this->maxDegree = (this->adjList[*vit].size() > this->maxDegree) ? this->adjList[*vit].size() : this->maxDegree;
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

Graph Graph::removeEdgesFromHighDegreeVertices(int numEdges,int topNDegrees){
	
	vector<pair<int,int> > degrees;

	for(set<int>::iterator it=this->vertices.begin();it!=this->vertices.end();it++){
		degrees.push_back(make_pair(*it,this->getDegree(*it)));
	}
	sort(degrees.begin(),degrees.end(),ComparisonDegree());
	Graph resultingGraph = *(this);
	int n=0;
	

	for(vector<pair<int,int> >::iterator it=degrees.begin();it!=degrees.end() && n<topNDegrees;it++,n++){
		int u = it->first;
		for(int i=0;i<numEdges && resultingGraph.adjList[u].size()>0;i++){
			int edgeToRemoveIndex = rand()%resultingGraph.adjList[u].size();
			// resultingGraph.adjList[u].erase(resultingGraph.adjList[u].begin()+edgeToRemoveIndex);
			set<int>::iterator pointerToItemToBeRemoved = resultingGraph.adjList[u].begin();
			for(int k=0;k<edgeToRemoveIndex;k++){
				pointerToItemToBeRemoved++;
			}
			resultingGraph.adjList[u].erase(pointerToItemToBeRemoved);
		}
	}
	resultingGraph.numEdges = resultingGraph.getEdgesQnt();
	return resultingGraph;
}

Graph Graph::getEdgeSample(double percentage,std::set<std::pair<int,int> > &edgesRemoved){
	Graph sampleGraph;
	vector<pair<int,int> > remainingEdges;
	int numberOfEdgesToRemove = ceil(((double)this->getEdgesQnt())*(1.0-percentage));
	
	edgesRemoved.clear();
	for(set<int>::iterator it=this->vertices.begin();it!=this->vertices.end();it++){
		int u= *it;
		sampleGraph.createVertex(u);
		for(set<int>::iterator it2=this->adjList[u].begin();it2!=this->adjList[u].end();it2++){
			int v=*it2;
			if(v>u){
				remainingEdges.push_back(make_pair(u,v));
			}
		}
	}
	for(int i=0;i<numberOfEdgesToRemove;i++){
		int p = rand() % remainingEdges.size();
		edgesRemoved.insert(remainingEdges[p]);
		remainingEdges.erase(remainingEdges.begin()+p);
	}
	for(vector<pair<int,int> >::iterator it = remainingEdges.begin();it!=remainingEdges.end();it++){
		sampleGraph.connectu(it->first,it->second);
	}
	return sampleGraph;
}
void Graph::createVertex(int u){
	this->vertices.insert(u);
}


void Graph::writeToFile(string fileName){
	fstream file;

	file.open(fileName.c_str(),fstream::out);
	if(file.is_open()) {
		for(set<int>::iterator it=this->vertices.begin();it!=this->vertices.end();it++){
			int u= *it;
			for(set<int>::iterator it2=this->adjList[u].begin();it2!=this->adjList[u].end();it2++){
				int v=*it2;
				if(v>u){
					file<<u<<"\t"<<v<<endl;
				}
			}
		}
		file.close();
	}else{
		cerr<<"ERROR: Could not open file for writting: "<<fileName<<endl;
	}
}
