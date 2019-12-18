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

    std::string getName();
	
	Pair getPosition();	//returns a Pair of position

	void setPosition(Pair pos);	// returns position of node
	
	int getRadius();	// return radius of node
		
	void setRadius(int r);	// set radius of node

	bool inBaseStationRadius(Node &node); // check if node in basestation of radius

	void addNode(Node &node); // add a node to the current basestation

	Node findNode(string nodename); // find a node with the name

	void updateNode(Node &node); // update current node to new node 

	void removeNode(Node &node); // remove a node from the basestation

	vector<Node> get_Nodes(); // return all nodes in basestation

	void allocateChannel(Node node1,Node node2); // allocates a channel based on availiable channels on node1 and node 2
	
	bool coChannelInterference();
	
	vector<vector<int>> weightBetweenTwoNodes(Node &node1, Node &node2); // get the weight of the routes between two nodes

	vector<int> allChannelWeights(Node &node1);

private:
    std::string name;
	Pair position;
	int radius;
	vector<Node> adjacency_list;

};

#endif //BASESTATION_H_
