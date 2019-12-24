#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <queue> 

#include "Node.h"
#include "BaseStation.h"
#include "Receiver.h"
#include "Sender.h"

using namespace std;

typedef pair<int,int> Pair;

vector<int> poisson(int numofchannels){
  // construct a trivial random generator engine from a time-based seed:
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);

  std::poisson_distribution<int> distribution (numofchannels);

  vector<int> values;
  for (int i=0; i<numofchannels; ++i){
	  values.push_back(distribution(generator));
  }
  return values;
}
Node& findNodeInBasestation(string nodename,vector<BaseStation> &basestations){
		for (size_t i = 0; i < basestations.size(); i++)
		{
			BaseStation current = basestations[i]; 
			auto allnodes = current.get_Nodes();
			for (size_t i = 0; i < allnodes.size(); i++)
			{
				if(allnodes.at(i).getName() == nodename){
					allnodes.at(i).setBasestation(current.getName());
					return allnodes.at(i);
				}
			}
		}		

}
void assignChannels(Node &node,BaseStation &bs,vector<int> &values){

	int total_channels = 5; 
	//cout << "assigning " << total_channels <<" channels for " << node.getName() << endl;
	node.setChannels(total_channels,values);
	node.setBasestation(bs.getName());
}

void displayAllChannels(Node &node){
	auto allchan = node.getAllChannelsStatus();
	cout << "All channels for " << node.getName() << " " << endl;
	for (size_t i = 0; i < allchan.size(); i++)
	{
		cout << " |Channel: " << i;
		cout << " |Channel Use Status: " << allchan[i];
		cout << " |With weight: " <<node.checkChannelWeight(i);
		cout << endl;
	}
	cout << endl;
}

void populateBaseStations(vector<BaseStation> &basestations,vector<Node> &nodes,int noderadius,int numofchannels){
	auto values = poisson(numofchannels);
	for (size_t i = 0; i < basestations.size(); i++)
	{
		BaseStation current = basestations[i]; // adding nodes the the basestation
		int number_of_nodes = nodes.size();
		for (size_t n = 0; n < number_of_nodes; n++)
		{
			if(current.inBaseStationRadius(nodes[n])){ // current node is in the current basestation radius
				assignChannels(nodes[n],current,values);
				nodes[n].setRadius(noderadius);
				current.addNode(nodes[n]);	
				basestations[i] = current;		
				//	displayAllChannels(nodes[n]);
			}
		}	
	}
}
void export_data();

//passing the src node and the list of all nodes which is our graph
vector<string> BFS( vector<Node>& graph, string src_node_name, string dest_node_name){
	//the vector that holds the route backwards; dest -> src. Basically a stack
	//I swap it at the end
	vector<string> backward_route;
//------------------------------------error handling--------------------------------
	//find index of the source node
	int src_index = -1;
	for(int i = 0; i < graph.size(); i++ ){
		if( graph[i].getName() == src_node_name){
			src_index = i;
		}
	}
	//check if the node is even in the graph
	if (src_index == -1){
		return backward_route; //node is not in the graph; returns an empty vector
	}
	
	//find the index of the destination node
	int dest_index = -1;
	for(int i = 0; i < graph.size(); i++ ){
		if( graph[i].getName() == dest_node_name){
			dest_index = i;
		}
	}
	if (dest_index == -1){
		return backward_route; 
	}
//-------------------------actually starting the algorithm--------------------------
	//for each node that is not the src node, set them to be undiscovered
	for(int i = 0; i < graph.size(); i++){
		if(i != src_index){
			graph[i].discovered = 0; 
			//Reminder: 0=undiscovered(ie first visit), 1=node visited but not adjacent nodes, 2=fully discovered 
			graph[i].hops = 100;
			graph[i].previous_hop = nullptr;
		}
	}
	//using index of src to initialize the src node variables
	graph[src_index].discovered = 1;
	graph[src_index].hops = 0;
	graph[src_index].previous_hop = nullptr;

	//this is a queue to keep track of nodes that have not been fully discovered
	queue<Node*> Q_needs_discovering;
	Node* src_ptr = &graph[src_idex];
	Q_needs_discovering.push(src_ptr);
	//this is just a temporary pointer
	Node* curr_node = nullptr; 
	while(!Q_needs_discovering.empty()){
		//pointer to the top node in the Queue
		curr_node = Q_needs_discovering.front();

		for(int i = 0; i < curr_node->adjlist.size(); i++){ //*** ADJLIST IS IN PRIVATE *****
			//pointer to the current adjacent node
			Node* adj_node = curr_node->adjlist[i];
			if(adj_node->discovered == 0){ //if the adjacent node is undiscovered
				adj_node->discovered = 1;
				adj_node->hops = curr_node->hops + 1;
				adj_node->previous_hop = Q_needs_discovering.front();
				Q_needs_discovering.push(curr_node->adjlist[i]);
				adj_node = nullptr; 
			}
		}
		//we have accessed every adjacent node thus this current node is fully discovered
		curr_node->discovered = 2;
		Q_needs_discovering.pop();
	}
	src_ptr = nullptr;
	curr_node = nullptr;

	//:::::::::::::::: above we find the route, below we prepare the output :::::::::::::::://

	curr_node = &graph[dest_index]; //starting from the destination we're working backwards
	//reminder: { vector<string> shortest_route } the vector that holds the route backwards
	vector<string> forward_route; //the vector that will be returned
	backward.push_back(graph[dest_index].getName()); //push the destination in

	//Im checking if destination is even reachable from the source; 
	//100 is a placeholder for infinity
	if(curr_node->hops < 100){ 
		while(curr_node->previous_hop != nullptr){
			//push in the name of the node preceding this one
    		backward_route.push_back(curr_node->previous_hop->getName());
    		curr_node = curr_node->previous_hop;
		}
		//the vector was populated backwards so I'm just swapping indices
		int length = backward_route.size();
		for(int i = 0; i < length; i++){
			forward_route.push_back(shortest_route.back());
			backward_route.pop_back();
		}
	}

	//output the result being returned
	cout<<"The shortestest route accoding to BFS: \n";
	for(int i = 0; i < forawrd_route.size(); i++){
		cout<<forawrd_route[i]<<"\t";
	}
	curr_node = nullptr;


	return forward_route;
}

int main(){

	
	//Parse the initial gui text file and initialize all basestations and nodes

	Receiver receiver;
  
  	receiver.read_data_from_GUI("test-file-receiver.txt");
  	receiver.parse_data();
	
	cout << "Finished Parsing Data" << endl;

	vector<BaseStation> basestations = receiver.basestations;
	int basestation_radius = receiver.base_station_radius;
	int total_basestations = receiver.num_of_base_stations; // Parse number of basestations from file

	int number_of_nodes = receiver.num_of_nodes;
	int node_radius = receiver.node_radius;
	int number_of_channels = 5;

	vector<Node> allnodes = receiver.nodes;
	populateBaseStations(basestations,allnodes,node_radius,number_of_channels); // populate the base stations
	cout << "Finished Populating all basestations" <<endl;

	//go through all requests
	// then go through each basestation
	// then go through each node to find match

	vector<vector<Hop>> everyhop;
	vector<Hop> allhops;	
 	vector<Request> requests = receiver.requests;
	cout << "	number of requests are" << requests.size() << endl;
	
	bool the_first_route = true; //we are going to service the first request
	for (size_t r = 0; r < requests.size(); r++){

		string curReqSrcId = requests.at(r).first;
		string curReqDestId = requests.at(r).second;

		if(the_first_route){
		//----------------------------------- the BFS -------------------------------------------//
		/* The BFS uses the graph, src node and dest node
			the graph is basically the the vector of all nodes with each node containing a 
			list of adjacent nodes 
			
			I am assuming: 
			Graph: allnodes (list of all nodes, with allocated adjlists)
			source name: curReqSrcId 
			destination name: curReqDestId
		*/

		//records the shortest route
		vector<string> shortest_route_vector = BFS(&allnodes, curReqSrcId, curReqDestId);
		//we have just serviced the first route
		the_first_route = false;
		//push shortest route into the solution vector (?????)
		everyhop.push_back(shortest_route_vector);		
		Sender sender("routes.txt");
		sender.export_data(everyhop);

		//---------------------------------------------------------------------------------------//
		}

		else {/* ... the other stuff underneath for servicing non-first requests, idk how this works*/}
		
		Node srcnode;
		Node destnode;

		srcnode.getChannelWeights();
		
		srcnode.setName(curReqSrcId);
		destnode.setName(curReqDestId);

		Node test1;
		Node test2;
		test1.setName("3");
		test2.setName("4");

		bool routeGenerated = false;
		bool routeGeneratedOtherBS = false;

		// Both nodes in one basestation
		srcnode = findNodeInBasestation(srcnode.getName(),basestations);
		destnode = findNodeInBasestation(destnode.getName(),basestations);
		srcnode.getChannelWeights();
		destnode.getChannelWeights();
		string srcbs = srcnode.getBasestation();
		string destbs = destnode.getBasestation();

		if(!routeGenerated){

			test1 = findNodeInBasestation(test1.getName(),basestations);
			test2 = findNodeInBasestation(test2.getName(),basestations);
			srcnode.testRouteGen(srcnode,test1,test2,destnode);	

			cerr << "Help b4 route gen " << endl;
			routeGenerated = srcnode.createRoute(destnode);
			cout << "after route generation " << endl;
			displayAllChannels(srcnode);
			cerr << "Help 2 " << endl;
			cout << "Route generated " << endl;	
			displayAllChannels(srcnode);

			for (size_t i = 0; i < basestations.size(); i++)
			{
				BaseStation current = basestations[i]; 
				if(srcnode.getBasestation() == current.getName()){
					current.updateNode(srcnode);
					allnodes = current.get_Nodes();
					vector<string> nodesinroute = srcnode.getRoutesString();
					cout << "size of srcnode routes " << nodesinroute.size() << endl;
					for (size_t n = 0; n < nodesinroute.size(); n++)
					{
						cout << n << endl;
						cout << nodesinroute.at(n) << endl;
					}
					auto test = srcnode.getResults();				
					basestations[i] = current;
					for (size_t k = 0; k < test.size(); k++)
					{
						allhops.push_back(test.at(k).at(i));
					}
					
					everyhop = test;
						cout << "Begin outputting results to Sender" << endl;
						Sender sender("routes.txt");
						sender.export_data(everyhop);		
				}
			}
		}
		if(routeGenerated){
	
		}				
			//displayAllChannels(srcnode);
	}
		
		// Display all channels and all weights
		for (size_t i = 0; i < basestations.size(); i++)
		{
			auto allnodes = basestations[i].get_Nodes();
			int max = allnodes.size();
			if(max == 1){
				Node first = basestations[i].findNode(allnodes.at(0).getName());	
				auto allweights = first.getChannelWeights();
			}		
			for (size_t t = 0; t < max-1; t++)
			{
				Node first = basestations[i].findNode(allnodes.at(t).getName());
				Node second = basestations[i].findNode(allnodes.at(t+1).getName());
				auto allweights = basestations[i].weightBetweenTwoNodes(first,second);			

			}
		}



		
}
