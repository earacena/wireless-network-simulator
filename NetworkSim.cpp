#include <iostream>
#include <utility>
#include <string>
#include <vector>

#include "Node.h"
#include "BaseStation.h"
#include "Receiver.h"

using namespace std;

typedef pair<int,int> Pair;
void assignChannels(Node &node,BaseStation &bs){

	int total_channels = 10; 
	auto values = bs.poisson(total_channels);
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

void populateBaseStations(vector<BaseStation> &basestations,vector<Node> &nodes){
	for (size_t i = 0; i < basestations.size(); i++)
	{
		BaseStation current = basestations[i]; // adding nodes the the basestation
		int number_of_nodes = nodes.size();
		for (size_t n = 0; n < number_of_nodes; n++)
		{
			if(current.inBaseStationRadius(nodes[n])){ // current node is in the current basestation radius
				assignChannels(nodes[n],current);
				cout << "Adding a new node " << nodes[n].getName() << " to " << current.getName() << endl;
				current.addNode(nodes[n]);	
				basestations[i] = current;		
				displayAllChannels(nodes[n]);
			}
		}	
	}
}

bool generateRoute(Node &n1, Node &n2,BaseStation &bs){
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
bool generateRoute(Node &n1, Node &n2,Node &n3,BaseStation &bs){
	cout << "gnerating route between nodes " << n1.getName() << "," << n2.getName() << "," << n3.getName() << " and basestation " << bs.getName() << endl;		
	bool valid = bs.createRoute(n1,n2,n3);
	if(!valid){
		cout << "No route possible, implement logic later -_-" << endl;
		return false;
	}
	else
	{
		return true;
	}
	
}

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
	vector<Node> allnodes = receiver.nodes;
	populateBaseStations(basestations,allnodes); // populate the base stations
	cout << "Finished Populating all basestations" <<endl;

	//go through all requests
	// then go through each basestation
	// then go through each node to find match
 	vector<Request> requests = receiver.requests;
	 cout << "Total number of requests are" << requests.size() << endl;
	for (size_t r = 0; r < requests.size(); r++){

		string curReqSrcId = requests.at(r).first;
		string curReqDestId = requests.at(r).second;
		cout << "Current requested is " << curReqSrcId << " | " << curReqDestId << endl;

		vector<Node> nodes;	 
		Node srcnode;
		Node destnode;

		for (size_t i = 0; i < basestations.size(); i++){
			BaseStation current = basestations[i]; 
			allnodes = current.get_Nodes();
			int max = allnodes.size();
			cout << "currently at " << current.getName() << endl;
			for (size_t n = 0; n < allnodes.size(); n++)
			{
				if(	allnodes[n].getBasestation() == current.getName()){ // Found only nodes belonging to bs needed
					if(allnodes[n].getName() == curReqSrcId || allnodes[n].getName() == curReqDestId){ //Found src and dest nodes in bs
						cout << "Found a node " << endl;
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
		for (size_t i = 0; i < basestations.size(); i++)
		{
			BaseStation current = basestations[i]; 
			if(!routeGenerated && current.getName() == srcbs && current.getName() == destbs ){
				cout << "Source and Dest Basestation is " << current.getName() <<endl;
				generateRoute(srcnode,destnode,current);
				routeGenerated = true;
			}	
			if(current.getName() == srcbs){
				cout << "Source Basestation is " << srcbs <<endl;
			}
			if(current.getName() == destbs){
				cout << "Dest Basestation is " << srcbs <<endl;
			}
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