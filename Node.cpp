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
Node::Node(string nodename){
	position.first = 0;
	position.second = 0;
	radius = 0;
	name = nodename;
}
Node& Node::returnNode(){
	return *this;
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
void Node::setBasestation(string station){ // assigns node to given basestation
	basestation = station;
}
string Node::getBasestation(){ // gets the basestation of current node
	return basestation;
}
void Node::setName(string nodename){
	name = nodename;}

string Node::getName(){ // gets node name
	return name;
}
int Node::getRadius(){	// return radius of node
	return radius;
}

void Node::setRadius(int r){	// set radius of node
	radius = r;
}
void Node::setChannels(int n,vector<int> &weight){ // set the number of channels and their weights
	Channels.resize(n);
	for(int i = 0; i < Channels.size(); i++){
		Channels[i].weight = weight[i];
		Channels[i].id = i;
	}
}
void Node::setDestination(Node &src, Node &dest){
}
string Node::getDestination(){}

void Node::setSource(Node &src, Node &dest){}

string Node::getSource(){}

bool Node::getBiggerWeight(Pair w1, Pair w2){

	return(w1.second > w2.second);

}

void Node::sortWeights(){

}

vector<int> Node::SortedWeightsByBest(){ // Returns a channel list by weight order
	pair <int,int> channelandweight;
	vector<pair<int,int>> channelsandweights;
	for (size_t i = 0; i < Channels.size(); i++)
	{
		channelandweight.second = i; //id of the channel
		channelandweight.first = Channels[i].weight; // weight of the channel
		channelsandweights.push_back(channelandweight);
	}

	sort(channelsandweights.begin(),channelsandweights.end(),greater<Pair>()); // Sort by descending order


	vector<int> bestchannels;
	for (size_t i = 0; i < channelsandweights.size(); i++)
	{
		//	cout << "The best avail channel is " << channelsandweights.at(i).second << "with weight" << channelsandweights.at(i).first << endl;
		bestchannels.push_back(channelsandweights.at(i).second);
	}
	//	cout << "found the best channels for node " << getName() << endl;
	bestChannelIds = bestchannels;
	return bestchannels;
}
int Node::getChannelName(){ // get the name of the channel
	
}
vector<int> Node::getChannelWeights(){// get the channel weights for current node
	vector<int> currentChannelsWeights;
	cout << getName() << " channel weights are: " << endl;
	for(int i = 0; i < Channels.size(); i++){
		cout << "Weight for Channel " << i << " is " << Channels[i].weight << " " << endl;
		currentChannelsWeights.push_back(Channels[i].weight);
	}
	return currentChannelsWeights;
}
vector<bool> Node::getAllChannelsStatus(){ // get all the channel use status for the current node
	vector<bool> currentChannelUse;
	for(int i = 0; i < Channels.size(); i++){
		currentChannelUse.push_back(checkChannelStatus(i));
	}
	return currentChannelUse;
}
vector<int> Node::getAllAvailableChannels(){// get all the free channels
	vector<int> freechannels;
	vector<bool> allchannels = getAllChannelsStatus();

	for (size_t i = 0; i < allchannels.size(); i++)
	{
		if(checkChannelStatus(i) == 0){
			freechannels.push_back(i); // push back if channel is free
		}
	}

	return freechannels;
}

int Node::getBestAvailableChannel(){ // get the best currently available channel for current node
	vector<int> bestChannels = bestChannelIds;
	for(int i = 0; i < Channels.size(); i++){
		if(checkChannelStatus(bestChannels[i]) == 0)// Channel available
		{
			//	cout << bestChannels[i] << " is the best available channel for node: " << getName() << endl;
			return bestChannels[i];
		}
	}
	return -1;
}
//	Co-channel 			interference --- Implemented
//	Adj Channel 		interference --- 
// 	Exposed terminal 	problem		 --- 
int Node::getBestAvailableChannel(vector<int> channelstoskip){ // get the best currently available channel for current node
	vector<int> bestChannels = SortedWeightsByBest();
	bool channelfound = false;
	int bestchannel = -1;
	for(int i = 0; i < bestChannels.size(); i++){ 
		// Co-Channel Check
		if(bestChannels[i] != channelstoskip[0] && channelfound ==false && checkChannelStatus(bestChannels[i]) == 0)// Channel available
		{
		//	cout << bestChannels[i] << " is the best available channel for node: " << getName() << endl;
			
			bestchannel = bestChannels[i];
		}

		//Adj Channel Check
		cout << "Checking for no Adj Channel Problems" << endl;
		{
			if(i = 0){ // At channel 0
				if(checkChannelStatus(bestChannels[i]) == 0 && checkChannelStatus(bestChannels[i+1]) == 0){
					bestchannel = bestChannels[i];
				}
			}
			if(i > 0 && i < bestChannels.size()-2){ // At second to last channel
					if(checkChannelStatus(bestChannels[i]) == 0 && checkChannelStatus(bestChannels[i+1]) == 0 && checkChannelStatus(bestChannels[i-1]) == 0){
					bestchannel = bestChannels[i];
				}	
			}
			if(i = bestChannels.size()-1){
					if(checkChannelStatus(bestChannels[i]) == 0 && checkChannelStatus(bestChannels[i-1]) == 0){
					bestchannel = bestChannels[i];
				}	
			}
			
		}

		channelfound = true;
	}
	if(!channelfound){
	cout << "No Free Channels" << endl;
		return -1;
	}
	else
		return bestchannel;
}
bool Node::reserveChannel(int num){
	if(num > Channels.size()){
		cout << "Error that channel doesnt exist";
		return false;
	}
	else
	{
		cout << " Reserving the requested channel " << num << " for node " << getName() << endl;
		Channels[num].used = true;
		return true;
	}


}

void Node::releaseChannel(int num){
	if(num > Channels.size()){
		cout << "Error that channel doesnt exist";
	}
	else
	{
		Channels[num].used = false;
	}

}
int Node::getSendingChannel(){ // get the sending channel used by the node
	return sendingchannel;
}
void Node::setSendingChannel(int channel){ // set the channel the node is currently transmitting on
	sendingchannel = channel;
}
int Node::getListeningChannel(){ // get the listening channel used by the node
	return listeningchannel;
}
void Node::setListeningChannel(int channel){ // set the channel the node is currently receieving on
	listeningchannel = channel;
}
bool Node::checkChannelStatus(int num){ // check status of a channel

	if(num > Channels.size()){
		cout << "Error that channel doesnt exist " << num << endl;
		return -1;
	}
	else if (Channels.size() > 11){
		cout << "problem" << 1 << endl;
		return -1;
	}
	else
	{
	//	cout << " Checking status of channel " << num << " | " << "for node" << getName() << endl;
		return Channels[num].used;
	}
}
int Node::checkChannelWeight(int num){ // check weight of a channel
	if(num > Channels.size()){
		cout << "Error that channel doesnt exist";
		return -1;
	}
	else
	{
		return Channels[num].weight;
	}
}
int Node::helpCreateRoute(){ // keep trying next best with no repeats
	auto sortedchannels = SortedWeightsByBest();	
	vector<int> tries;
	int channel = 0;
	bool used = false;
	for (size_t i = 0; i < sortedchannels.size(); i++)
	{
		//
		cout << "is channel " << sortedchannels[i] << " used " << used << endl;		
		if(!used){
				used = checkChannelStatus(sortedchannels[i]);	
				channel = getBestAvailableChannel();
				used = true;
			//		cout << "current status of chan " << channel << " " << used << endl;
				break;
		}
	}
	cout << "Found the best channel for the current node "<< getName() << " channel " << channel << endl;
	return channel;
}
bool Node::createRoute(){ // Create a new route between three nodes
	int node1channel = -1;

	auto bestChannels = SortedWeightsByBest();

	auto allnodesinpath = fullroutes;

	if (fullroutes.size() == 2){ // Only two nodes
		cout << "Only two total nodes in path detected " << endl;
		int node1channel = -1;
		int node2channel = -1;

		//Get the first and only two nodes 
		cout << fullroutes.size() << "all routes size" << endl;
		Node destnode = fullroutes.at(0).at(fullroutes.size()-1);

		auto wn1 = SortedWeightsByBest(); // Node 1
		auto wn2 = destnode.SortedWeightsByBest(); // Node 2

		//Get the best channel 
		//	cout << "Looking for best channel for nodes " << n1.getName() << " & " << n2.getName() << endl;

		node1channel = helpCreateRoute();
		node2channel = node1channel;

		//cout << "best channel for node: " << n1.getName() << " is " << node1channel << " | using the same channel for " << n2.getName() << " which is " << node2channel << '\n';
		// cout << n1.checkChannelStatus(node1channel) << " | " << n2.checkChannelStatus(node2channel);

		int count = 0;
		while (checkChannelStatus(node1channel) == 1 || destnode.checkChannelStatus(node2channel) == 1)
		{	
			cout << " The requested channel is not available for both nodes trying again " << endl;
			node1channel = wn1[count];
			node2channel = node1channel;

		//	cout << "New channel names " << node1channel << " | " << node2channel << endl;
		//	cout << " New channels " << n1.checkChannelStatus(node1channel) << " | " << n2.checkChannelStatus(node2channel) << endl;

			count ++;
		}
		// The channel selections are available
		if(!this->reserveChannel(node1channel)){
			cout << "Couldn't reserve channel on " << getName() << endl;
			return false;
		}
		if(!destnode.reserveChannel(node1channel)){
			cout << "Couldn't reserve channel on " << getName() << endl;
			return false;
		}
		else {
			cout << "Both Channels are now reserved " << endl;
			fullroutes.at(0).at(fullroutes.size()-1) = destnode;
			return true;
		}

	}		
	else // at least 3 nodes
	{
		cout << "3 + total nodes in path detected " << endl;
		for (size_t i = 0; i <= fullroutes.size()-2; i+2)
		{
			int node1channel = -1;
			int node2channel = -1;
			int node3channel = -1;
		
			//Get the first three nodes 
			cout << fullroutes.size() << " all routes size" << endl;
			Node n2 = fullroutes.at(0).at(i+1);
			Node n3 = fullroutes.at(0).at(i+2);

			auto wn1 = SortedWeightsByBest(); // Node 1
			auto wn2 = n2.SortedWeightsByBest(); // Node 2
			auto wn3 = n3.SortedWeightsByBest(); // Node 2

			node1channel = helpCreateRoute();
			node2channel = node1channel;
			vector<int> channelstoskip;

			channelstoskip.push_back(node2channel); // Avoid co channel interference

			node3channel = n3.getBestAvailableChannel(channelstoskip); // find a channel thats not used on node 1 and 2

			if(node3channel == -1){ // No point in trying if node 3 has no channels available
				return false;
			}		
			//cerr << "Checking that status of all three chosen channels "  << n1.checkChannelStatus(node1channel) << " | " << n2.checkChannelStatus(node2channel) << " | " << n2.checkChannelStatus(node3channel) << " | " << n3.checkChannelStatus(node3channel) << " " << endl;

 			int count = 0;
 			while (checkChannelStatus(node1channel) == 1 || n2.checkChannelStatus(node2channel) == 1 && count < wn1.size()-1) // Channel is not avail for n1 or n2
			{	
				if(count > wn1.size()-1){
					cout << "Couldn't find a channel " << endl;
					return false;
				}
				else{
					node1channel = wn1[count];
					node2channel = node1channel;
			//		cout << "New channel names " << node1channel << " | " << node2channel << endl;
			//		cout << "New channels" << n1.checkChannelStatus(node1channel) << " | " << n2.checkChannelStatus(node2channel) << endl;
					count ++;
				}
			}
			//	cout << "Found channels for first two nodes/3" << endl;
			//	cout << "current channels stat " << n2.checkChannelStatus(node2channel) << " | " << n2.checkChannelStatus(node3channel) << " | " << n3.checkChannelStatus(node3channel) << endl;
			count = 0;
			while (n2.checkChannelStatus(node2channel) == 1 || n2.checkChannelStatus(node3channel) == 1 || n3.checkChannelStatus(node3channel) == 1 && count < wn2.size()-1)
			{
				if(count > wn2.size()-1){
					cout << "Couldn't find a channel " << endl;
					return false;
			}
				else{
					vector<int> tries;
					tries.push_back(node2channel);
					node2channel = wn2[count];
					node3channel = node2channel;
					//cout << "New channel names " << node2channel << " | " << node3channel << endl;
					//cout << "New channels" << n2.checkChannelStatus(node2channel) << " | " << n3.checkChannelStatus(node3channel) << endl;
				}
			}
			cerr << "Found channels for last two nodes/3 " << endl;
	 		// The channel selections are available
	 		if(!this->reserveChannel(node1channel)){
				cout << "Couldn't reserve channel on " << getName() << endl;
			return false;
			}
			if(!n2.reserveChannel(node2channel)){
				return false;
			}
			if(!n2.reserveChannel(node3channel)){
				return false;
			}
			if(!n3.reserveChannel(node3channel)){
				return false;
			}
			else {
				cout << "Channels are  now reserved " << endl;
				fullroutes.at(0).at(i) = returnNode();
				fullroutes.at(0).at(i+1) = n2;
				fullroutes.at(0).at(i+2) = n3;
				return true;
			}

		}
	}
}

vector<vector<Node>> Node::getRoutes(){ // get the routes taken by the node
	return fullroutes;
}

void Node::testRouteGen(Node &n1, Node &n2, Node &n3){ // Test Function
    vector<Node> path_track;
    path_track.push_back(n1);
	path_track.push_back(n2);
	path_track.push_back(n3);

    n1.fullroutes.push_back(path_track);
}


void Node::graphGenerationAlgo(Node startNode, Node endNode){//during the first call of the function
    vector<Node> path_track;
    path_track.push_back(startNode);
    for(auto nodecheck : routes){
         if (nodecheck.second.name == endNode.name){
            path_track.push_back(nodecheck.second);
            fullroutes.push_back(path_track);
        }
         else if (nodecheck.first.name == startNode.name){
                path_track.push_back(nodecheck.second);
                graphGenerationAlgo(nodecheck.second, endNode, path_track);
            }
    }
}

void Node::graphGenerationAlgo(Node startNode, Node endNode, vector<Node> path){//this is called during all subsequent function calls
    for(auto nodecheck : routes){
        if (nodecheck.second.name == endNode.name){
            path.push_back(nodecheck.second);
            fullroutes.push_back(path);
        }
        else if (nodecheck.first.name == startNode.name){
                if (pathCheck(nodecheck.second, path) == true){
                    path.push_back(nodecheck.second);
                    graphGenerationAlgo(nodecheck.second, endNode, path);
                }
            }
        }
    }

void Node::nodesInRange(Node & initialNode, vector<Node> & allNodes){
    for (auto & theNode : allNodes){
      //  if (initialNode.name != theNode.name){
        //    int distance = distanceFormula(initialNode.position.first, initialNode.position.second, theNode.position.first, theNode.position.second);
        //    if (distance <= initialNode.radius){
        //        vector<Node> replaceVec;
        //    	pair<Node,Node> inrange(initialNode, theNode);
        //        initialNode.adjlist.push_back(inrange);
        //        replaceVec.push_back
        //    }
        //}
    }
       /* for (auto & subNodes : initialNode.adjlist){
                cout<<"the intit node "<<initialNode.name<<'\n';
                cout<<"the sub node " <<subNodes.second.name<<'\n';
            if(subNodes.second.adjlist.empty()){
                nodesInRange(subNodes.second, allNodes);
            }
        }*/
}




bool Node:: pathCheck(const Node & nextNode, const vector<Node> & path){
    for (auto visited : path){
        if (visited.name == nextNode.name){
            return false;
        }
    }
    return true;
}
