#include "ComplexNetwork/include/ComplexNetwork.hpp"
using namespace std;

ComplexNetwork::ComplexNetwork(Graph &g) : triangles(N,-1),tripplets(N,-1){
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
	if(this->tripplets[u]<0){
		int degree = this->net->getDegree(u);
		this->tripplets[u]= (degree*(degree-1))/2;
	}
	return this->tripplets[u];
}

int ComplexNetwork::getTrianglesNumber(int u){
	if(this->triangles[u]<0){
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
		triangles[u]= counter;
	}
	return triangles[u];
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
std::vector<std::pair<std::pair<int,int>,double> > ComplexNetwork::adamicAdarAll(){
	vector<pair<pair<int,int>,double> > result;
	set<int> vertices = this->net->getVertices();
	for(set<int>::iterator it = vertices.begin();it!=vertices.end();it++){
		int u=*it;
		for(set<int>::iterator it2 = vertices.begin();it2!=vertices.end();it2++){
			int v=*it2;
			if(u>v){
				result.push_back(pair<pair<int,int>,double>(pair<int,int>(u,v),this->adamicAdarCoefficient(u,v)));
			}
			
		}	
	}
	return result;
}
std::vector<std::pair<std::pair<int,int>,double> > ComplexNetwork::CNAll(){
	vector<pair<pair<int,int>,double> > result;
	set<int> vertices = this->net->getVertices();
	for(set<int>::iterator it = vertices.begin();it!=vertices.end();it++){
		int u=*it;
		for(set<int>::iterator it2 = vertices.begin();it2!=vertices.end();it2++){
			int v=*it2;
			if(u>v){
				result.push_back(pair<pair<int,int>,double>(pair<int,int>(u,v),this->CN(u,v)));
			}
			
		}
		
	}
	return result;
}
void ComplexNetwork::linkPrediction(int predictor,std::set<std::pair<int,int> > &edgesToCheck,int K){
	vector<pair<pair<int,int>,double> > coefficients;
	int counterCorrectM = 0;
	pair<int,int> p1;
	pair<int,int> p2;	
	ComparisonPredictors comp;
	//Precision  = true Positive / Total Positive
	//accuracy = true positive + true negative / total population
	comp = ComparisonPredictors();
	switch (predictor){
		case PREDICTOR_ADAMIC_ADAR:
			cerr<<"Running Adamic Adar for All Pairs"<<endl;
			coefficients  = this->adamicAdarAll();
			cerr<<"AdamicAdarOrdenado:"<<endl;
			break;
		case PREDICTOR_CN:
			cerr<<"Running CN for All Pairs"<<endl;
			coefficients  = this->CNAll();
			cerr<<"AdamicAdarOrdenado:"<<endl;
			break;
		default:
			cerr<<"Invalid Predictor"<<endl;
			return;
			break;
	}
	sort(coefficients.begin(),coefficients.end(),comp);
	for(int i=0;i<K;i++){
		p1=coefficients[i].first;
		p2 = pair<int,int>(coefficients[i].first.second,coefficients[i].first.first);
		cerr<<"\t"<<coefficients[i].first.first<<" "<<coefficients[i].first.second<<" "<<coefficients[i].second<<endl;
		if(edgesToCheck.count(p1)>0 || edgesToCheck.count(p2)>0){
			counterCorrectM++;
		}
	}
	cerr<<"\t\tCorrect :"<<counterCorrectM <<" out of "<<K<<endl;
	double percentage = counterCorrectM*1.0/edgesToCheck.size();
	cerr<<"\t\tCorrect :"<<counterCorrectM <<" out of "<<edgesToCheck.size()<<": "<<percentage<<endl;
}