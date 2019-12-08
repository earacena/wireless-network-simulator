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
bool BaseStation::inBaseStationRadius(Node &node){ // check if node in basestation of radius
	double dist = 0;
	int bsradius = getRadius();
	int noderadius = node.getRadius();

	Pair coords = node.getPosition();
	int nodexcoord = coords.first;
	int nodeycoord = coords.second;

	Pair bscoords = getPosition();
	int bsxcoord = bscoords.first;
	int bsycoord = bscoords.second;

	dist = sqrt(pow(nodexcoord - bsxcoord, 2) + pow(nodeycoord - bsycoord, 2) * 1.0); 

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
		//	cout << "updating node " << node.getName() << endl;
		}
	}
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
int helpCreateRoute(Node &node){ // keep trying next best with no repeats
	auto channels = node.getSortedChannelsByWeights();
	
	vector<int> tries;
	int channel = 0;
	bool used = false;
	for (size_t i = 0; i < channels.size(); i++)
	{
	//
		cout << "is channel " << channels[i] << " used " << used << endl;		
		if(!used){
				used = node.checkChannelStatus(channels[i]);	
				channel = channels[i];
				used = true;
		//		cout << "current status of chan " << channel << " " << used << endl;
				break;
		}
	}
//	cout << "Found a channel for the current node "<< node.getName() << " channel " << channel << endl;
	return channel;
}

bool BaseStation::createRoute(Node &n1, Node &n2){ // Create a new route between two nodes
	int node1channel = -1;
	int node2channel = -1;

	auto wn1 = n1.getSortedChannelsByWeights();
	auto wn2 = n2.getSortedChannelsByWeights();

	//Get the best channel 
//	cout << "Looking for best channel for nodes " << n1.getName() << " & " << n2.getName() << endl;
	node1channel = helpCreateRoute(n1);
	node2channel = node1channel;
	//cout << "best channel for node: " << n1.getName() << " is " << node1channel << " | using the same channel for " << n2.getName() << " which is " << node2channel << '\n';
	// cout << n1.checkChannelStatus(node1channel) << " | " << n2.checkChannelStatus(node2channel);
	int count = 0;
	while (n1.checkChannelStatus(node1channel) == 1 || n2.checkChannelStatus(node2channel) == 1)
	{	
		cout << " The requested channel is not available for both nodes trying again " << endl;
		node1channel = wn1[count];
		node2channel = node1channel;
	//	cout << "New channel names " << node1channel << " | " << node2channel << endl;
	//	cout << " New channels " << n1.checkChannelStatus(node1channel) << " | " << n2.checkChannelStatus(node2channel) << endl;
		count ++;
	}
	// The channel selections are available
	if(!n1.reserveChannel(node1channel)){
		cout << "Couldn't reserve channel on " << n1.getName() << endl;
		return false;
	}
	if(!n2.reserveChannel(node1channel)){
		cout << "Couldn't reserve channel on " << n2.getName() << endl;
		return false;
	}
	else {
		cout << "Both Channels are now reserved " << endl;
		return true;
	}

}
bool BaseStation::createRoute(Node &n1, Node &n2,Node &n3){ // Create a new route between three nodes
	int node1channel = -1;
	int node2channel = -1;
	int node3channel = -1;

	auto wn1 = n1.getSortedChannelsByWeights();
	auto wn2 = n2.getSortedChannelsByWeights();
	auto wn3 = n3.getSortedChannelsByWeights();
	//Get the best channel 
	node1channel = helpCreateRoute(n1);
	node2channel = node1channel;
	node3channel = n3.getBestAvailableChannel(node2channel); // find a channel thats not used on node 1 and 2

	if(node3channel == -1){ // No point in trying if node 3 has no channels available
		return false;
	}
	//cerr << "Checking that status of all three chosen channels "  << n1.checkChannelStatus(node1channel) << " | " << n2.checkChannelStatus(node2channel) << " | " << n2.checkChannelStatus(node3channel) << " | " << n3.checkChannelStatus(node3channel) << " " << endl;

	int count = 0;
	while (n1.checkChannelStatus(node1channel) == 1 || n2.checkChannelStatus(node2channel) == 1 && count < wn1.size()-1) // Channel is not avail for n1 or n2
	{	
		if(count > wn1.size()-1){
			cout << "Couldn't find a channel " << endl;
			return false;
		}
		else{
			node1channel = wn1[count];
			node2channel = node1channel;
	//		cout << "New channel names " << node1channel << " | " << node2channel << endl;
	//		cout << "New channels" << n1.checkChannelStatus(node1channel) << " | " << n2.checkChannelStatus(node2channel) << endl;
			count ++;
		}
	}
//	cout << "Found channels for first two nodes/3" << endl;
//	cout << "current channels stat " << n2.checkChannelStatus(node2channel) << " | " << n2.checkChannelStatus(node3channel) << " | " << n3.checkChannelStatus(node3channel) << endl;
	count = 0;
	while (n2.checkChannelStatus(node2channel) == 1 || n2.checkChannelStatus(node3channel) == 1 || n3.checkChannelStatus(node3channel) == 1 && count < wn2.size()-1)
	{
		if(count > wn2.size()-1){
			cout << "Couldn't find a channel " << endl;
			return false;
		}
		else{
			vector<int> tries;
			tries.push_back(node2channel);
			node2channel = wn2[count];
			node3channel = node2channel;
		//cout << "New channel names " << node2channel << " | " << node3channel << endl;
		//cout << "New channels" << n2.checkChannelStatus(node2channel) << " | " << n3.checkChannelStatus(node3channel) << endl;
		count ++;
		}
	}
	cerr << "Found channels for last two nodes/3 " << endl;
	 // The channel selections are available
	if(!n1.reserveChannel(node1channel)){
		return false;
	}
	if(!n2.reserveChannel(node2channel)){
		return false;
	}
	if(!n2.reserveChannel(node3channel)){
		return false;
	}
	if(!n3.reserveChannel(node3channel)){
		return false;
	}
	return true;
}

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
