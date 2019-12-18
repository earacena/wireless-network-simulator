// this is the header file includes the Node and Basestation classes 

#include <iostream>
#include <utility>
#include <vector>
#include <chrono>
#include <random>

#include "BaseStation.h"

using namespace std;

typedef pair<int,int> Pair;


BaseStation::BaseStation(){	// default constructor
	position.first = 0;
	position.second = 0;
	radius = 0;
}

BaseStation::BaseStation(Pair p, int r){
	position = p;
	radius = r;
}

BaseStation::BaseStation(int x, int y, int r){
	position.first = x;
	position.second = y;
	radius = r;
}
BaseStation::BaseStation(std::string BSID,int r){
	position.first = 0;
	position.second = 0;
	radius = r;
	name = BSID;
}

std::string BaseStation::getName(){ // return the name
	return name;
}

Pair BaseStation::getPosition(){	//returns a Pair of position
	return position;
}
	
void BaseStation::setPosition(Pair pos){	// returns position of node
	position = pos;
}
	
int BaseStation::getRadius(){	// return radius of node
	return radius;
}

void BaseStation::setRadius(int r){	// set radius of node
	radius = r;
}
bool BaseStation::inBaseStationRadius(Node &node){ // check if node in radius of basestation
	double dist = 0;
	int bsradius = getRadius();
	int noderadius = node.getRadius();

	Pair coords = node.getPosition();
	int nodexcoord = coords.first;
	int nodeycoord = coords.second;

	Pair bscoords = getPosition();
	int bsxcoord = bscoords.first;
	int bsycoord = bscoords.second;

	dist = sqrt(pow(abs(nodexcoord - bsxcoord), 2) + pow(abs(nodeycoord - bsycoord), 2) * 1.0); 

	if(dist <= bsradius){
		cout << "Node " << node.getName() << " is in BS " << getName() << "'s Radius" << endl;
		return true;
	}
	else
	{
		cout << "Node " << node.getName() << " is not in BS " << getName() << "'s Radius" << endl;
		return false;
	}
	

}

void BaseStation::addNode(Node &node){ // add a node to the current basestation
	adjacency_list.push_back(node);
//	cout << adjacency_list.size() << endl;
}
vector<Node> BaseStation::get_Nodes(){ // return all nodes in basestation
	return adjacency_list;
}
void BaseStation::removeNode(Node &node){ // remove a node from the basestation
}

Node BaseStation::findNode(string nodetofind){
	cout << "Looking for " << nodetofind << endl;
	for (size_t i = 0; i < adjacency_list.size(); i++)
	{
		if(adjacency_list[i].getName() == nodetofind)
			return adjacency_list[i];
	}
	Node blank("error");
	cout << "Looking for " << nodetofind << " it was not found" << endl;
	return blank;	
}
void BaseStation::updateNode(Node &node){ // update current node to new node 
	for (size_t i = 0; i < adjacency_list.size(); i++)
	{
		if(adjacency_list.at(i).getName() == node.getName()){
			adjacency_list.at(i) = node;
			cout << "updating node " << node.getName() << endl;
		}
	}
}

//	Co-channel 			interference --- Implemented
//	Adj Channel 		interference --- 
// 	Exposed terminal 	problem		 --- 
vector<vector<int>> BaseStation::weightBetweenTwoNodes(Node &node1, Node &node2){ // get the weight of the routes between two nodes	
	
	vector<vector<int>> finalweights(10, vector<int>(10)); // 10 by 10 vector 
	//cout << "getting " << node1.getName() << " weights " << endl;
	vector<int> n1weight = node1.getChannelWeights();
	//cout << "getting " << node2.getName()<<  " weights" << endl;
	vector<int> n2weight = node2.getChannelWeights();

	cout << "Getting all weights for " << node1.getName() << " and " << node2.getName() << endl;
	for (size_t i = 0; i < finalweights.size(); i++)
	{
		for (size_t j = i; j < finalweights[i].size(); j++)
		{
			finalweights[i][j] = n1weight[i] * n2weight[j];
//			cout << "weight is = " << n1weight[i] << " * " << n2weight[j] << " = " << finalweights[i][j] << endl;
		}
		
	}
	return finalweights;		
}
