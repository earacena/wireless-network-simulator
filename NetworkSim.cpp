#include <iostream>
#include <utility>
#include <string>
#include <vector>

#include "Node.h"
#include "BaseStation.h"
#include "Receiver.h"

using namespace std;

typedef pair<int,int> Pair;

vector<int> poisson(int numofchannels){
  // construct a trivial random generator engine from a time-based seed:
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);

  std::poisson_distribution<int> distribution (numofchannels);

 // std::cout << "some Poisson-distributed results (mean=numofchannels: ";
  vector<int> values;
  for (int i=0; i<numofchannels; ++i){
	  values.push_back(distribution(generator));
  }
  return values;
}
void assignChannels(Node &node,BaseStation &bs,vector<int> &values){

	int total_channels = 10; 
	//cout << "assigning " << total_channels <<" channels for " << node.getName() << endl;
	node.setChannels(total_channels,values);
	node.setBasestation(bs.getName());
}

void displayAllChannels(Node node){
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
				cout << "Adding a new node " << nodes[n].getName() << " to " << current.getName() << endl;
				nodes[n].setRadius(noderadius);
				current.addNode(nodes[n]);	
				basestations[i] = current;		
				displayAllChannels(nodes[n]);
			}
		}	
	}
}
bool generateRoute(Node &n1,BaseStation &bs){
//	cout << "Route for " << bs.getName() << " with nodes " << n1.getName() << endl;
	bool valid = bs.createRoute(n1);
	if(!valid){
		cout << "No route possible, implement logic later -_-" << endl;
		return false;
	}
	else
	{
		return true;
	}
	
}

bool generateRoute(Node &n1, Node &n2,BaseStation &bs){
//	cout << "Route for " << bs.getName() << " with nodes " << n1.getName() << " & " << n2.getName() << endl;
	bool valid = bs.createRoute(n1,n2);
	if(!valid){
		cout << "No route possible, implement logic later -_-" << endl;
		return false;
	}
	else
	{
		return true;
	}
	
}

void export_data();

int main(){

	
	//Parse the initial gui text file
	Receiver receiver;
  
  	receiver.read_data_from_GUI("test-file-receiver.txt");
  	receiver.parse_data();
	
	cout << "Finished Parsing Data" << endl;

	vector<BaseStation> basestations = receiver.basestations;
	int basestation_radius = receiver.base_station_radius;
	int total_basestations = receiver.num_of_base_stations; // Parse number of basestations from file

	int number_of_nodes = receiver.num_of_nodes;
	int node_radius = receiver.node_radius;
	int number_of_channels = 10;

	vector<Node> allnodes = receiver.nodes;
	populateBaseStations(basestations,allnodes,node_radius,number_of_channels); // populate the base stations
	cout << "Finished Populating all basestations" <<endl;

	//go through all requests
	// then go through each basestation
	// then go through each node to find match
 	vector<Request> requests = receiver.requests;
	 cout << "Total number of requests are" << requests.size() << endl;
	for (size_t r = 0; r < requests.size(); r++){

		string curReqSrcId = requests.at(r).first;
		string curReqDestId = requests.at(r).second;
	//	cout << "Current requested is " << curReqSrcId << " | " << curReqDestId << endl;

		vector<Node> nodes;	 
		Node srcnode;
		Node destnode;

		for (size_t i = 0; i < basestations.size(); i++){
			BaseStation current = basestations[i]; 
			allnodes = current.get_Nodes();
			int max = allnodes.size();
		//	cout << "currently at " << current.getName() << endl;
			for (size_t n = 0; n < allnodes.size(); n++)
			{
				if(	allnodes[n].getBasestation() == current.getName()){ // Found only nodes belonging to bs needed
					if(allnodes[n].getName() == curReqSrcId || allnodes[n].getName() == curReqDestId){ //Found src and dest nodes in bs
					//	cout << "Found a node " << endl;
						nodes.push_back(allnodes[n]);	
					}
				}
			}
		}
		// At this point should have found both nodes needed
		for (size_t m = 0; m < nodes.size(); m++)
		{
			if(nodes.at(m).getName() == curReqSrcId){
				srcnode = nodes.at(m);
			}
			if(nodes.at(m).getName() == curReqDestId){
				destnode = nodes.at(m);
			}			
		}
		
		string srcbs = srcnode.getBasestation();
		string destbs = destnode.getBasestation();

		bool routeGenerated = false;
		bool routeGeneratedOtherBS = false;
		for (size_t i = 0; i < basestations.size(); i++)
		{
			BaseStation current = basestations[i]; 
			// Both nodes in one basestation
			if(!routeGenerated && current.getName() == srcbs && current.getName() == destbs ){
				cout << "Source and Dest Basestation is " << current.getName() <<endl;
				//if(srcnode.inNodeRadius(destnode)){
					routeGenerated = generateRoute(srcnode,destnode,current);

					allnodes = current.get_Nodes();		
					// update nodes and basestations
					for (size_t n = 0; n < allnodes.size(); n++)
					{
						if(allnodes[n].getName() == srcnode.getName()){
							Node srcnodetoupd = srcnode;
							current.updateNode(srcnodetoupd);
						}
						if(allnodes[n].getName() == destnode.getName()){
							Node destnodetoupd = destnode;
							current.updateNode(destnodetoupd);
						}
					}
					basestations[i] = current;
				//}
				// else // might need to be a while loop to keep going till it runs out
				// {
				// 	cout << "The source and destination are currently not in the same radius " << endl;
				// 	//Need a list of all nodes in range of this node to choose from
				// 	vector<Node> nodesinrange;
				// 	vector<Node> nodesused;
				// 	allnodes = current.get_Nodes();
				// 	for (size_t i = 0; i < allnodes.size(); i++)
				// 	{
				// 		if(allnodes[i].getName() != srcnode.getName() && srcnode.inNodeRadius(allnodes[i])){
				// 			cout << "Found another node to hop to " << allnodes[i].getName() << endl;
				// 			nodesinrange.push_back(allnodes[i]);							
				// 		}
				// 	}
				// 	// This is where the graph generation choices come into play
				// 	// Current non smart way below
				// 	for (size_t i = 0; i < nodesinrange.size(); i++)
				// 	{
				// 		Node nextNode = nodesinrange[i];
				// 		if(srcnode.inNodeRadius(nextNode)){
							
				// 		}
				// 		else
				// 		{
				// 			nodesused.push_back(nextNode);
				// 		}
						
				// 	}



				// }
				
			}	
			// If the destination is not in current basestation
			else if(current.getName() == srcbs && current.getName() != destbs){
				cout << "Source Basestation is " << srcbs <<endl;
				cout << "Dest Basestation is " << destbs <<endl;
				for (size_t j = i+1; j < basestations.size(); j++)
				{
					BaseStation second = basestations[j];
					if(basestations[j].getName() == destbs && !routeGeneratedOtherBS && ! routeGenerated){
						cout << "Generating a route between two basestations " << endl;
						routeGenerated = generateRoute(srcnode,current);
						routeGeneratedOtherBS = generateRoute(destnode,second);	

						for (size_t n = 0; n < allnodes.size(); n++)
						{
							if(allnodes[n].getName() == srcnode.getName()){
							Node srcnodetoupd = srcnode;
							current.updateNode(srcnodetoupd);
						}
							if(allnodes[n].getName() == destnode.getName()){
							Node destnodetoupd = destnode;
							second.updateNode(destnodetoupd);
					}
				}					
						basestations[i] = current;
						basestations[j] = second;
					}
				}
				

			}
		}
		if(!routeGenerated){
			cout << "Route generation not possible " << endl;
		}
		displayAllChannels(srcnode);
		displayAllChannels(destnode);
	}
		cout << "Finshed Dealing with all requests" << endl;	

	 for (size_t i = 0; i < basestations.size(); i++)
	 {
		cout << "Displaying all weights for bs " << basestations[i].getName() << endl;
		auto allnodes = basestations[i].get_Nodes();
		int max = allnodes.size();
		if(max == 1){
			cout << allnodes.at(0).getName() << endl;
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