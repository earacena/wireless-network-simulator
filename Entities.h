// this is the header file includes the Node and Basestation classes 

#ifndef ENTITIES_H_
#define ENTITIES_H_

#include <iostream>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int,int> Pair;

class Node {
public:
	Node(){	// default constructor
		position.first = 0;
		position.second = 0;
		radius = 0;
	}

	Node(Pair p, int r){	// 2 arg constructor 
		position = p;
		radius = r;
	}

	Node(int x, int y, int r){ // 3 arg contructor
		position.first = x;
		position.second = y;
		radius = r;
	}

	Pair getPosition(){	//returns a Pair of position
		return position;
	}
	
	void setPosition(Pair pos){	// sets position of node, pair version
		position = pos;
	}

	void setPosition(int x, int y){			// sets position of node, separate entry
		position.first = x;
		position.second = y;
	}
	
	int getRadius(){	// return radius of node
		return radius;
	}

	void setRadius(int r){	// set radius of node
		radius = r;
	}

 
private:
	pair<int, int> position;
	int radius;

};

class BaseStation {		
public:
	BaseStation(){	// default constructor
		position.first = 0;
		position.second = 0;
		radius = 0;
	}

	Pair getPosition(){	//returns a Pair of position
		return position;
	}
	
	void setPosition(Pair pos){	// returns position of node
		position = pos;
	}
	
	int getRadius(){	// return radius of node
		return radius;
	}

	void setRadius(int r){	// set radius of node
		radius = r;
	}



private:
	Pair position;
	int radius;
	vector<Node> adjacency_list;

};

#endif //ENTITIES_H_