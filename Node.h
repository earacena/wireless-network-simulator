// this is the header file includes the Node and Basestation classes

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <utility>
#include <vector>
#include <bits/stdc++.h>
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

	void setDestination(Node &nodesrc, Node &nodedes);

	string getDestination();

	void setSource(Node &nodesrc, Node &nodedes);

	string getSource();

	void setName(string nodename);

	string getName (); // gets node name

	int getRadius();	// return radius of node

	void setRadius(int r);	// set radius of node

	void setChannels(int n, vector<int> &weight); // set the number of channels with corresponding weight

	vector<int> getChannelWeights(); // get the channel weights for current node

	bool getBiggerWeight(Pair weight1, Pair weight2); // compare two weights helper

	void sortWeights(); // sort weights

	vector<int> SortedWeightsByBest(); // get the best weights sorted by channel id

	vector<bool> getAllChannelsStatus(); // get all the channels for current node

	vector<int> getAllAvailableChannels(); // get all the free channels for the current node

	int getBestAvailableChannel(); // get the best currently available channel for current node

	int getBestAvailableChannel(int channeltoskip); // get the best currently available channel thats not the parameter

	bool reserveChannel(int channel);// reserve a channel

	void releaseChannel(int channel); // release a channel

	bool checkChannelStatus(int channel); // check status of a channel

	int checkChannelWeight(int channel);// check weight of a channel

	void createRoute(Node othernode); // Create a route to another node

	void getRoute(Node &node); // get the route taken by the node


	vector<int> getSortedChannelsByWeights();

    void graphGenerationAlgo(Node startNode, Node endNode);//generates the available graphs from the start to the destination

private:
	pair<int, int> position;
	int radius;
	string basestation;

	string name;
	string dest;
	string source;

	vector<int> bestChannelIds;
    void graphGenerationAlgo(Node startNode, Node endNode, vector<Node> path);//overloaded for use within the graphGenerationAlgo function
    bool pathCheck (const Node  & nextNode, const vector<Node> & path);//helper function to check if the node is already in the path
	struct Channel
	{
		bool used; // is the channel in use
		int weight; // weight of the channel
		int id; // id of the current channel
	};

	vector<Channel> Channels; // Vector of the number of channels for each node
	vector<pair<Node,Node>> routes; // Vector that contains the current routes through node
	vector<vector<Node>> fullroutes;//passes back a list of all the routes from the start to the destination
};


#endif //NODE_H_
