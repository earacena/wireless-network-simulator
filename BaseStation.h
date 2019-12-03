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

	BaseStation(string BSID);

	vector<int> poisson(int numofchannels); // returns a poisson generated random number for number of channels

	string getName();

	Pair getPosition();	//returns a Pair of position

	void setPosition(Pair pos);	// returns position of node
	
	int getRadius();	// return radius of node
		
	void setRadius(int r);	// set radius of node

	vector<Node> get_Nodes(); // return all nodes in basestation

	void allocateChannel(Node node1,Node node2); // allocates a channel based on availiable channels on node1 and node 2
	
	bool coChannelInterference();
	bool createRoute(Node &node1, Node &node2); // Create a new route between two nodes
	bool createRoute(Node &node1, Node &node2,Node &node3); // Create a new route between three nodes

private:
	string name;
	Pair position;
	int radius;
	vector<Node> adjacency_list;

};

#endif //BASESTATION_H_
