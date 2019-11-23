// this is the header file includes the Node and Basestation classes 

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int,int> Pair;

class Node {
public:
	Node();	// default constructor
		

	Node(Pair p, int r);	// 2 arg constructor 
		

	Node(int x, int y, int r); // 3 arg contructor
		

	Pair getPosition();	//returns a Pair of position
		
	
	void setPosition(Pair pos);	// sets position of node, pair version
	

	void setPosition(int x, int y);			// sets position of node, separate entry
		
	
	int getRadius();	// return radius of node
		

	void setRadius(int r);	// set radius of node
		

 
private:
	pair<int, int> position;
	int radius;

};


#endif //NODE_H_