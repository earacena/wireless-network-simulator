#include <iostream>
#include <utility>
#include <vector>
#include "Node.h"

using namespace std;

typedef pair<int,int> Pair;


Node::Node(){	// default constructor
	position.first = 0;
	position.second = 0;
	radius = 0;
}

Node::Node(Pair p, int r){	// 2 arg constructor 
	position = p;
	radius = r;
}

Node::Node(int x, int y, int r){ // 3 arg contructor
	position.first = x;
	position.second = y;
	radius = r;
}

Pair Node::getPosition(){	//returns a Pair of position
	return position;
}
	
void Node::setPosition(Pair pos){	// sets position of node, pair version
	position = pos;
}

void Node::setPosition(int x, int y){			// sets position of node, separate entry
	position.first = x;
	position.second = y;
}
	
int Node::getRadius(){	// return radius of node
	return radius;
}

void Node::setRadius(int r){	// set radius of node
	radius = r;
}
