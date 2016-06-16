#include "ComplexNetwork/include/ComplexNetwork.hpp"
using namespace std;

ComplexNetwork::ComplexNetwork(Graph &g) : triangles(N,-1),tripplets(N,-1){
	this->net = new Graph();
	*(this->net) = g;
	buildDegreeVerticesMap();
	buildlocalClusteringCoeffPerNode();
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
			this->degreeVerticesMap[this->net->getDegree(*vit)].insert(*vit);
		}
	}
}

std::map<int, int> ComplexNetwork::getDegreeHistogram() {
	std::map<int, int> degreeHistogram;
	if (!this->degreeVerticesMap.empty()) {
		for (std::map<int, std::set<int> >::iterator it=this->degreeVerticesMap.begin(); it != this->degreeVerticesMap.end(); it++) {
			degreeHistogram[it->first] = it->second.size();
		}
	}
	return degreeHistogram;
}

std::map<int, float> ComplexNetwork::getDegreeDistribution() {
	map<int, float> degreeDist;
	if (!this->degreeVerticesMap.empty()) {
		for (std::map<int, std::set<int> >::iterator it=this->degreeVerticesMap.begin(); it != this->degreeVerticesMap.end(); it++) {
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


void ComplexNetwork::computeQK() {
	double acc=0.0;
	int k=0;
	for (std::map<int, std::set<int> >::iterator itI = this->degreeVerticesMap.begin(); itI != this->degreeVerticesMap.end(); itI++) {
		k = itI->first-1;
		acc = 0.0;
		cout << "this->net->getMaxDegree(): " << this->net->getMaxDegree() <<endl;
		for (int i = 0; i < this->net->getMaxDegree(); i++) {
			if (this->EMatrix.count(make_pair(i,k))) {
				acc += this->EMatrix[ make_pair(i,k) ];
			}
		}
		cerr << "acc p/ k="<<k<<" : "<<acc<<endl;
		this->qkMap[ k ] = acc/(double)this->net->getAvgDegree();
	}
}

void ComplexNetwork::printQKs() {
	cerr << "\n------------------------------\n qk values:\n";
	for (std::map<int, double >::iterator itI = this->qkMap.begin(); itI != this->qkMap.end(); itI++) {
		cerr << "[" << itI->first << "] : " << itI->second << "\n";
	}
}

void ComplexNetwork::printJointProbability() {
	for (std::map<int, std::set<int> >::iterator itI = this->degreeVerticesMap.begin(); itI != this->degreeVerticesMap.end(); itI++) {
		for (std::map<int, std::set<int> >::iterator itJ = this->degreeVerticesMap.begin(); itJ != this->degreeVerticesMap.end(); itJ++) {
			cerr << "E[" << itI->first-1 << "][" << itJ->first-1 << "]: " << this->EMatrix[ make_pair(itI->first - 1, itJ->first - 1) ] << "\n";
		}
	}
}

void ComplexNetwork::buildJointProbabilityDistOfRemainingDegree() {
	int cnt=0;
	for (std::map<int, std::set<int> >::iterator itI = this->degreeVerticesMap.begin(); itI != this->degreeVerticesMap.end(); itI++) {
		for (std::map<int, std::set<int> >::iterator itJ = this->degreeVerticesMap.begin(); itJ != this->degreeVerticesMap.end(); itJ++) {
			cnt=0;
			for (std::set<int>::iterator veci = itI->second.begin(); veci != itI->second.end(); veci++) {
				set<int> list = this->net->getAdjList(*veci);
				for (set<int>::iterator adj = list.begin(); adj != list.end(); adj++) {
					if (itJ->second.count(*adj)) {
						cnt++;
					}
				}
			}
			this->EMatrix[ make_pair(itI->first - 1, itJ->first - 1) ] = (cnt/((double)this->net->getTotalVertices()*2.0));
		}
	}
}

double ComplexNetwork::computeVariance() {
	double var=0.0;
	for (map<int, double>::iterator it = this->qkMap.begin(); it != qkMap.end(); it++) {
		var += (it->first) * (it->first) * it->second;
	}
	for (map<int, double>::iterator it = this->qkMap.begin(); it != qkMap.end(); it++) {
		var -= (it->first * it->second) * (it->first * it->second);
	}
	return var;
}


double ComplexNetwork::computeAssortativity() {
	double var, acc=0.0;
	buildJointProbabilityDistOfRemainingDegree();
	
	//Delete
	printJointProbability();

	computeQK();
	printQKs();
	var = computeVariance();
	cerr << "computeVariance: "<<var<<endl;
	for (map<int, double>::iterator itj = qkMap.begin(); itj != qkMap.end(); itj++) {
		for (map<int, double>::iterator itk = qkMap.begin(); itk != qkMap.end(); itk++) {
			acc += itj->first*itk->first*(EMatrix[make_pair(itj->first, itk->first)] - (itj->second * itk->second));
		}
	}
	return acc/var;
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

void ComplexNetwork::buildlocalClusteringCoeffPerNode(){
	if(this->localClusteringCoeffPerNode.empty()){
		cerr<<"Building Local Clustering Coeff Per Node Map"<<endl;
		set<int> vertices = this->net->getVertices();
		for(set<int>::iterator it = vertices.begin();it!=vertices.end();it++){
			this->localClusteringCoeffPerNode[*it]=this->localClusteringCoefficient(*it);
		}
	}else{
		cerr<<"Map already calculated"<<endl;
	}
}
void ComplexNetwork::buildlocalClusteringCoeffMap(){
	if (this->localClusteringCoeffMap.empty()){
		this->buildlocalClusteringCoeffPerNode();
		set<int> vertices = this->net->getVertices();
		for(set<int>::iterator it = vertices.begin();it!=vertices.end();it++){
			this->localClusteringCoeffMap[this->localClusteringCoeffPerNode[*it]].push_back(*it);
		}
	}
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

std::vector<std::pair<std::pair<int,int>,double> > ComplexNetwork::jaccardAll(){
	if(this->jaccardCoeffBuffer.size()>0){
		return this->jaccardCoeffBuffer;
	}
	vector<pair<pair<int,int>,double> > result;
	set<int> vertices = this->net->getVertices();
	for(set<int>::iterator it = vertices.begin();it!=vertices.end();it++){
		int u=*it;
		for(set<int>::iterator it2 = vertices.begin();it2!=vertices.end();it2++){
			int v=*it2;
			if(u>v){
				if(this->net->getAdjList(u).count(v)==0){
					result.push_back(pair<pair<int,int>,double>(pair<int,int>(u,v),this->jaccardCoefficient(u,v)));
				}
			}
			
		}	
	}

	return result;
}
std::vector<std::pair<std::pair<int,int>,double> > ComplexNetwork::adamicAdarAll(){
	if(this->adamicAdarCoeffBuffer.size()>0){
		return this->adamicAdarCoeffBuffer;
	}
	vector<pair<pair<int,int>,double> > result;
	set<int> vertices = this->net->getVertices();
	for(set<int>::iterator it = vertices.begin();it!=vertices.end();it++){
		int u=*it;
		for(set<int>::iterator it2 = vertices.begin();it2!=vertices.end();it2++){
			int v=*it2;
			if(u>v){
				if(this->net->getAdjList(u).count(v)==0){
					result.push_back(pair<pair<int,int>,double>(pair<int,int>(u,v),this->adamicAdarCoefficient(u,v)));
				}
			}
			
		}	
	}
	return result;
}
std::vector<std::pair<std::pair<int,int>,double> > ComplexNetwork::CNAll(){
	if(this->CNCoeffBuffer.size()>0){
		return this->CNCoeffBuffer;
	}
	vector<pair<pair<int,int>,double> > result;
	set<int> vertices = this->net->getVertices();
	for(set<int>::iterator it = vertices.begin();it!=vertices.end();it++){
		int u=*it;
		for(set<int>::iterator it2 = vertices.begin();it2!=vertices.end();it2++){
			int v=*it2;
			if(u>v){
				if(this->net->getAdjList(u).count(v)==0){
					result.push_back(pair<pair<int,int>,double>(pair<int,int>(u,v),this->CN(u,v)));
				}
			}
		}
		
	}
	return result;
}
void ComplexNetwork::linkPrediction(int predictor,std::set<std::pair<int,int> > &edgesToCheck,int K,ostream &outFile){
	this->calculatePredictorsBuffers();
	vector<pair<pair<int,int>,double> > coefficients;
	int counterCorrectM = 0;
	pair<int,int> p1;
	pair<int,int> p2;	
	ComparisonPredictors comp;
	//Precision  = true Positive / Total Positive
	//accuracy = true positive + true negative / total population
	comp = ComparisonPredictors();
	switch (predictor){
		case PREDICTOR_JACCARD:
			// cerr<<"Running Jaccard for All Pairs"<<endl;
			coefficients  = this->jaccardAll();
			break;
		case PREDICTOR_ADAMIC_ADAR:
			// cerr<<"Running Adamic Adar for All Pairs"<<endl;
			coefficients  = this->adamicAdarAll();
			// cerr<<"AdamicAdarOrdenado:"<<endl;
			break;
		case PREDICTOR_CN:
			// cerr<<"Running CN for All Pairs"<<endl;
			coefficients  = this->CNAll();
			// cerr<<"CN Ordenado:"<<endl;
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
		// cerr<<"\t"<<coefficients[i].first.first<<" "<<coefficients[i].first.second<<" "<<coefficients[i].second<<endl;
		if(edgesToCheck.count(p1)>0 || edgesToCheck.count(p2)>0){
			counterCorrectM++;
		}
	}

	double precision = counterCorrectM*1.0 / K;
	double recall = (edgesToCheck.size()!=0)?counterCorrectM*1.0/edgesToCheck.size():0;
	outFile<<"\t\tCorrects: "<<counterCorrectM<<endl;
	outFile<<"\t\tL: "<<K<<endl;
	outFile<<"\t\tEdges Removed: "<<edgesToCheck.size()<<endl;
	outFile<<"\t\tPrecision:"<<precision<<endl;
	outFile<<"\t\tRecall :"<<recall<<endl;
}

void ComplexNetwork::printLocalClustHistogram(){
	this->buildlocalClusteringCoeffMap();
	for (map<double,vector<int> >::iterator it = this->localClusteringCoeffMap.begin(); 
			it != this->localClusteringCoeffMap.end(); 
			it++)
		cout << it->first << " " << it->second.size() << "\n";
}

void ComplexNetwork::printLocalClustHistogram(std::string filename, std::string suffix){
	this->buildlocalClusteringCoeffMap();
	ofstream outFile;
	string outFilename = filename + "." + suffix;

	outFile.open(outFilename.c_str());
	if (outFile.is_open()) {
		for (map<double,vector<int> >::iterator it = this->localClusteringCoeffMap.begin();
			it != this->localClusteringCoeffMap.end();
			it++
		)
			outFile << it->first << " " << it->second.size() << "\n";
		outFile.close();
	}
	else {
		cerr << "ERROR: Output File could not be created: " << outFilename << "\n";
	}
}
void ComplexNetwork::calculatePredictorsBuffers(){
	vector<pair<pair<int,int>,double> > coefficients;
	pair<int,int> p1;
	pair<int,int> p2;	
	ComparisonPredictors comp;
	//Precision  = true Positive / Total Positive
	//accuracy = true positive + true negative / total population
	comp = ComparisonPredictors();
	if(this->jaccardCoeffBuffer.empty()) {
		cerr<<"Calculating JACCARD for ALL PAIRS"<<endl;
		coefficients  = this->jaccardAll();
		sort(coefficients.begin(),coefficients.end(),comp);
		this->jaccardCoeffBuffer.insert(this->jaccardCoeffBuffer.end(),coefficients.begin(),coefficients.begin()+MAX_TO_STORE);
		
	}
	if(this->adamicAdarCoeffBuffer.empty()){
		cerr<<"Calculating ADAMIC ADAR for ALL PAIRS"<<endl;
		coefficients  = this->adamicAdarAll();
		sort(coefficients.begin(),coefficients.end(),comp);
		this->adamicAdarCoeffBuffer.insert(this->adamicAdarCoeffBuffer.end(),coefficients.begin(),coefficients.begin()+MAX_TO_STORE);
	}

	if(this->CNCoeffBuffer.empty()){
		cerr<<"Calculating CN for ALL PAIRS"<<endl;
		coefficients  = this->CNAll();
		sort(coefficients.begin(),coefficients.end(),comp);
		this->CNCoeffBuffer.insert(this->CNCoeffBuffer.end(),coefficients.begin(),coefficients.begin()+MAX_TO_STORE);
	}

	

}

void ComplexNetwork::printPredictorsBuffer(std::string filename, std::string suffix){
	this->calculatePredictorsBuffers();
	
	ofstream outFile;
	string outFilename = filename + "." + suffix;

	outFile.open(outFilename.c_str());
	if (outFile.is_open()) {
		outFile<<"Jaccard"<<endl;
		for (vector<pair<pair<int,int>,double> >::iterator it = this->jaccardCoeffBuffer.begin();
			it != this->jaccardCoeffBuffer.end();
			it++
		)
			outFile << it->first.first << " "<<it->first.second <<" " << it->second << "\n";
		outFile<<"Adamic"<<endl;
		for (vector<pair<pair<int,int>,double> >::iterator it = this->adamicAdarCoeffBuffer.begin();
			it != this->adamicAdarCoeffBuffer.end();
			it++
		)
			outFile << it->first.first << " "<<it->first.second <<" " << it->second << "\n";

		outFile<<"CN"<<endl;
		for (vector<pair<pair<int,int>,double> >::iterator it = this->CNCoeffBuffer.begin();
			it != this->CNCoeffBuffer.end();
			it++
		)
			outFile << it->first.first << " "<<it->first.second <<" " << it->second << "\n";
		outFile.close();
	}
	else {
		cerr << "ERROR: Output File could not be created: " << outFilename << "\n";
	}
}
void ComplexNetwork::runAval(std::string filename,set<pair<int,int> >edgesRemoved ,std::string suffix){

	ofstream outFile;
	string outFilename = filename + "." + suffix;

	outFile.open(outFilename.c_str());
	if (outFile.is_open()) {
		outFile<<"Jaccard"<<endl;
		this->linkPrediction(PREDICTOR_JACCARD,edgesRemoved,100,outFile);
		outFile<<endl;
		this->linkPrediction(PREDICTOR_JACCARD,edgesRemoved,300,outFile);
		outFile<<endl;
		this->linkPrediction(PREDICTOR_JACCARD,edgesRemoved,500,outFile);
		outFile<<endl;
		this->linkPrediction(PREDICTOR_JACCARD,edgesRemoved,1000,outFile);
		outFile<<endl;
		outFile<<"CN "<<endl;
		this->linkPrediction(PREDICTOR_CN,edgesRemoved,100,outFile);
		outFile<<endl;
		this->linkPrediction(PREDICTOR_CN,edgesRemoved,300,outFile);
		outFile<<endl;
		this->linkPrediction(PREDICTOR_CN,edgesRemoved,500,outFile);
		outFile<<endl;
		this->linkPrediction(PREDICTOR_CN,edgesRemoved,1000,outFile);
		outFile<<endl;
		outFile<<"Adamic"<<endl;
		this->linkPrediction(PREDICTOR_ADAMIC_ADAR,edgesRemoved,100,outFile);
		outFile<<endl;
		this->linkPrediction(PREDICTOR_ADAMIC_ADAR,edgesRemoved,300,outFile);
		outFile<<endl;
		this->linkPrediction(PREDICTOR_ADAMIC_ADAR,edgesRemoved,500,outFile);
		outFile<<endl;
		this->linkPrediction(PREDICTOR_ADAMIC_ADAR,edgesRemoved,1000,outFile);
		
		outFile.close();
	}
	else {
		cerr << "ERROR: Output File could not be created: " << outFilename << "\n";
	}
}