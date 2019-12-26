// this is the header file includes the Node and Basestation classes

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <utility>
#include <vector>
#include <bits/stdc++.h>
#include "Sender.h"
using namespace std;

typedef pair<int,int> Pair;

class Node {
public:
	Node();	// default constructor


	Node(Pair p, int r);	// 2 arg constructor


	Node(int x, int y, int r); // 3 arg contructor

	Node(string nodename);

	Node &operator=(const Node &oldnode); // copy constructor 

	Node& returnNode();

	Node returnNodeByString(string nodename);

	Node& findNodeInAdjList(string &nodename);

	bool existsinAdjList(string nodename);

	void updateNodeinAdjList(Node &node);

	void updateSecondNodeFromAdjlist(Node &srcnode, Node &secondnode);

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

	bool getBiggerWeight(Pair weight1, Pair weight2); // compare two weights helper

	void sortWeights(); // sort weights

	vector<pair<int,int>> SortedWeightsByBest(); // get the best weights sorted by channel id

	vector<int> getAllChannels();

	vector<bool> getAllChannelsStatus(); // get all the channels for current node

	vector<int> getAllAvailableChannels(); // get all the free channels for the current node

	int getBestAvailableChannel(); // get the best currently available channel for current node

	int getBestAvailableChannel(vector<int> &channelstoskip); // get the best currently available channel thats not the parameter

	bool reserveChannel(int channel,string nodename);// reserve a channel

	void releaseChannel(int channel); // release a channel

	bool checkChannelStatus(int channel); // chec  k status of a channel

	int checkChannelWeight(int channel);// check weight of a channel

	int getChannelName(); // get the name of the channel

	int getSendingChannel(); // get the sending channel used by the node

	void setSendingChannel(int channel); // set the channel the node is currently transmitting on

	int getListeningChannel();// get the listening channel used by the node

	void setListeningChannel(int channel); // set the channel the node is currently receieving on

	int getPrevListeningChannel();// get the prevlistening channel used by the node

	void setPrevListeningChannel(int channel); // set the prev channel the node isreceieving on

	void setDestNode(string nodename, int channeltoset); // set the destnode of the current channel

	string getDestNode(int channel); // Get the Destination node for the requested channel

	int getDestChannelBySrcNode(string nodename);

	vector<vector<Hop>> getResults();

	void addToResults(vector<Hop> &currenthops);

	vector<vector<Node>> getRoutes(); // get the route taken by the node

 	vector<string> getRoutesString(); // get the route taken by the node 

	void nodesInRange(vector<Node> & allNodes);//fill the Adjacency list with Nodes that are within range


	int helpCreateRoute(vector<int> &channelstoavoid); // keep trying next best with no repeats

	bool oneHopHelper(int dest,string route,vector<Node> &allnodes);

	bool twoHopHelper(int start,string route,vector<Node> &allnodes);

	bool createRoute(Node &destnode,vector<Node> &allnodes); // Create a new route for a node

 	void testRouteGen(Node &n1,Node &n2, Node &n3,Node &n4); // Test Function
	
	//graph Algo functions
	
	void graphGenerationAlgo(Node & startNode, Node & endNode, vector<Node> noderef);//generates the available graphs from the start to the destination

  bool loopCheck (const string path, const char refChar);//helper function to check if the node is already in the path

  bool deadEnd (const string & path,const vector<string> & currentPaths);

	void setAllNodeRef(Node & initialNode, vector<Node> & receiverList);


	bool newRoutePossible(Node & startNode, Node & endNode, vector<string>  currentPaths);

	void mergePaths(Node & startNode, Node & endNode, vector<string>  currentPaths);

	vector<Node> routeRequest (vector<Node> & givenNodeList, Node & startNode, int pathIndex);

  float distanceFormula(int & x1, int & y1, int & x2, int & y2);

	/*----- ~ the following variables are just for the BFS implementation ~ ------*/
		//tracker to see if the node has been discovered;
		//0 = UNDISCOVERED, 1 = NEIGHBORS UNDISCOVERED, 2 = FULLY DISCOVERED
	int discovered = 0;
		//the number of hops; initialized to 100 to imitate infinity
	int hops = 100;
		//when running BFS we need to see the parent node
	Node* previous_hop = nullptr;
	/*---------------------------------------------------------------------------*/

private:
	pair<int, int> position;
	int radius;
	string basestation;
  
	vector<string> fullroutesstring;
	string adjlistsstring;

	string name;
	string dest;
	string source;

	int sendingchannel = -1;
	int listeningchannel = -1;
	int prevlistchannel = -1;
	vector<int> bestChannelIds; 

	struct Channel
	{
		bool used; // is the channel in use
		int weight; // weight of the channel
		int id; // id of the current channel
		string usedby; // what node is using this channel
	};
    vector<pair<Node,Node>> adjlist;//adjacency list
	vector<Channel> Channels; // Vector of the number of channels for each node
	vector<pair<Node,Node>> routes; // Vector that contains the current routes through node
	vector<vector<Node>> fullroutes;//passes back a list of all the routes from the start to the destination
	vector<vector<Hop>> results;
};


#endif //NODE_H_
