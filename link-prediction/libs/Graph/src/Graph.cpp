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
	
	int previousDeg=-1;
	for(vector<pair<int,int> >::iterator it=degrees.begin();it!=degrees.end() && n<topNDegrees;it++){
		int u = it->first;
		int currDeg= it->second;
		if(currDeg!=previousDeg){
			n++;
		}
		previousDeg=currDeg;
		for(int i=0;i<numEdges*0.01*resultingGraph.adjList[u].size() && resultingGraph.adjList[u].size()>0;i++){
			int edgeToRemoveIndex = rand()%resultingGraph.adjList[u].size();
			// resultingGraph.adjList[u].erase(resultingGraph.adjList[u].begin()+edgeToRemoveIndex);
			set<int>::iterator pointerToItemToBeRemoved = resultingGraph.adjList[u].begin();
			for(int k=0;k<edgeToRemoveIndex;k++){//GAMBS pra funcionar o iterador
				pointerToItemToBeRemoved++;
			}
			resultingGraph.removeEdgeu(u,*pointerToItemToBeRemoved);
		}
	}
	resultingGraph.numEdges = resultingGraph.getEdgesQnt();
	return resultingGraph;
}

Graph Graph::getEdgeSample(double percentage,std::set<std::pair<int,int> > &edgesRemoved,bool considerConnecComponents){
	Graph sampleGraph;
	set<pair<int,int> >  remainingEdges;
	vector<pair<int,int> > remainingEdgesToChoose;
	int numberOfEdgesToRemove = ceil(((double)this->getEdgesQnt())*(1.0-percentage));
	

	int connectedComponentOriginal=this->getNumberOfConnectedComponents();
	int connectedComponentLocal=0;
	// cerr<<"ORiginal Connectedd Components : "<<connectedComponentOriginal<<endl;
	cerr.flush();


	edgesRemoved.clear();
	for(set<int>::iterator it=this->vertices.begin();it!=this->vertices.end();it++){
		int u= *it;
		sampleGraph.createVertex(u);
		for(set<int>::iterator it2=this->adjList[u].begin();it2!=this->adjList[u].end();it2++){
			int v=*it2;
			if(v>u){
				remainingEdges.insert(make_pair(u,v));
			}
		}
	}
	remainingEdgesToChoose.clear();
	remainingEdgesToChoose.insert(remainingEdgesToChoose.end(),remainingEdges.begin(),remainingEdges.end());
	Graph auxGraph = *(this);
	for(int i=0;i<numberOfEdgesToRemove;i++){
		int p = rand() % remainingEdgesToChoose.size();
		
		// cerr<<"Remaining size :"<< remainingEdges.size()<<endl;
		// cerr<<"\t\tChosen["<<p<<"]  :"<< remainingEdges[p].first <<" "<< remainingEdges[p].second <<endl;
		if(considerConnecComponents){
			auxGraph.removeEdgeu(remainingEdgesToChoose[p].first,remainingEdgesToChoose[p].second);
			connectedComponentLocal=auxGraph.getNumberOfConnectedComponents();
			// cerr<<"connectedComponentLocal "<<connectedComponentLocal <<endl;
			if(connectedComponentOriginal<connectedComponentLocal){
				// cerr<<"entrou"<<endl;
				auxGraph.connectu(remainingEdgesToChoose[p].first,remainingEdgesToChoose[p].second);
				i--;
				remainingEdgesToChoose.erase(remainingEdgesToChoose.begin()+p);		
				continue;
			}
		}

		edgesRemoved.insert(remainingEdgesToChoose[p]);
		remainingEdges.erase(remainingEdgesToChoose[p]);
		remainingEdgesToChoose.erase(remainingEdgesToChoose.begin()+p);
	}
	for(set<pair<int,int> >::iterator it = remainingEdges.begin();it!=remainingEdges.end();it++){
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
void Graph::bfs(int source){
	
	int currentVertex;

	queue<int> q;

	

	this->visited[source]=VISIT;
	q.push(source);

	
	while(!q.empty()){
		currentVertex= q.front();
		q.pop();
		for(set<int>::iterator it=this->adjList[currentVertex].begin();
				it!=this->adjList[currentVertex].end();
				it++){
			int childNode = *it;
			if(this->visited[childNode]==NOT_VISIT){//se ainda nao foi visitado
				q.push(childNode);
				visited[childNode]=VISIT;
			}
		}
	}
}
void Graph::resetVisited(){
	this->visited.set(); 
	for(int i=0;i<N;i++){
		if(this->vertices.count(i)==0){
			this->visited.reset(i);
		}
	}
}

bool Graph::removeEdgeu(int u,int v){
	if (this->adjList[u].count(v)>0 && this->adjList[v].count(u)>0) {
		this->removeEdge(u,v);
		this->removeEdge(v,u);
		this->numEdges--;
	}
	
}

bool Graph::removeEdge(int u,int v){
	return this->adjList[u].erase(v);
}
bool Graph::wasAllVisited(){
	return this->visited.none();
}

int Graph::getUnvisitedVertex(){
	for(set<int>::iterator it=this->vertices.begin();it!=this->vertices.end();it++){
		if(this->visited[*it]==NOT_VISIT){
			return *it;
		}
	}
	return -1;
}

int Graph::getNumberOfConnectedComponents(){
	int n=0;
	this->resetVisited();
	while(!this->wasAllVisited()){
		int src=this->getUnvisitedVertex();
		this->bfs(src);
		n++;
	}	
	return n;
}

set<pair<int,int> > Graph::getEdgesInPairs(){
	set<pair<int,int> > edg;
	for(set<int>::iterator it=this->vertices.begin();it!=this->vertices.end();it++){
		int u= *it;
		for(set<int>::iterator it2=this->adjList[u].begin();it2!=this->adjList[u].end();it2++){
			int v=*it2;
			if(v>u){
				edg.insert(pair<int,int>(u,v));
			}
		}
	}
	return edg;
}