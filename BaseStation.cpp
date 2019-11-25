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

  std::cout << "some Poisson-distributed results (mean=numofchannels: ";
  vector<int> values;
  for (int i=0; i<numofchannels; ++i){
	  values.push_back(distribution(generator));
  }
  cout << values.size();
  return values;
}
