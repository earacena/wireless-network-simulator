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

	Node(string nodename);		

	Pair getPosition();	//returns a Pair of position
		
	
	void setPosition(Pair pos);	// sets position of node, pair version
	

	void setPosition(int x, int y);			// sets position of node, separate entry

	void setBasestation(string basestation); // assigns node to given basestation		
	
	string getBasestation(); // gets the basestation of current node

	void setName(string nodename);

	string getName (); // gets node name

	int getRadius();	// return radius of node		

	void setRadius(int r);	// set radius of node

	void setChannels(int n, vector<int> &weight); // set the number of channels with corresponding weight
	
	vector<int> getChannelWeights(); // get the channel weights for current node

	vector<bool> getAllChannels(); // get all the channels for current node

	int getBestAvailableChannel(); // get the best currently available channel for current node
	
	int getBestAvailableChannel(int channeltoavoid); // get the best currently available channel thats not the parameter

	void reserveChannel(int channel);// reserve a channel
 
	void releaseChannel(int channel); // release a channel

	bool checkChannelStatus(int channel); // check status of a channel
	
	int checkChannelWeight(int channel);// check weight of a channel

	void createRoute(Node othernode); // Create a route to another node


private:
	pair<int, int> position;
	int radius;

	string basestation;
	string name;

	struct Channel
	{
		bool used; // is the channel in use
		int weight; // weight of the channel
	};
	
	vector<Channel> Channels; // Vector of the number of channels for each node
	vector<pair<Node,Channel>> routes; // Vector that contains the current routes through node
};


#endif //NODE_H_