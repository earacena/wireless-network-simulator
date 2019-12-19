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
	for(int i = 0; i < Channels.size(); i++){
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
				cout << "erasing " << bestChannels.at(j).second << endl;
				bestChannels.erase(bestChannels.begin()+j);
			}
		}
		
	}

	for(int i = 0; i < bestChannels.size(); i++){
		cout << "Valid channel is " << bestChannels.at(i).second << endl;
		validChannels.push_back(bestChannels[i]);
	}
	for (size_t i = 0; i < validChannels.size(); i++)
	{

		bestchannel = validChannels[i].second;
		cout << " this is the first best channel " << bestchannel << endl;
		return bestchannel;
	}

	// At the first channel
	if(!channelfound){
		return -1;
	}
	else
		return bestchannel;
}
bool Node::reserveChannel(int num){
	if(num > Channels.size()){
		return false;
	}
	else
	{
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
	cout << listeningchannel << " is the listning channel for node " << getName() << endl;
	return listeningchannel;
}
void Node::setListeningChannel(int channel){ // set the channel the node is currently receieving on
	cout << channel << " is the new listening channel for node " << getName() << endl;

	listeningchannel = channel;
}
int Node::getPrevListeningChannel(){ // get the listening channel used by the node
	cout << prevlistchannel << " is the prev listning channel for node " << getName() << endl;
	return prevlistchannel;
}
void Node::setPrevListeningChannel(int channel){ // set the channel the node is currently receieving on
	cout << channel << " is the new prev listening channel for node " << getName() << endl;

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
		cout << "Error that channel doesnt exist " << num << endl;
		return -1;
	}
	else if (Channels.size() > 11){
		cout << "problem" << 1 << endl;
		return -1;
	}
	else
	{
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
		if(!used){
				used = checkChannelStatus(sortedchannels[i].second);
				channel = getBestAvailableChannel(channelstoskip);
				used = true;
				break;
		}
	}
	return channel;
}

bool Node::oneHopHelper(int startnodeindex,vector<Node> &routes){
	auto bestChannels = SortedWeightsByBest();

	vector<vector<Hop>> hopsresult;

	vector<Hop> currenthop;
	int node1channel = -1;
	int node2channel = -1;

	//Get the first and only two nodes 

	Node n1 = routes.at(startnodeindex);

	Node destnode = routes.at(startnodeindex+1);

	auto wn1 = n1.SortedWeightsByBest(); // Node 1
	auto wn2 = destnode.SortedWeightsByBest(); // Node 2

	//Get the best channel 

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
	cout << "avoiding prev list " << n1.getPrevListeningChannel() << endl;
	channelstoskipn2.push_back(n1.getPrevListeningChannel());
	channelstoskipn2.push_back(n1.getSendingChannel());	
	for (size_t i = 0; i < channelstoskipn2.size(); i++)
	{
		cout << "test " <<	 channelstoskipn2.at(i) << endl;
	}
	
	node2channel = destnode.getBestAvailableChannel(channelstoskipn2);

	cout << "this is the 2nd node channel used " << node2channel << endl;

	int count = 0;
	while (checkChannelStatus(node1channel) == 1 || destnode.checkChannelStatus(node2channel) == 1)
	{
		cout << " The requested channel is not available for both nodes trying again " << endl;
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
	if(!n1.reserveChannel(node2channel)){
		cout << "Couldn't reserve channel on " << getName() << endl;
		return false;
	}
	if(!destnode.reserveChannel(node2channel)){
		cout << "Couldn't reserve channel on " << getName() << endl;
		return false;
	}
	else {
		cout << "Both Channels are now reserved " << node1channel << " | " << node2channel<< endl;

		n1.setSendingChannel(node1channel);
		destnode.setListeningChannel(node1channel);

		n1.setDestNode(destnode.getName(),node2channel);
		destnode.setDestNode(n1.getName(),node2channel);

		Hop hop1;

		hop1 = make_tuple(n1.getName(),node2channel,n1.getDestNode(node2channel));

		std::vector<Hop> path = {hop1};
		// Update the nodes along the route
		n1.addToResults(path);
		routes.at(startnodeindex) = n1;
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
		if(!channelsreserved){
			int node1channel = -1;
			int node2channel = -1;
			int node3channel = -1;
			//Get the first three nodes 
			n1 = routes.at(i);
			n2 = routes.at(i+1);
			n3 = routes.at(i+2);
			auto wn1 = n1.SortedWeightsByBest(); // Node 1
			auto wn2 = n2.SortedWeightsByBest(); // Node 2
			auto wn3 = n3.SortedWeightsByBest(); // Node 2
			vector<int> channelstoskipn1;

			channelstoskipn1.push_back(-1);

			auto allchannelsn1 = n1.getAllChannels();
			for (size_t i = 0; i < allchannelsn1.size(); i++)
			{
				if(allchannelsn1[i]==1 && i > 0){
					channelstoskipn1.push_back(i-1);
					channelstoskipn1.push_back(i+1);
				}
				else if(i == 0 && allchannelsn1[i]==1){
					channelstoskipn1.push_back(i+1);		
				}				
			}
			
			node1channel = n1.helpCreateRoute(channelstoskipn1); // Assign a channel for node 1

			vector<int> channelstoskipn2;
			channelstoskipn2.push_back(node1channel); // Avoid Co channel interference with node 1 and node 2 

			auto allchannelsn2 = n2.getAllChannelsStatus();
			for (size_t i = 0; i < allchannelsn2.size(); i++) // Check all channels of n2 and see if they are in use atm
			{
				if(allchannelsn2[i]==1 && i > 0){
					cout << "Avoiding adj interference avoiding ( ) for second node in first hop/2  " << i+1 << endl;
					cout << "Avoiding adj interference avoiding ( ) for second node in first hop/2  " << i-1 << endl;	
					channelstoskipn2.push_back(i-1);
					channelstoskipn2.push_back(i+1);
				}
				else if(i == 0 && allchannelsn2[i]==1){
					cout << "Avoiding adj interference avoiding ( ) for second node in first hop/2 i = 0  " << i+1 << endl;
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
				//cout << "Found a matching path " << endl;
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
	results.push_back(hopstoadd);
} 

void Node::testRouteGen(Node &n2, Node &n3,Node &destNode){ // Test Function
    vector<Node> path_track;
    path_track.push_back(returnNode());
	path_track.push_back(n2);
	path_track.push_back(n3);
	path_track.push_back(destNode);

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

void Node:: mergePaths(Node & startNode, Node & endNode, vector<string>  currentPaths){//used within the graphAlgo to find and merge subpaths
    string pathUpdate;
    vector<string> allPathUpdate;
    int start(1);
    string firstPush{""};

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
                            for(auto node : routeCheck){
                               if ((node != route.back())&&(route[0] != routeCheck.back())){
                                    if (loopCheck(route, routeCheck)){
                                        pathUpdate += route;
                                        pathUpdate.push_back(node);
                                    }
                               }
                               if ((pathUpdate.back() == endNode.name[0]) && (pathUpdate != firstPush)){
                                    startNode.fullroutesstring.push_back(pathUpdate);
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
        }
}

float Node::distanceFormula(int x1, int y1, int x2, int y2){
    float distance = pow((x2 - x1), 2) + pow((y2 - y1), 2);
    distance = sqrt(distance);
    return distance;
}
