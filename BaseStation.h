// this is the header file includes the Node and Basestation classes 

#ifndef BASESTATION_H_
#define BASESTATION_H_

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <bits/stdc++.h> 
#include "Node.h"

using namespace std;

typedef pair<int,int> Pair;


class BaseStation {		
public:
	BaseStation();	// default constructor

	BaseStation(Pair p, int r);

	BaseStation(int x, int y, int r);

        BaseStation(std::string BSID,int r);

	vector<int> poisson(int numofchannels); // returns a poisson generated random number for number of channels
  
        std::string getName();

	Pair getPosition();	//returns a Pair of position

	void setPosition(Pair pos);	// returns position of node
	
	int getRadius();	// return radius of node
		
	void setRadius(int r);	// set radius of node

	void addNode(Node &node); // add a node to the current basestation

	Node findNode(string nodename); // find a node with the name

	void updateNode(Node &node); // update current node to new node 

	void removeNode(Node &node); // remove a node from the basestation

	vector<Node> get_Nodes(); // return all nodes in basestation

	void allocateChannel(Node node1,Node node2); // allocates a channel based on availiable channels on node1 and node 2
	
	bool coChannelInterference();
	
	vector<vector<int>> weightBetweenTwoNodes(Node &node1, Node &node2); // get the weight of the routes between two nodes

	vector<int> allChannelWeights(Node &node1);
	bool createRoute(Node &node1, Node &node2); // Create a new route between two nodes
	bool createRoute(Node &node1, Node &node2,Node &node3); // Create a new route between three nodes

private:
        std::string name;
	Pair position;
	int radius;
	vector<Node> adjacency_list;

};

#endif //BASESTATION_H_
