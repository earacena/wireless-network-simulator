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
BaseStation::BaseStation(string BSID){
	position.first = 0;
	position.second = 0;
	radius = 0;
	name = BSID;
}

string BaseStation::getName(){ // return the name
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
	node2channel = n2.getBestAvailableChannel(node1channel); // find a channel thats not channel 1
	// cout << "best channel for node: " << n1.getName() << " is " << node1channel << " | the best for node: " << n2.getName() << " is " << node2channel << '\n';
	// cout << n1.checkChannelStatus(node1channel) << " | " << n2.checkChannelStatus(node2channel);
	if(n1.checkChannelStatus(node1channel) == 0 && n2.checkChannelStatus(node2channel) == 0){ // The channel selections are available
		cout << " reserving channels " << node1channel << " " << node2channel << '\n';
		n1.reserveChannel(node1channel);
		n2.reserveChannel(node2channel);
		return true;
	}
	else
	{
		return false;
	}
	

}
