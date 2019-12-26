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
Node &Node::operator=(const Node &oldnode){ // copy constructor
	position.first = oldnode.position.first;
	position.second = oldnode.position.second;
	radius = oldnode.radius;
	name = oldnode.name;
	prevlistchannel = oldnode.prevlistchannel;
	listeningchannel = oldnode.listeningchannel;
	sendingchannel = oldnode.sendingchannel;
	vector<pair<Node,Node>> routes; // Vector that contains the current routes through node
	vector<vector<Node>> fullroutes;//passes back a list of all the routes from the start to the destination
	vector<vector<Hop>> results;	
	Channels.clear();
	adjlistsstring.clear();
	fullroutesstring.clear();
	adjlist.clear();
	results.clear();
	for (size_t i = 0; i < oldnode.Channels.size(); i++)
	{
	//	cout << "copying over the old channels for node " << oldnode.name<< endl;
		Channels.push_back(oldnode.Channels.at(i));
	}
	for (size_t i = 0; i < oldnode.adjlist.size(); i++)
	{
		adjlist.push_back(oldnode.adjlist.at(i));
	}
		for (size_t i = 0; i < oldnode.fullroutesstring.size(); i++)
	{
		fullroutesstring.push_back(oldnode.fullroutesstring.at(i));
	}
		for (size_t i = 0; i < oldnode.adjlistsstring.size(); i++)
	{
		adjlistsstring.push_back(oldnode.adjlistsstring.at(i));
	}	
		for (size_t i = 0; i < oldnode.results.size(); i++)
	{
		results.push_back(oldnode.results.at(i));
	}		
}
Node& Node::returnNode(){
	return *this;
}
bool Node::existsinAdjList(string name){
	for (size_t i = 0; i < adjlistsstring.size(); i++)
	{
		if(name.at(0) == adjlistsstring.at(i)){
			return true;
		} 
	}
	return false;
	
}
Node& Node::findNodeInAdjList(string &nodename){
//	cout << "Looking for node " << nodename << " in the adjlist of node " << getName() << endl;
//	cout << " out of a total adjlist of " << adjlist.size() << endl;
	for (size_t i = 0; i <adjlist.size(); i++) // Iterate through adj list to find the node needed
	{
		auto currentnode = adjlist.at(i);
	//	cout << currentnode.first.getName() << " | " << currentnode.second.getName() << endl; 
		if(currentnode.second.getName() == nodename){
	//		cout << "Found a dest node, now returning it" << endl;
			return adjlist.at(i).second;
		}
		else if(currentnode.first.getName() == nodename){
		//	cout << "Found a src node, now returning it" << endl;
			return adjlist.at(i).first;
		}		
	}
//	cout << "Couldn't find one " << endl;
}
void Node::updateNodeinAdjList(Node &node){
//	cout << " currently in node  " << getName() << " out of a total adjlist of " << adjlist.size() << " updating it with values of " << node.getName() << endl;
//	cout << "The status of the node with new values that will update the other nodes " << endl;
//	node.getAllChannelsStatus();
//	cout << endl;	
	for (size_t i = 0; i <adjlist.size(); i++) // Iterate through adj list to find the node needed
	{
		auto currentnode = adjlist.at(i);
//		cout << currentnode.first.getName() << " ||| " << currentnode.second.getName() << endl;
		if(currentnode.first.getName() == node.getName()){
//			cout << "Updating the src node in the adj list of node " << getName() << endl;

			adjlist.at(i).first = node;
//			cout << "status after " << endl;
		}
		if(currentnode.second.getName() == node.getName()){
//			cout << "Updating the dest node in the adj list of node " << getName() << endl;
//			cout << "status before " << endl;
			adjlist.at(i).second = node;
//			cout << "status after " << endl;
		}		
	}
	
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


bool Node::getBiggerWeight(Pair w1, Pair w2){

	return(w1.second > w2.second);

}

vector<pair<int,int>> Node::SortedWeightsByBest(){ // Returns a channel list by weight order
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
		bestchannels.push_back(channelsandweights.at(i).second);
	}
	bestChannelIds = bestchannels;
	return channelsandweights;
}
int Node::getChannelName(){ // get the name of the channel

}
vector<int> Node::getChannelWeights(){// get the channel weights for current node
	vector<int> currentChannelsWeights;
	for(int i = 0; i < Channels.size(); i++){
		currentChannelsWeights.push_back(Channels[i].weight);
	}
	return currentChannelsWeights;
}
vector<bool> Node::getAllChannelsStatus(){ // get all the channel use status for the current node
	vector<bool> currentChannelUse;
	//cout << "This is the current channel status of node " << getName() << endl;
	for(int i = 0; i < Channels.size(); i++){
	//	cout << i << " current status of that channel is " << checkChannelStatus(i) << endl;
		currentChannelUse.push_back(checkChannelStatus(i));
	}
	return currentChannelUse;
}
vector<int> Node::getAllChannels(){// get all the channels
	vector<int> allchannels;
	for(int i = 0; i < Channels.size(); i++){
		allchannels.push_back(checkChannelStatus(i));
	}
	return allchannels;
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
//	Co-channel 			interference --- Implemented
//	Adj Channel 		interference --- Implemented
// 	Exposed terminal 	problem		 ---  Implemented?
int Node::getBestAvailableChannel(vector<int> &channelstoskip){ // get the best currently available channel for current node

	vector<pair<int,int>> bestChannels = SortedWeightsByBest();
	vector<pair<int,int>> validChannels;
	vector<int> allchannels = getAllChannels();
	bool channelfound = false;
	int bestchannel = -1;
	for (size_t i = 0; i < channelstoskip.size(); i++)
	{
		for (size_t j = 0; j < bestChannels.size(); j++)
		{
			if(channelstoskip.at(i) == bestChannels.at(j).second){
	//			cout << "erasing " << bestChannels.at(j).second << endl;
				bestChannels.erase(bestChannels.begin()+j);
			}
		}
		
	}

	for(int i = 0; i < bestChannels.size(); i++){
	//	cout << "Valid channel is " << bestChannels.at(i).second << endl;
		validChannels.push_back(bestChannels[i]);
	}
	if(validChannels.size() == 0){
		//cout << "No valid channels" << endl;
		return -1;
	}
	for (size_t i = 0; i < validChannels.size(); i++)
	{

		bestchannel = validChannels[i].second;
	//	cout << " this is the first best channel out of valid channels  " << bestchannel << endl;
		return bestchannel;
	}

	// At the first channel
	if(!channelfound){
		return -1;
	}
	else
		return bestchannel;
}
bool Node::reserveChannel(int num,string nodename){
//	cout << "Reserving channel " << num << " for node " << getName() << endl;
	if(num > Channels.size()){
		return false;
	}
	else
	{
		Channels[num].used = true;
		Channels[num].usedby = nodename;
	//	cerr << "Channel reserved " << endl;		
		return true;
	}


}

void Node::releaseChannel(int num){
	if(num > Channels.size()){
		//cout << "Error that channel doesnt exist";
	}
	else
	{
		cout << "Releasing channel " << num << "for node " << getName() << endl;
		cerr << "Releasing channel " << num << "for node " << getName() << endl;
		Channels[num].used = false;
		Channels[num].usedby = "";
	}

}
int Node::getSendingChannel(){ // get the sending channel used by the node
	return sendingchannel;
}
void Node::setSendingChannel(int channel){ // set the channel the node is currently transmitting on
	sendingchannel = channel;
}
int Node::getListeningChannel(){ // get the listening channel used by the node
	//cout << listeningchannel << " is the listning channel for node " << getName() << endl;
	return listeningchannel;
}
void Node::setListeningChannel(int channel){ // set the channel the node is currently receieving on
	//cout << channel << " is the new listening channel for node " << getName() << endl;

	listeningchannel = channel;
}
int Node::getPrevListeningChannel(){ // get the listening channel used by the node
	//cout << prevlistchannel << " is the prev listning channel for node " << getName() << endl;
	return prevlistchannel;
}
void Node::setPrevListeningChannel(int channel){ // set the channel the node is currently receieving on
	//cout << channel << " is the new prev listening channel for node " << getName() << endl;

	prevlistchannel = channel;
}

void Node::setDestNode(string destnodename,int channelid){
	Channels[channelid].usedby = destnodename;
}

string Node::getDestNode(int channel){
	for (size_t i = 0; i < Channels.size(); i++)
	{
		if(i == channel){
			return Channels[channel].usedby;
		}
	}
}
int Node::getDestChannelBySrcNode(string nodename){
	for (size_t i = 0; i < Channels.size(); i++)
	{
		if(Channels.at(i).usedby == nodename){
			return Channels.at(i).id;
		}
	}
}

bool Node::checkChannelStatus(int num){ // check status of a channel

	if(num > Channels.size()){
		//cout << "Error that channel doesnt exist " << num << endl;
		return -1;
	}
	else if (Channels.size() > 11){
		//cout << "problem" << 1 << endl;
		return -1;
	}
	else
	{
		return Channels[num].used;
	}
}
int Node::checkChannelWeight(int num){ // check weight of a channel
	if(num > Channels.size()){
		//cout << "Error that channel doesnt exist";
		return -1;
	}
	else
	{
		return Channels[num].weight;
	}
}
int Node::helpCreateRoute(vector<int> &channelstoskip){ // keep trying next best with no repeats
	auto sortedchannels = SortedWeightsByBest();
	vector<int> tries;
	int channel = 0;
	bool used = false;
	for (size_t i = 0; i < sortedchannels.size(); i++)
	{
		if(!used){
				used = checkChannelStatus(sortedchannels[i].second);
				channel = getBestAvailableChannel(channelstoskip);
				used = true;
				break; 
		}
	}
	//cout << "help create route chose " << channel << endl;
	return channel;
}


bool Node::oneHopHelper(int startnodeindex,string route,vector<Node> &allnodes){
//	cout << "In one hop helper " << endl;
	auto bestChannels = SortedWeightsByBest();

	vector<vector<Hop>> hopsresult;

	vector<Hop> currenthop;
	int node1channel = -1;
	int node2channel = -1;
	//Get the first and only two nodes 

	string firstnodename = string(1,route.at(0));
	string node1name = string(1,route.at(startnodeindex));
	string destnodename = string(1,route.at(startnodeindex+1));

	bool firstnodeexists = false;
	bool node1exists = false;
	bool destnodeexists = false;	

	Node firstnode, n1, destnode;

	//Check if the node is listed
	for (size_t i = 0; i < allnodes.size(); i++)
		{
			if(allnodes.at(i).existsinAdjList(firstnodename) && !firstnodeexists){ // Node contains the first node in its adj list
				firstnode = allnodes.at(i).findNodeInAdjList(firstnodename);
				firstnodeexists = true;
			}
			if(allnodes.at(i).existsinAdjList(node1name) && !node1exists){ // Node contains the 1st node in its adj list
				n1 = allnodes.at(i).findNodeInAdjList(node1name);
				node1exists = true;
			}
			if(allnodes.at(i).existsinAdjList(destnodename) && !destnodeexists){ // Node contains the dest node in its adj list
				destnode = allnodes.at(i).findNodeInAdjList(destnodename);
				destnodeexists = true;
			}							
		}
	if(!firstnodeexists || !node1exists || !destnodeexists){
			return false;
	}
		auto wn1 = n1.SortedWeightsByBest(); // Node 1
		auto wn2 = destnode.SortedWeightsByBest(); // Node 2

		//Get the best channel 

		vector<int> channelstoskipn2;
		channelstoskipn2.clear();
	//	cout << "Getting all channel status of n1 in onehophelper " << endl;
		auto allchannelsn1 = n1.getAllChannelsStatus();
		//Adj channel logic doesnt work
		// Go through the existing first node and make sure to not choose any channels in use at n1
		for (size_t i = 0; i < allchannelsn1.size(); i++)
		{
			if(allchannelsn1[i]==1 && i > 0){
			//	cout << "Avoiding adj interference avoiding ( ) for first hop  " << i+1 << endl;
			//	cout << "Avoiding adj interference avoiding ( ) for first hop  " << i-1 << endl;
				channelstoskipn2.push_back(i);
				channelstoskipn2.push_back(i-1);
				channelstoskipn2.push_back(i+1);
			}
			else if(i == 0 && allchannelsn1[i]==1){
			//	cout << "Avoiding adj interference avoiding ( ) for first hop i = 0  " << i+1 << endl;
				channelstoskipn2.push_back(i);
				channelstoskipn2.push_back(i+1);
			}
		}
		auto allchannelsn2 = destnode.getAllChannelsStatus();
		//Adj channel logic doesnt work
		// Go through the existing second node and make sure to not choose any channels in use at n1
		for (size_t i = 0; i < allchannelsn2.size(); i++)
		{
			if(allchannelsn2[i]==1 && i > 0){
			//	cout << "Avoiding adj interference avoiding ( ) for first hop  " << i+1 << endl;
			//	cout << "Avoiding adj interference avoiding ( ) for first hop  " << i-1 << endl;
				channelstoskipn2.push_back(i);
				channelstoskipn2.push_back(i-1);
				channelstoskipn2.push_back(i+1);
			}
			else if(i == 0 && allchannelsn2[i]==1){
			//	cout << "Avoiding adj interference avoiding ( ) for first hop i = 0  " << i+1 << endl;
				channelstoskipn2.push_back(i);
				channelstoskipn2.push_back(i+1);
			}
		}	
		node1channel = n1.helpCreateRoute(channelstoskipn2);
		n1.setSendingChannel(node1channel);		

		if(node1channel == -1){
			return false;
		}

	//	channelstoskipn2.push_back(node1channel);

	//	cout << "avoiding prev listening channel for n1 " << n1.getPrevListeningChannel() << endl;

		channelstoskipn2.push_back(n1.getPrevListeningChannel());
		
	//	channelstoskipn2.push_back(n1.getSendingChannel());	

	//	cout << "Looking for the best channel for destnode " << endl;
		
		node2channel = destnode.getBestAvailableChannel(channelstoskipn2);

	//	cout << "this is the 2nd node channel used " << node2channel << endl;

		if(node2channel == -1){
			return false;
		}


		int count = 0;
		while (checkChannelStatus(node1channel) == 1 || destnode.checkChannelStatus(node2channel) == 1 && count <= destnode.Channels.size())
		{
			//cout << " The requested channel is not available for both nodes trying again " << endl;
			node1channel = wn1[count].second;
			channelstoskipn2.clear();
			channelstoskipn2.push_back(node1channel+1);
			channelstoskipn2.push_back(node1channel+2);
			channelstoskipn2.push_back(n1.getPrevListeningChannel());
			channelstoskipn2.push_back(n1.getSendingChannel());			
			node2channel = destnode.getBestAvailableChannel(channelstoskipn2);
			count ++;
		}
		// The channel selections are available
		if(!n1.reserveChannel(node2channel,destnode.getName())){
			//cout << "Couldn't reserve channel on " << getName() << endl;
			return false;
		}
		if(!destnode.reserveChannel(node2channel,n1.getName())){
			n1.releaseChannel(node2channel);
			//cout << "Couldn't reserve channel on " << getName() << endl;
			return false;
		}
		else {
		//	cout << "Both Channels are now reserved " << node1channel << " | " << node2channel<< endl;

			n1.setSendingChannel(node1channel);
			destnode.setListeningChannel(node1channel);

			n1.setDestNode(destnode.getName(),node2channel);
			destnode.setDestNode(n1.getName(),node2channel);

			Hop hop1;

			hop1 = make_tuple(n1.getName(),node2channel,n1.getDestNode(node2channel));

			std::vector<Hop> path = {hop1};
			// Update the nodes along the route
			//firstnode.addToResults(path);

			for (size_t i = 0; i < allnodes.size(); i++)
			{
				if(allnodes.at(i).getName() == firstnodename){
					allnodes.at(i).Channels.clear();
					allnodes.at(i).addToResults(path);			
				}
				if(allnodes.at(i).getName() == node1name){
					allnodes.at(i).Channels.clear();
					for (size_t j = 0; j < n1.Channels.size(); j++)
					{
						allnodes.at(i).Channels.push_back(n1.Channels.at(j));
					}					
				}
				if(allnodes.at(i).getName() == destnodename){
					allnodes.at(i).Channels.clear();
					for (size_t i = 0; i < destnode.Channels.size(); i++)
					{
						allnodes.at(i).Channels.push_back(destnode.Channels.at(i));
					}	
				}	
				if(allnodes.at(i).existsinAdjList(firstnodename)){ // Node contains the first node in its adj list
					//cout << "first node exists in adj list" << endl;
					allnodes.at(i).updateNodeinAdjList(firstnode);
				}							
				if(allnodes.at(i).existsinAdjList(node1name)){ // Node contains the first node in its adj list
					//cout << "node 1 exists in adj list" << endl;
					allnodes.at(i).updateNodeinAdjList(n1);
				}
				if(allnodes.at(i).existsinAdjList(destnodename)){ // Node contains the dest node in its adj list
					//cout << "dest node exists in adj list" << endl;
					allnodes.at(i).updateNodeinAdjList(destnode);
				}								
			}
			return true;
		}	

	
}

bool Node::twoHopHelper(int start,string route,vector<Node> &allnodes)
{	
	//cout << "In two hop helper " << endl;
	//cout << "start " <<start << " route " << route << endl;
	vector<int> allchannels = getAllChannels();
	auto test = Channels;
	vector<Hop> n1ton2hops;
	vector<Hop> n2ton3hops;
	vector<vector<Hop>> hopsresult;

	bool channelsreserved = false;

	string firstnodename = string(1,route.at(0));
	string node1name = string(1,route.at(start));
	string node2name = string(1,route.at(start+1));
	string node3name = string(1,route.at(start+2));

	bool firstnodeexists = false;
	bool node1exists = false;
	bool node2exists = false;
	bool node3exists = false;

	Node firstnode, n1, n2, n3;

		for (size_t i = 0; i < allnodes.size(); i++)
		{
			if(allnodes.at(i).existsinAdjList(firstnodename)){ // Node contains the first node in its adj list
				firstnode = allnodes.at(i).findNodeInAdjList(firstnodename);
				firstnodeexists = true;
			}
			if(allnodes.at(i).existsinAdjList(node1name)){ // Node contains the 1st node in its adj list
				n1 = allnodes.at(i).findNodeInAdjList(node1name);
				node1exists = true;
			}
			if(allnodes.at(i).existsinAdjList(node2name)){ // Node contains the 2nd node in its adj list
				n2 = allnodes.at(i).findNodeInAdjList(node2name);
				node2exists = true;
			}
			if(allnodes.at(i).existsinAdjList(node3name)){ // Node contains the 3rd node in its adj list
				n3 = allnodes.at(i).findNodeInAdjList(node3name);
				node3exists = true;
			}									
		}
		if(!firstnodeexists || !node1exists || !node2exists || !node3exists){
			return false;
		}
		
		auto wn1 = n1.SortedWeightsByBest(); // Node 1
		auto wn2 = n2.SortedWeightsByBest(); // Node 2
		Hop hop1, hop2 ;	
		int i = start;
			if(!channelsreserved){
				int node1channel = -1;
				int node2channel = -1;
				int node3channel = -1;
				//Get the first three nodes 

				auto wn1 = n1.SortedWeightsByBest(); // Node 1
				auto wn2 = n2.SortedWeightsByBest(); // Node 2
				auto wn3 = n3.SortedWeightsByBest(); // Node 2
				vector<int> channelstoskipn1;

				channelstoskipn1.push_back(-1);

				//cout << "Getting all channel status of n1 in twohophelper " << endl;
				auto allchannelsn1 = n1.getAllChannelsStatus();
				for (size_t i = 0; i < allchannelsn1.size(); i++)
				{
					if(allchannelsn1[i]==1 && i > 0){
						channelstoskipn1.push_back(i);	
						channelstoskipn1.push_back(i-1);
						channelstoskipn1.push_back(i+1);
					}
					else if(i == 0 && allchannelsn1[i]==1){
						channelstoskipn1.push_back(i);	
						channelstoskipn1.push_back(i+1);		
					}				
				}
				channelstoskipn1.push_back(n1.getPrevListeningChannel());
				node1channel = n1.helpCreateRoute(channelstoskipn1); // Assign a channel for node 1
				if(node1channel == -1){
					return false;
				}


				vector<int> channelstoskipn2;
			//	channelstoskipn2.push_back(node1channel); // Avoid Co channel interference with node 1 and node 2 
				channelstoskipn2.push_back(node1channel-1);
				channelstoskipn2.push_back(node1channel+1);				

				//cout << "Getting all channel status of n2 in twohophelper " << endl;
				auto allchannelsn2 = n2.getAllChannelsStatus();
				for (size_t i = 0; i < allchannelsn2.size(); i++) // Check all channels of n2 and see if they are in use atm
				{
					if(allchannelsn2[i]==1 && i > 0){
						//cout << "Avoiding adj interference avoiding ( ) for second node in first hop/2  " << i+1 << endl;
						//cout << "Avoiding adj interference avoiding ( ) for second node in first hop/2  " << i-1 << endl;	
						channelstoskipn2.push_back(i);
						channelstoskipn2.push_back(i-1);
						channelstoskipn2.push_back(i+1);
					}
					else if(i == 0 && allchannelsn2[i]==1){
						//cout << "Avoiding adj interference avoiding ( ) for second node in first hop/2 i = 0  " << i+1 << endl;
						channelstoskipn2.push_back(i);
						channelstoskipn2.push_back(i+1);		
					}
				}

				channelstoskipn2.push_back(n1.getSendingChannel());
				channelstoskipn2.push_back(n1.getPrevListeningChannel());			
				node2channel = n1.helpCreateRoute(channelstoskipn2);
				if(node2channel == -1){
					return false;
				}
				vector<int> channelstoskipn3;

				channelstoskipn3.push_back(node2channel); // Avoid co channel interference
				channelstoskipn3.push_back(node1channel); // Avoid exposed problem with node
				channelstoskipn3.push_back(node2channel-1);
				channelstoskipn3.push_back(node2channel+1);		

				//cout << "Getting all channel status of n3 in twohophelper " << endl;
				auto allchannelsn3 = n3.getAllChannelsStatus();
				
				for (size_t i = 0; i < allchannelsn3.size(); i++)
				{
					if(allchannelsn3[i]==1 && i > 0){
						//cout << "Avoiding adj interference avoiding ( ) for second hop  " << i+1 << endl;
						//cout << "Avoiding adj interference avoiding ( ) for second hop  " << i-1 << endl;
						channelstoskipn3.push_back(i);
						channelstoskipn3.push_back(i-1);
						channelstoskipn3.push_back(i+1);
					}
					else if(i == 0 && allchannelsn3[i]==1){
						//cout << "Avoiding adj interference avoiding ( ) for first hop  " << i+1 << endl;
						channelstoskipn3.push_back(i);
						channelstoskipn2.push_back(i+1);
					}
				}
				node3channel = n3.getBestAvailableChannel(channelstoskipn3); // find a channel thats not used on node 1 and 2

				if(node3channel == -1){ // No point in trying if node 3 has no channels available
					return false;
				}

				int count = 0;
				while (checkChannelStatus(node1channel) == 1 || n2.checkChannelStatus(node2channel) == 1 && count < wn1.size()) // Channel is not avail for n1 or n2
				{
					channelstoskipn2.clear();
					node1channel = wn1[count].second;
					channelstoskipn2.push_back(count+1);
					channelstoskipn2.push_back(count-1);
					node2channel = n2.getBestAvailableChannel(channelstoskipn2);
					//	cout << "New channel names " << node1channel << " | " << node2channel << endl;
						//cout << "New channels" << checkChannelStatus(node1channel) << " | " << n2.checkChannelStatus(node2channel) << endl;
					count ++;
				if(count >= wn1.size()){
					//cout << "Couldn't find a channel cout > wn1 " << endl;
					return false;
				}
				}
				//	cout << "Found channels for first two nodes/3" << endl;
				//	cout << "current channels stat " << n2.checkChannelStatus(node2channel) << " | " << n2.checkChannelStatus(node3channel) << " | " << n3.checkChannelStatus(node3channel) << endl;
				count = 0;
				while (n2.checkChannelStatus(node2channel) == 1 || n2.checkChannelStatus(node3channel) == 1 || n3.checkChannelStatus(node3channel) == 1 && count < wn2.size()-1)
				{
					channelstoskipn3.clear();
					if(count > wn2.size()-1){
						//	cout << "Couldn't find a channel > wn2 " << endl;
						return false;
					}
					else{
						node2channel = wn2[count].second;
						channelstoskipn3.push_back(node1channel);
						channelstoskipn3.push_back(node2channel+1);
						channelstoskipn3.push_back(node2channel-1);
						node3channel = n3.getBestAvailableChannel(channelstoskipn3);
						count ++; // avoid loop
					}
				}

				//cout << "Found channels for last two nodes/3 " << endl;
				// The channel selections are available
				if(!n1.reserveChannel(node1channel,n2.getName())){
					return false;
				}
				else if(!n2.reserveChannel(node2channel,n1.getName())){
					n1.releaseChannel(node1channel);
					return false;
				}
				else if(!n2.reserveChannel(node3channel,n3.getName())){
					n1.releaseChannel(node1channel);
					n2.releaseChannel(node2channel);
					return false;
				}
				else if(!n3.reserveChannel(node3channel,n2.getName())){
					n1.releaseChannel(node1channel);
					n2.releaseChannel(node2channel);
					n2.releaseChannel(node3channel);
					return false;
				}
				else {
					//cerr << "test again " << endl;
					//	cout << "All 4 Channels are now reserved " << endl;
					// Set the destnode for nodes involved
					n1.setDestNode(n2.getName(),node1channel);
					n2.setDestNode(n1.getName(),node2channel);
					n2.setDestNode(n3.getName(),node3channel);
					n3.setDestNode(n2.getName(),node3channel);

					
					n1.setSendingChannel(node1channel);
					n2.setListeningChannel(node1channel);
					n2.setSendingChannel(node2channel);
					n3.setListeningChannel(node3channel);
					n3.setPrevListeningChannel(node1channel);


					// Check that destination 	set correctly
					n1.getDestNode(node1channel);
					n2.getDestNode(node2channel);
					n2.getDestNode(node3channel);
					n3.getDestNode(node3channel);

					hop1 = make_tuple(n1.getName(),node1channel,n1.getDestNode(node1channel));
					hop2 = make_tuple(n2.getName(),node3channel,n2.getDestNode(node3channel));

					std::vector<Hop> path = {hop1,hop2};
					// Update the nodes along the route
					//firstnode.addToResults(path);

					for (size_t i = 0; i < allnodes.size(); i++)
					{
						if(allnodes.at(i).getName() == firstnodename){
							allnodes.at(i).Channels.clear();
							allnodes.at(i).addToResults(path);			
						}
						if(allnodes.at(i).getName() == node1name){
							allnodes.at(i).Channels.clear();
							for (size_t j = 0; j < n1.Channels.size(); j++)
							{
								allnodes.at(i).Channels.push_back(n1.Channels.at(j));
							}					
						}
						if(allnodes.at(i).getName() == node2name){
							allnodes.at(i).Channels.clear();
							for (size_t i = 0; i < n2.Channels.size(); i++)
							{
								allnodes.at(i).Channels.push_back(n2.Channels.at(i));
							}	
						}
						if(allnodes.at(i).getName() == node3name){
							allnodes.at(i).Channels.clear();
							for (size_t i = 0; i < n3.Channels.size(); i++)
							{
								allnodes.at(i).Channels.push_back(n3.Channels.at(i));
							}	
						}													
						if(allnodes.at(i).existsinAdjList(firstnodename)){ // Node contains the first node in its adj list
							allnodes.at(i).updateNodeinAdjList(firstnode);
						}
						if(allnodes.at(i).existsinAdjList(node1name)){ // Node contains the 1st node in its adj list
							allnodes.at(i).updateNodeinAdjList(n1);
						}
						if(allnodes.at(i).existsinAdjList(node2name)){ // Node contains the dest node in its adj list
							allnodes.at(i).updateNodeinAdjList(n2);
						}	
						if(allnodes.at(i).existsinAdjList(node3name)){ // Node contains the dest node in its adj list
							//cout << "Found a matching node for node 3 in an adj list " << endl;
							allnodes.at(i).updateNodeinAdjList(n3);
						}														
					}

					if(i <= fullroutesstring.at(0).size()-3){
						channelsreserved = true;
						//cout << "Channel is now reserved " << channelsreserved <<endl;
					//	cerr << "Channel is reserved" << endl;
					}
				}
			}	
		if(channelsreserved){
			//cout << " after total number of hops = " << n1.results.size() <<endl; 
			return channelsreserved;
		}
		if(!channelsreserved)
			return false;
	
}	
bool Node::createRoute(Node &destnode,vector<Node> &allnodes){ // Create a new route between three nodes
	vector<vector<Hop>> everyhop;
	vector<Node> oldnodes;

	for (size_t i = 0; i < allnodes.size(); i++)
	{
		oldnodes.push_back(allnodes.at(i));	
	}
	
	vector<Hop> allhops;	
	string routetouse;
	bool routecreated = false;
	// No possible routes to this node
	if(fullroutesstring.size() == 0){
		return false;
	}
	for (size_t i = 0; i < fullroutesstring.size(); i++)
	{
		if(routecreated){
			return true;
		}
		if(i > 0)
			cout<< "Previous path failed trying the next one " << endl;
		if(string(1,fullroutesstring.at(i).at(0)) == getName() && string(1,fullroutesstring.at(i).at(fullroutesstring.at(i).size()-1)) == destnode.getName() && !routecreated ){
			cout << "Current path meets src / dest node requirement, trying that path now. Path: " << i << " out of " <<fullroutesstring.size()-1 << endl;
			routetouse = fullroutesstring.at(i); 
			int routesize = routetouse.size();
			if(routesize <= 1){
				//cout << "No route passed" << endl;
				return false;
			}
			auto test = fullroutesstring.at(0);
			if(routesize == 2){
				routecreated = oneHopHelper(0,routetouse,allnodes);
			}
			else{
			//	cerr << "Splitting route into groups of hops" << endl;
				bool resultone = false;
				bool resulttwo = false;
				bool resulttwofirstgroup = false;
				bool routeoneneeded = false;
				bool routetwoneeded = false;
				//Check if 
				for (size_t i = 0; i <= routesize-2; i+=2)
				{
				//	cout << "at hop " << i << " route to use is " << routetouse << "out of " << fullroutesstring.size()<<  endl;

					if(i == 0){ // group of three and at end of list of routes
						//cout << "3current i value " << i << endl ;
						resulttwofirstgroup = twoHopHelper(i,routetouse,allnodes);
						//cerr << "result of two hop helper at i = 0 " << resulttwofirstgroup << endl;
						resulttwo = resulttwofirstgroup;
						routetwoneeded = true;
					}
					else if(routesize%2 == 0 && i== routesize-2 && resulttwo){ 
						//cout << "1current i value " << i << endl ;
						resultone = oneHopHelper(i,routetouse,allnodes);
						//cerr << "result of onehophelper " << resultone << endl;
				
						routetwoneeded = true;
						routeoneneeded = true;
					}
					else if(routesize%2 == 1 && i ==routesize-3){ // group of three and at end of list of routes
						if(resulttwofirstgroup){ // The first group of hops done
							//cout << "2current i value " << i << endl ;	
							resulttwo = twoHopHelper(i,routetouse,allnodes);
							//cerr << "result of two hop helper at last group of 3 " << resulttwo << endl;
							routetwoneeded = true;
						}
						else
						{
							resulttwo = false; // Dont try if the first group doesnt work
						}
						
					}
					else if(resulttwo && i>3)
					{
						//cerr << "4current i value " << i << endl ;
						resulttwo = twoHopHelper(i,routetouse,allnodes);
						//cerr << "result of two hop helper at i >3 " << resulttwo << endl;
						routetwoneeded = true;
					}
								
				}
				//cerr << "Done going through all of the hops " << routeoneneeded << " " << routetwoneeded << endl;
				if(routetwoneeded && routeoneneeded){
					routecreated = (resultone && resulttwo);
					if(!routecreated && results.size() > 0){
						cerr << "No route created " << endl;
						for (size_t i = 0; i < allnodes.size(); i++)
						{
							allnodes.at(i) = oldnodes.at(i);
						}						
					}
				}
				if(routetwoneeded && !routeoneneeded){
					routecreated = resulttwo;
					if(!routecreated){
						for (size_t i = 0; i < allnodes.size(); i++)
						{
							allnodes.at(i) = oldnodes.at(i);
						}
						cerr<< "No route created both hops only  failed " << endl;
					}
				}
				if(!routetwoneeded && routeoneneeded){
					routecreated = resultone;
					if(!routecreated){
						for (size_t i = 0; i < allnodes.size(); i++)
						{
							allnodes.at(i) = oldnodes.at(i);
						}						
						cerr << "No route created one hop failed " << endl;
					}					
				}
			}			
		}
		else
		{
			cout << "Current path does not meet src / dest requirement" << endl;
		}		
		
	}
	if(routecreated){
		return true;
	}
	else
	{
		cout << "No possible route out of all routes " << endl;
		return false;
	}
}

vector<vector<Node>> Node::getRoutes(){ // get the routes taken by the node
	return fullroutes;
}vector<string> Node::getRoutesString(){ // get the route taken by the node
	return fullroutesstring;
}

vector<vector<Hop>> Node::getResults(){
	//cout << "current size of results " << results.size() << endl;
	return results;
}
void Node::addToResults(vector<Hop> &hopstoadd){
	vector<Hop> mergedhops;
	//cout << "size of result before adding " << results.size() << endl;
	//cout << "adding hops to results " << hopstoadd.size() << " this is node " << getName() << endl;
	if(results.size() > 0){
		auto currentresult= results.at(results.size()-1); // Get the most recent result
		string currsrcid = get<0>(currentresult.at(0)); // Get the source node id
		string srcidhopstoadd = get<0>(hopstoadd.at(0)); // Get the source id of the new hops to add
		string destid = get<0>(currentresult.at(currentresult.size()-1)); // Get the destination id
		//cout << "Current last node id " << destid << endl;
		if(currsrcid == srcidhopstoadd){
			results.push_back(hopstoadd);
			currentresult = results.at(results.size()-1);
		}
		else
		{
			for (size_t t = 0; t < currentresult.size(); t++)
			{
				mergedhops.push_back(currentresult.at(t));
			}
			for (size_t h = 0; h < hopstoadd.size(); h++)
			{
				mergedhops.push_back(hopstoadd.at(h));
			}
				
			results.at(results.size()-1) = mergedhops;
			//cout << "size of mergd hops " << mergedhops.size() << endl;
			//cout << "size of result " << results.size() << endl;	
		}
	}
		// Check for the same path being abnormally shorter than the prior as it should always increase in hops
		
	else
	{
		results.push_back(hopstoadd);
	}	
} 

void Node::testRouteGen(Node &n1,Node &n2, Node &n3,Node &destNode){ // Test Function
    vector<Node> path_track;
	string path;
    path_track.push_back(n1);
	path + n1.getName();
	path_track.push_back(n2);
	path_track.push_back(n3);
	path_track.push_back(destNode);

	pair<Node,Node> tn1, tn2 , tn3, tdestNode;

	//cout << "size of adjlist is " << adjlist.size() << endl;

	tn1.first = n1;
	tn2.first = n1;
	tn3.first = n1;
	tdestNode.first = n1;

	tn1.second = n2;
	tn2.second = n3;
	tn3.second = destNode;

	n1.adjlist.push_back(tn1);
	n1.adjlist.push_back(tn2);
	n1.adjlist.push_back(tn3);

	path = path + n1.getName();
	path = path + n2.getName();	
	path = path + n3.getName();
	path = path + destNode.getName();	

	//cout << "adding path " << path << endl;
	fullroutesstring.push_back(path);
	//cout << "Length of adj list is " << adjlist.size() << endl;
    fullroutes.push_back(path_track);
}



void Node::graphGenerationAlgo(Node & startNode, Node & endNode, vector<Node>  noderef){//graph algo, the result of which will be stored within the starting node
    string PathFragment;
    vector<string> PathFragmentList;
    string nameRef(startNode.name);
        for (auto & node: noderef){
       // cout<<"hi";
        for (auto & subNodes : node.adjlist){
          //  cout<<subNodes.first.name<<'\n';
          //  cout<<subNodes.second.name<<'\n';
        }
        //cout<<'\n';
    }

        for (auto  node : noderef){

            if (!(node.adjlist.empty())){

                for (auto  adjNode: node.adjlist){
                    //cout<<node.name<<'\n';
                    //cout<<adjNode.second.name <<'\n';
                    PathFragment += node.name;
                    PathFragment += adjNode.second.name;
                    PathFragmentList.push_back(PathFragment);
                    PathFragment.clear();
                }
            }
        }
            mergePaths(startNode, endNode, PathFragmentList);

            for (auto  vec: startNode.fullroutes){
         //   cout<<"new path: ";
             //       cout<<vec;
          //      cout<<'\n';
       }
          //  cout<<"shortest path: " <<startNode.fullroutes[0];
}



void Node::nodesInRange(vector<Node> & allNodes){
    for(auto & initialNode : allNodes){
            initialNode.adjlist.reserve(10);
           // cout<<initialNode.name<<'\n';
        for (auto & theNode : allNodes){
            if (initialNode.name != theNode.name){
             //   cout<<theNode.name;
                int distance = distanceFormula(initialNode.position.first, initialNode.position.second, theNode.position.first, theNode.position.second);
                if (distance <= initialNode.radius){
                    pair<Node  ,Node  > inrange(initialNode, theNode);
                    initialNode.adjlist.push_back(inrange);
					initialNode.adjlistsstring = initialNode.adjlistsstring + inrange.first.getName();
					initialNode.adjlistsstring = initialNode.adjlistsstring + inrange.second.getName();

                }
            }
        }
    }
}



void Node:: mergePaths(Node & startNode, Node & endNode, vector<string>  currentPaths){//used within the graphAlgo to find and merge subpaths
    string pathUpdate;
    vector<string> allPathUpdate;
    allPathUpdate.reserve(100);
    int start(1);
    string firstPush{""};
	//cout<<"hi";
    for(auto initialcheck : currentPaths){

        if ((initialcheck[0] == startNode.name[0])&& (initialcheck.back() == endNode.name[0])){
            startNode.fullroutesstring.push_back(initialcheck);

        }
    }

    while ((start == 1) || ((newRoutePossible( startNode, endNode, currentPaths)) == true)){
            start = 0;

            for (auto route : currentPaths){
                if ((route[0] == (startNode.name[0])) && (route.back() != endNode.name[0])){

                    for(auto routeCheck : currentPaths){
                        if ((routeCheck[0] == route.back())&&(routeCheck[0] != endNode.name[0])){

                            for(auto stringchar : routeCheck){
                               if ((stringchar != route.back())&&(route[0] != routeCheck.back())){

                                    if (loopCheck(route, stringchar)){
                                        pathUpdate += route;
                                        pathUpdate.push_back(stringchar);

                                    }
                                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                               }
                               /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                               if ((pathUpdate.back() == endNode.name[0]) && (pathUpdate != firstPush)){

                                        startNode.fullroutesstring.push_back(pathUpdate);
                                        firstPush = pathUpdate;

                                        pathUpdate.clear();
                               }
                               //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                else if (!(deadEnd(pathUpdate, currentPaths))){
                                    allPathUpdate.push_back(pathUpdate);
                                    pathUpdate.clear();
                                }

                                else{

                                    pathUpdate.clear();
                                }
                            }
                        }
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    }
                }
                 else if((route[0] != startNode.name[0]) && (route[0] != endNode.name[0])){

                //    cout<<route<<'\n';
                    allPathUpdate.push_back(route);
                    pathUpdate.clear();
                }
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            }
            currentPaths = allPathUpdate;
            allPathUpdate.clear();
        }

   }


vector<Node> Node:: routeRequest(vector<Node> & givenNodeList, Node & startNode, int pathIndex){

    vector<Node> newRoute;

    for (auto & nodeonPath : startNode.fullroutes[pathIndex]){

         for (auto & nodebyRef : givenNodeList){
            if (nodeonPath.getName() == nodebyRef.getName()){
                newRoute.push_back(nodebyRef);
            }
         }
    }
    return newRoute;
}

bool Node:: newRoutePossible(Node & startNode , Node & endNode, vector<string>  currentPath){//used with graph algo to check  whether further routes are possible
    for (auto & route : currentPath){
        if (((route[0] == (startNode.name[0])) && (route.back() != endNode.name[0]))){
                return true;
        }
    }
    return false;
}

bool Node:: deadEnd(const string & path, const vector<string> & currentPaths){
    vector<string> newcurrent;
    for (auto & deadEnd : currentPaths){
    	if (path == deadEnd){
        	return true;
    	}
    }
    return false;
}

bool Node:: loopCheck(const string path, const char refChar){//prevents looping paths in the merge algo

    for (auto name : path){
            if (name == refChar){
                return false;
        }
    }
    return true;
}



float Node::distanceFormula(int & x1, int & y1, int & x2, int & y2){
    float distance = pow((x2 - x1), 2) + pow((y2 - y1), 2);
    distance = sqrt(distance);
    return distance;
}

