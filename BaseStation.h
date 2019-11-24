// this is the header file includes the Node and Basestation classes 

#ifndef BASESTATION_H_
#define BASESTATION_H_

#include <iostream>
#include <utility>
#include <vector>
#include "Node.h"

using namespace std;

typedef pair<int,int> Pair;


class BaseStation {		
public:
	BaseStation();	// default constructor

	BaseStation(Pair p, int r);

	BaseStation(int x, int y, int r);

	Pair getPosition();	//returns a Pair of position

	void setPosition(Pair pos);	// returns position of node
	
	int getRadius();	// return radius of node
		
	void setRadius(int r);	// set radius of node

private:
	Pair position;
	int radius;
	vector<Node> adjacency_list;

};

#endif //BASESTATION_H_
