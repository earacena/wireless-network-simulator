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
		//	cout << "The best avail channel is " << channelsandweights.at(i).second << "with weight" << channelsandweights.at(i).first << endl;
		bestchannels.push_back(channelsandweights.at(i).second);
	}
	//	cout << "found the best channels for node " << getName() << endl;
	bestChannelIds = bestchannels;
	return channelsandweights;
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
vector<int> Node::getAllChannels(){// get all the free channels
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
	for (size_t i = 0; i < channelstoskip.size(); i++)
	{
		cout << "channel to skip are " << channelstoskip[i] << endl;
	}

	vector<pair<int,int>> bestChannels = SortedWeightsByBest();
	vector<pair<int,int>> validChannels;
	vector<int> allchannels = getAllChannels();
	bool channelfound = false;
	int bestchannel = -1;

	for(int i = 0; i < bestChannels.size(); i++){
		// Co-Channel Check
		for (size_t j = 0; j < channelstoskip.size(); j++)
		{
			if(bestChannels[i].second != channelstoskip[j])
			// && channelfound ==false && checkChannelStatus(bestChannels[i].second) == 0)// Channel available
			{
				validChannels.push_back(bestChannels[i]);
				//cout << bestChannels[i].second << " is the best available channel for node: " << getName() << endl;
				i++;
				//	channelfound = true;
			}
		}
	}
	cout << "Total number of valid channels " << validChannels.size() << endl;
	for (size_t i = 0; i < validChannels.size(); i++)
	{
		bestchannel = validChannels[i].second;
		return bestchannel;
	}

	// At the first channel
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

void Node::setDestNode(string destnodename,int channelid){
	Channels[channelid].usedby = destnodename;
}

string Node::getDestNode(int channel){
	for (size_t i = 0; i < Channels.size(); i++)
	{
		if(i == channel){
			cout << "Current Dest on Node " << getName() << " on channel " << i << "is " << Channels[channel].usedby << endl;
			return Channels[channel].usedby;
		}
	}
}
int Node::getDestChannelBySrcNode(string nodename){
	for (size_t i = 0; i < Channels.size(); i++)
	{
		if(Channels.at(i).usedby == nodename){
			cout << "Current Dest Node is " << Channels[i].usedby << endl;
			return Channels.at(i).id;
		}
	}
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
int Node::helpCreateRoute(vector<int> &channelstoskip){ // keep trying next best with no repeats
	auto sortedchannels = SortedWeightsByBest();
	vector<int> tries;
	int channel = 0;
	bool used = false;
	for (size_t i = 0; i < sortedchannels.size(); i++)
	{
		//
		cout << "is channel " << sortedchannels[i].second << " used " << used << endl;
		if(!used){
				used = checkChannelStatus(sortedchannels[i].second);
				channel = getBestAvailableChannel(channelstoskip);
				used = true;
			//		cout << "current status of chan " << channel << " " << used << endl;
				break;
		}
	}
	cout << "Found the best channel for the current node "<< getName() << " channel " << channel << endl;
	return channel;
}

bool Node::oneHopHelper(int startnodeindex,vector<Node> &routes){
	auto bestChannels = SortedWeightsByBest();

	vector<vector<Hop>> hopsresult;

	vector<Hop> currenthop;
	cout << "Only two left over nodes in path detected " << endl;
	int node1channel = -1;
	int node2channel = -1;

	//Get the first and only two nodes 

	Node n1 = routes.at(startnodeindex);
	cout << routes.size() << "all routes size , starting at node ( ) in path " << startnodeindex << n1.getName() << endl;	

	Node destnode = routes.at(startnodeindex+1);

	auto wn1 = n1.SortedWeightsByBest(); // Node 1
	auto wn2 = destnode.SortedWeightsByBest(); // Node 2

	//Get the best channel 
	cout << "Looking for best channel for nodes " << n1.getName() << " & " << destnode.getName() << endl;

	vector<int> channelstoskipn2;
	auto allchannelsn2 = destnode.getAllChannelsStatus();
	for (size_t i = 0; i < allchannelsn2.size(); i++)
	{
		if(allchannelsn2[i]==1 && i > 0){
			cout << "Avoiding adj interference avoiding ( ) for first hop  " << i+1 << endl;
			cout << "Avoiding adj interference avoiding ( ) for first hop  " << i-1 << endl;
			channelstoskipn2.push_back(i-1);
			channelstoskipn2.push_back(i+1);
		}
		else if(i == 0 && allchannelsn2[i]==1){
			cout << "Avoiding adj interference avoiding ( ) for first hop i = 0  " << i+1 << endl;
			channelstoskipn2.push_back(i+1);
		}
	}
	channelstoskipn2.push_back(-1);
	node1channel = n1.helpCreateRoute(channelstoskipn2);

	channelstoskipn2.push_back(node1channel+1);
	channelstoskipn2.push_back(node1channel-1);
	node2channel = destnode.getBestAvailableChannel(channelstoskipn2);

	//cout << "best channel for node: " << n1.getName() << " is " << node1channel << " | using the same channel for " << n2.getName() << " which is " << node2channel << '\n';
	// cout << n1.checkChannelStatus(node1channel) << " | " << n2.checkChannelStatus(node2channel);

	int count = 0;
	while (checkChannelStatus(node1channel) == 1 || destnode.checkChannelStatus(node2channel) == 1)
	{
		cout << " The requested channel is not available for both nodes trying again " << endl;
		node1channel = wn1[count].second;
		channelstoskipn2.clear();
		channelstoskipn2.push_back(node1channel+1);
		channelstoskipn2.push_back(node1channel+2);
		node2channel = getBestAvailableChannel(channelstoskipn2);

		//	cout << "New channel names " << node1channel << " | " << node2channel << endl;
		//	cout << " New channels " << n1.checkChannelStatus(node1channel) << " | " << n2.checkChannelStatus(node2channel) << endl;

		count ++;
	}
	// The channel selections are available
	if(!n1.reserveChannel(node1channel)){
		cout << "Couldn't reserve channel on " << getName() << endl;
		return false;
	}
	if(!destnode.reserveChannel(node1channel)){
		cout << "Couldn't reserve channel on " << getName() << endl;
		return false;
	}
	else {
		cout << "Both Channels are now reserved " << endl;

		n1.setSendingChannel(node1channel);
		destnode.setListeningChannel(node1channel);

		n1.setDestNode(destnode.getName(),node1channel);
		destnode.setDestNode(n1.getName(),node2channel);

		Hop hop1;

		hop1 = make_tuple(n1.getName(),node1channel,n1.getDestNode(node1channel));
		cout << "Checking Hop 1 only 1 hop made" << endl;

		cout << get<0>(hop1) << endl;
		cout << get<1>(hop1) << endl;
		cout << get<2>(hop1) << endl;

		std::vector<Hop> path = {hop1};
		// Update the nodes along the route
		n1.addToResults(path);
		cout << "total number of current hop = " << path.size() << endl; 		
		routes.at(startnodeindex) = returnNode();
		routes.at(startnodeindex+1) = destnode;			
		return true;
	}
}

bool Node::twoHopHelper(int start,vector<Node> &routes)
{	
	vector<int> allchannels = getAllChannels();
	auto test = Channels;
	vector<Hop> n1ton2hops;
	vector<Hop> n2ton3hops;
	vector<vector<Hop>> hopsresult;

	bool channelsreserved = false;
	Node n1,n2, n3;
	Hop hop1, hop2 ;	
	int i = start;
	cout << "3 + total nodes in path detected " << routes.size() << endl;
		cout << "Trying to reserve a channel starting at node " << i << endl;
		if(!channelsreserved){
			int node1channel = -1;
			int node2channel = -1;
			int node3channel = -1;
			cerr <<"in " << i << endl;
			//Get the first three nodes 
			cerr << routes.size() << " all routes size 3+" << endl;
			n1 = routes.at(i);
			cerr << "assigned 1 " << endl;
			n2 = routes.at(i+1);
			cerr << "assigned 2 " << i+2 << endl;
			n3 = routes.at(i+2);
			cout << "assigned all three nodes starting with node " << n1.getName() << endl;
			auto wn1 = n1.SortedWeightsByBest(); // Node 1
			auto wn2 = n2.SortedWeightsByBest(); // Node 2
			auto wn3 = n3.SortedWeightsByBest(); // Node 2
			vector<int> channelstoskipn2;

			channelstoskipn2.push_back(-1);

			node1channel = n1.helpCreateRoute(channelstoskipn2);

			auto allchannelsn2 = n2.getAllChannelsStatus();
			for (size_t i = 0; i < allchannelsn2.size(); i++)
			{
				if(allchannelsn2[i]==1 && i > 0){
					cout << "Avoiding adj interference avoiding ( ) for first hop/2  " << i+1 << endl;
					cout << "Avoiding adj interference avoiding ( ) for first hop/2  " << i-1 << endl;	
					channelstoskipn2.push_back(i-1);
					channelstoskipn2.push_back(i+1);
				}
				else if(i == 0 && allchannelsn2[i]==1){
					cout << "Avoiding adj interference avoiding ( ) for first hop/2 i = 0  " << i+1 << endl;
					channelstoskipn2.push_back(i+1);		
				}
			}

			node2channel = n1.helpCreateRoute(channelstoskipn2);

			vector<int> channelstoskipn3;
			channelstoskipn3.push_back(node2channel); // Avoid co channel interference
			channelstoskipn3.push_back(node1channel); // Avoid exposed problem with node
			auto allchannelsn3 = n3.getAllChannelsStatus();
			for (size_t i = 0; i < allchannelsn3.size(); i++)
			{
				if(allchannelsn3[i]==1 && i > 0){
					cout << "Avoiding adj interference avoiding ( ) for second hop  " << i+1 << endl;
					cout << "Avoiding adj interference avoiding ( ) for second hop  " << i-1 << endl;
					channelstoskipn3.push_back(i-1);
					channelstoskipn3.push_back(i+1);
				}
				else if(i == 0 && allchannelsn3[i]==1){
					cout << "Avoiding adj interference avoiding ( ) for first hop  " << i+1 << endl;
					channelstoskipn2.push_back(i+1);
				}
			}
			channelstoskipn3.push_back(node1channel); // Avoid exposed terminal
			node3channel = n3.getBestAvailableChannel(channelstoskipn3); // find a channel thats not used on node 1 and 2

			if(node3channel == -1){ // No point in trying if node 3 has no channels available
				return false;
			}
			cout << "Checking that status of all four chosen channels "  << checkChannelStatus(node1channel) << " | " << n2.checkChannelStatus(node2channel) << " | " << n2.checkChannelStatus(node3channel) << " | " << n3.checkChannelStatus(node3channel) << " " << endl;

			int count = 0;
			while (checkChannelStatus(node1channel) == 1 || n2.checkChannelStatus(node2channel) == 1 && count < wn1.size()) // Channel is not avail for n1 or n2
			{
				channelstoskipn2.clear();
				cout << "Finding " << endl;
				node1channel = wn1[count].second;
				channelstoskipn2.push_back(count+1);
				cout << "Avoiding adj interference avoiding ( ) for first hop out of two hops  " << count+1 << endl;				
				channelstoskipn2.push_back(count-1);
				cout << "Avoiding adj interference avoiding ( ) for first hop out of two hops  " << count-1 << endl;
				node2channel = n2.getBestAvailableChannel(channelstoskipn2);
				//	cout << "New channel names " << node1channel << " | " << node2channel << endl;
				//	cout << "New channels" << checkChannelStatus(node1channel) << " | " << n2.checkChannelStatus(node2channel) << endl;
				count ++;
			}
			if(count >= wn1.size()){
				cout << "Couldn't find a channel cout > wn1 " << endl;
				return false;
			}
			//	cout << "Found channels for first two nodes/3" << endl;
			//	cout << "current channels stat " << n2.checkChannelStatus(node2channel) << " | " << n2.checkChannelStatus(node3channel) << " | " << n3.checkChannelStatus(node3channel) << endl;
			count = 0;
			while (n2.checkChannelStatus(node2channel) == 1 || n2.checkChannelStatus(node3channel) == 1 || n3.checkChannelStatus(node3channel) == 1 && count < wn2.size()-1)
			{
				channelstoskipn3.clear();
				if(count > wn2.size()-1){
					cout << "Couldn't find a channel > wn2 " << endl;
					return false;
				}
				else{
					node2channel = wn2[count].second;
					channelstoskipn3.push_back(node1channel);
					channelstoskipn3.push_back(node2channel+1);
					channelstoskipn3.push_back(node2channel-1);
					node3channel = n3.getBestAvailableChannel(channelstoskipn3);
					//cout << "New channel names " << node2channel << " | " << node3channel << endl;
					//cout << "New channels" << n2.checkChannelStatus(node2channel) << " | " << n3.checkChannelStatus(node3channel) << endl;
					count ++; // avoid loop
				}
			}

			cout << "Found channels for last two nodes/3 " << endl;
			// The channel selections are available
			if(!n1.reserveChannel(node1channel)){
				cout << "Couldn't reserve channel on " << getName() << endl;
				return false;
			}
			else if(!n2.reserveChannel(node2channel)){
				return false;
			}
			else if(!n2.reserveChannel(node3channel)){
				return false;
			}
			else if(!n3.reserveChannel(node3channel)){
				return false;
			}
			else {
				cout << "All 4 Channels are now reserved " << endl;
				// Set the destnode for nodes involved
				n1.setDestNode(n2.getName(),node1channel);
				n2.setDestNode(n1.getName(),node2channel);
				n2.setDestNode(n3.getName(),node3channel);
				n3.setDestNode(n2.getName(),node3channel);

				
				n1.setSendingChannel(node1channel);
				n2.setListeningChannel(node1channel);
				n2.setSendingChannel(node2channel);
				n3.setListeningChannel(node3channel);


				// Check that destination 	set correctly
				n1.getDestNode(node1channel);
				n2.getDestNode(node2channel);
				n2.getDestNode(node3channel);
				cout << "wait " << endl;
				n3.getDestNode(node3channel);

				hop1 = make_tuple(n1.getName(),node1channel,n1.getDestNode(node1channel));
				hop2 = make_tuple(n2.getName(),node3channel,n2.getDestNode(node3channel));

				cerr << "Hello" << endl;

				cout << "Checking Hop 1" << endl;

				cout << get<0>(hop1) << endl;
				cout << get<1>(hop1) << endl;
				cout << get<2>(hop1) << endl;

				cout << "Checking Hop 2" << endl;

				cout << get<0>(hop2) << endl;
				cout << get<1>(hop2) << endl;
				cout << get<2>(hop2) << endl;

				std::vector<Hop> path = {hop1,hop2};
				// Update the nodes along the route
				n1.addToResults(path);
				routes.at(i) = n1;
				routes.at(i+1) = n2;
				routes.at(i+2) = n3;

				if(i <= fullroutes.at(0).size()-3){
					channelsreserved = true;
					cout << "Channel is now reserved " << channelsreserved <<endl;
					cerr << "Channel is reserved" << endl;
				}
			}
		}
	if(channelsreserved){
		cout << " after total number of hops = " << n1.results.size() <<endl; 
		return channelsreserved;
	}
	if(!channelsreserved)
		return false;
}	
bool Node::createRoute(Node &destnode){ // Create a new route between three nodes
	for (size_t i = 0; i < fullroutes.size(); i++)
	{
		for (size_t j = i; j < fullroutes.at(i).size(); j++)
		{
			if(fullroutes.at(i).at(0).getName() == getName() && fullroutes.at(i).at(fullroutes.at(i).size()-1).getName() == destnode.getName() ){
				cout << "Found a matching path " << endl;
			}
		}
		
	}	
	int routesize = fullroutes.at(0).size();
	if(routesize <= 1){
		cout << "No route passed" << endl;
		return false;
	}
	if(routesize == 2){
		return twoHopHelper(1,fullroutes.at(0));
	}
	else{
		bool resultone = false;
		bool resulttwo = false;
		bool routeoneneeded = false;
		bool routetwoneeded = false;
		//Check if 
		for (size_t i = 0; i <= routesize-2; i+=2)
		{
			cout << "at hop " << i << endl;
			if(routesize%2 == 0 && i== routesize-2){ 
				cout << "1current i value " << i << endl ;
				resultone = oneHopHelper(i,fullroutes.at(0));
				routetwoneeded = true;
				routeoneneeded = true;
			}
			else if(routesize%2 == 1 && i ==routesize-3){ // group of three and at end of list of routes
				cout << "2current i value " << i << endl ;
				resulttwo = twoHopHelper(i,fullroutes.at(0));
				routetwoneeded = true;
			}
			else if(i == 0){ // group of three and at end of list of routes
				cout << "3current i value " << i << endl ;
				resulttwo = twoHopHelper(i,fullroutes.at(0));
				routetwoneeded = true;
			}
		}
		if(routetwoneeded && routeoneneeded){
			return true;
		}
		if(routetwoneeded && !routeoneneeded){
			return routetwoneeded;
		}
		if(!routetwoneeded && routeoneneeded){
			return routetwoneeded;
		}
	}


}

vector<vector<Node>> Node::getRoutes(){ // get the routes taken by the node
	return fullroutes;
}

vector<vector<Hop>> Node::getResults(){
	return results;
}
void Node::addToResults(vector<Hop> &hopstoadd){
	cout << "adding to results " << endl;
	results.push_back(hopstoadd);
	cout << "size of results" << results.size() << endl;
} 

void Node::testRouteGen(Node &n2, Node &n3,Node &destNode){ // Test Function
    vector<Node> path_track;
    path_track.push_back(returnNode());
	path_track.push_back(n2);
	path_track.push_back(n3);
	path_track.push_back(destNode);

	cout << "Current path length is " << path_track.size() << endl;
    fullroutes.push_back(path_track);
}


void Node::graphGenerationAlgo(Node & startNode, Node & endNode, vector<Node> noderef){//graph algo, the result of which will be stored within the starting node
    string PathFragment;
    vector<string> PathFragmentList;
    string nameRef(startNode.name);
        for (auto & node: noderef){

        for (auto & subNodes : node.adjlist){
            cout<<subNodes.first.name<<'\n';
            cout<<subNodes.second.name<<'\n';
        }
        cout<<'\n';
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
        for(auto nodelist : PathFragmentList){

            for ( auto name : nodelist){
                cout<<name<<'\n';
            }
            cout<<"new connection"<<'\n';
        }
       mergePaths(startNode, endNode, PathFragmentList);
}


void Node::nodesInRange(vector<Node> & allNodes){
    for(auto & initialNode : allNodes){
        for (auto & theNode : allNodes){
            if (initialNode.name != theNode.name){
                int distance = distanceFormula(initialNode.position.first, initialNode.position.second, theNode.position.first, theNode.position.second);
                if (distance <= initialNode.radius){
                    pair<Node &,Node &> inrange(initialNode, theNode);
                    initialNode.adjlist.push_back(inrange);
                }
            }
        }
        initialNode.setAllNodeRef(initialNode, allNodes);
    }
}
       /* for (auto & subNodes : initialNode.adjlist){
                cout<<"the intit node "<<initialNode.name<<'\n';
                cout<<"the sub node " <<subNodes.second.name<<'\n';
            if(subNodes.second.adjlist.empty()){
                nodesInRange(subNodes.second, allNodes);
            }
        }*/
}

void Node:: mergePaths(Node & startNode, Node & endNode, vector<string>  currentPaths){//used within the graphAlgo to find and merge subpaths
    string pathUpdate;
    vector<string> allPathUpdate;
    int start(1);
    string firstPush{""};

    for(auto initialcheck : currentPaths){
        if ((initialcheck[0] == startNode.name[0])&& (initialcheck.back() == endNode.name[0])){
            startNode.fullroutes.push_back(initialcheck);
        }
    }

    while ((start == 1) || ((newRoutePossible( startNode, endNode, currentPaths)) == true)){
            start = 0;

            for (auto route : currentPaths){

                if ((route[0] == (startNode.name[0])) && (route.back() != endNode.name[0])){

                    for(auto routeCheck : currentPaths){
                        if ((routeCheck[0] == route.back())&&(routeCheck[0] != endNode.name[0])){
                            for(auto node : routeCheck){
                               if ((node != route.back())&&(route[0] != routeCheck.back())){
                                    if (loopCheck(route, routeCheck)){
                                        pathUpdate += route;
                                        pathUpdate.push_back(node);
                                    }
                               }
                               if ((pathUpdate.back() == endNode.name[0]) && (pathUpdate != firstPush)){
                                    startNode.fullroutes.push_back(pathUpdate);
                                    firstPush = pathUpdate;
                               }
                            }
                        }

                        else if((route[0] != routeCheck.back()) && (routeCheck[0] != endNode.name[0])){
                                if(routeCheck[0] != startNode.name[0]){
                                        pathUpdate += routeCheck;

                                        allPathUpdate.push_back(pathUpdate);
                                        pathUpdate.clear();
                                }
                        }


                            allPathUpdate.push_back(pathUpdate);
                            pathUpdate.clear();

                    }
                }
            }

            currentPaths = allPathUpdate;
            allPathUpdate.clear();


        }

   }



bool Node:: newRoutePossible(Node & startNode , Node & endNode, vector<string>  currentPath){//used with graph algo to check  whether further routes are possible

    for (auto & route : currentPath){
            if (((route[0] == (startNode.name[0])) && (route.back() != endNode.name[0]))){
                    return true;
        }
    }
    return false;

}

bool Node:: loopCheck(const string path, const string refString){//prevents looping paths in the merge algo

    for (auto name : path){
            if (name == refString.back()){
                return false;
        }
    }
    return true;
}

void Node:: setAllNodeRef(Node & initialNode, vector<Node>  & receiverList){
        for (auto  setNode : receiverList){
            initialNode.allNodeRef.push_back(setNode);
            //cout<<setNode.name;
        }
}

float Node::distanceFormula(int x1, int y1, int x2, int y2){
    float distance = pow((x2 - x1), 2) + pow((y2 - y1), 2);
    distance = sqrt(distance);
    return distance;
}
