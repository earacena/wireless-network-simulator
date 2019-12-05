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
BaseStation::BaseStation(char BSID,int r){
	position.first = 0;
	position.second = 0;
	radius = r;
	name = BSID;
}

char BaseStation::getName(){ // return the name
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
void BaseStation::addNode(Node &node){ // add a node to the current basestation
	adjacency_list.push_back(node);
}
void BaseStation::removeNode(Node &node){ // remove a node from the basestation
}

Node BaseStation::findNode(string nodetofind){
	for (size_t i = 0; i < adjacency_list.size(); i++)
	{
		if(adjacency_list[i].getName() == nodetofind)
			return adjacency_list[i];
	}
	
}
void BaseStation::updateNode(Node &node){ // update current node to new node 
	Node oldnode = findNode(node.getName());
	oldnode = node;
}
vector<int> BaseStation::poisson(int numofchannels){
  // construct a trivial random generator engine from a time-based seed:
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);

  std::poisson_distribution<int> distribution (numofchannels);

 // std::cout << "some Poisson-distributed results (mean=numofchannels: ";
  vector<int> values;
  for (int i=0; i<numofchannels; ++i){
	  values.push_back(distribution(generator));
  }
  return values;
}

bool BaseStation::createRoute(Node &n1, Node &n2){ // Create a new route between two nodes
	int node1channel = -1;
	int node2channel = -1;

	//Get the best channel 
	node1channel = n1.getBestAvailableChannel();
	// cout << "best channel for node: " << n1.getName() << " is " << node1channel << " | the best for node: " << n2.getName() << " is " << node2channel << '\n';
	// cout << n1.checkChannelStatus(node1channel) << " | " << n2.checkChannelStatus(node2channel);
	if(n1.checkChannelStatus(node1channel) == 0 && n2.checkChannelStatus(node1channel) == 0){ // The channel selections are available
		cout << "reserving channels " << node1channel << '\n';
		n1.reserveChannel(node1channel);
		n2.reserveChannel(node1channel);
		return true;
	}
	else
	{
		return false;
	}	

}
bool BaseStation::createRoute(Node &n1, Node &n2,Node &n3){ // Create a new route between three nodes
	int node1channel = -1;
	int node2channel = -1;
	int node3channel = -1;

	//Get the best channel 
	node1channel = n1.getBestAvailableChannel();
	cout <<node1channel << "best for node 1" << endl;
	node2channel = node1channel;
		cout <<"test" << endl;
	node3channel = n3.getBestAvailableChannel(node1channel); // find a channel thats not channel 1
		cout <<"test2" << endl;
	//cout << "best channel for node: " << n1.getName() << " is " << node1channel << " | the best for node: " << n2.getName() << " is " << node2channel << '\n';
	 cout << n1.checkChannelStatus(node1channel) << " | " << n2.checkChannelStatus(node2channel);
	if(n1.checkChannelStatus(node1channel) == 0 && n2.checkChannelStatus(node2channel) == 0 && n2.checkChannelStatus(node3channel) == 0 && n2.checkChannelStatus(node3channel) == 0){ // The channel selections are available
		cout << "reserving channels " << node1channel << " " << node2channel << " " << node3channel <<  '\n';
		n1.reserveChannel(node1channel);
		n2.reserveChannel(node2channel);
		n2.reserveChannel(node3channel);
		n3.reserveChannel(node3channel);
		return true;
	}
	else
	{
		return false;
	}
}

vector<vector<int>> BaseStation::weightBetweenTwoNodes(Node &node1, Node &node2){ // get the weight of the routes between two nodes	
	
	vector<vector<int>> finalweights(10, vector<int>(10)); // 10 by 10 vector 
	//cout << "getting " << node1.getName() << " weights " << endl;
	vector<int> n1weight = node1.getChannelWeights();
	//cout << "getting " << node2.getName()<<  " weights" << endl;
	vector<int> n2weight = node2.getChannelWeights();

	for (size_t i = 0; i < finalweights.size(); i++)
	{
		for (size_t j = i; j < finalweights[i].size(); j++)
		{
			finalweights[i][j] = n1weight[i] * n2weight[j];
			cout << "weight is = " << n1weight[i] << " * " << n2weight[j] << " = " << finalweights[i][j] << endl;
		}
		
	}
	return finalweights;		
}
