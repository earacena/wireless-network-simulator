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

	int getBestAvailableChannel(vector<int> channelstoskip); // get the best currently available channel thats not the parameter

	bool reserveChannel(int channel);// reserve a channel

	void releaseChannel(int channel); // release a channel

	bool checkChannelStatus(int channel); // chec  k status of a channel

	int checkChannelWeight(int channel);// check weight of a channel

	int getChannelName(); // get the name of the channel
	int getSendingChannel(); // get the sending channel used by the node
	
	void setSendingChannel(int channel); // set the channel the node is currently transmitting on
	
	int getListeningChannel();// get the listening channel used by the node

	void setListeningChannel(int channel); // set the channel the node is currently receieving on

	void createRoute(Node othernode); // Create a route to another node

	void getRoute(Node &node); // get the route taken by the node

	void nodesInRange(Node & initialNode, vector<Node> & allNodes);//fill the Adjacency list with Nodes that are within range

	vector<int> getSortedChannelsByWeights();

	int helpCreateRoute(); // keep trying next best with no repeats
	bool createRoute(Node &node1, Node &node2,Node &node3); // Create a new route between three nodes
	bool createRoute(Node &node1, Node &node2); // Create a new route between two nodes
	bool createRoute(); // Create a new route for a node

    void graphGenerationAlgo(Node startNode, Node endNode);//generates the available graphs from the start to the destination

private:
	pair<int, int> position;
	int radius;
	string basestation;

	string name;
	string dest;
	string source;

	int sendingchannel;
	int listeningchannel;


	vector<int> bestChannelIds;
    void graphGenerationAlgo(Node startNode, Node endNode, vector<Node> path);//overloaded for use within the graphGenerationAlgo function
    bool pathCheck (const Node  & nextNode, const vector<Node> & path);//helper function to check if the node is already in the path
	struct Channel
	{
		bool used; // is the channel in use
		int weight; // weight of the channel
		int id; // id of the current channel
	};
    vector<pair<Node,Node>> adjlist;//adjacency list
	vector<Channel> Channels; // Vector of the number of channels for each node
	vector<pair<Node,Node>> routes; // Vector that contains the current routes through node
	vector<vector<Node>> fullroutes;//passes back a list of all the routes from the start to the destination
};


#endif //NODE_H_
