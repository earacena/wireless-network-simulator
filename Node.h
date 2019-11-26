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

	void setChannels(int n, vector<int> &weight); // set the number of channels with corresponding weight
	
	vector<int> getChannelWeights(); // get the channel weights for current node

	vector<bool> getAllChannels(); // get all the channels for current node

	int getBestAvailableChannel(); // get the best currently available channel for current node
	
	void reserveChannel(int channel);// reserve a channel
 
	void releaseChannel(int channel); // release a channel

	bool checkChannelStatus(int channel); // check status of a channel
	
	int checkChannelWeight(int channel);// check weight of a channel


private:
	pair<int, int> position;
	int radius;

	struct Channel
	{
		bool used; // is the channel in use
		int weight; // weight of the channel
	};
	
	vector<Channel> Channels; // Vector of the number of channels for each node

};


#endif //NODE_H_