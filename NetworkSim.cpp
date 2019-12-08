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
}

void displayAllChannels(Node node){
	auto allchan = node.getAllChannelsStatus();
	cout << "All channels for " << node.getName() << " ";
	for (size_t i = 0; i < allchan.size(); i++)
	{
		cout << allchan[i];
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
	bs.createRoute(n1,n2);
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

 	vector<Request> requests = receiver.requests;
	// GENERATING ROUTE BELOW HERE
	// Based on route req find the correct basestation and choose only those 2 nodes
	for (size_t i = 0; i < basestations.size(); i++)// for testing with just 1 basestation
	{
		BaseStation current = basestations[i]; // adding nodes the the basestation
		allnodes = current.get_Nodes();
		int max = allnodes.size();
		cout << "currently at " << current.getName() << endl;
		for (size_t n = 0; n < max; n++) // This whole section can change once data passed in
		{
			if(n == 0 && max == 1){ // Only 1 node
				Node node1 = current.findNode(allnodes[n].getName());
			}
			if(n == 1 && max == 2){ // Only 2 node
				Node node1 = current.findNode(allnodes[n-1].getName());
				Node node2 = current.findNode(allnodes[n].getName());
				generateRoute(node1,node2,basestations[i]);

				current.updateNode(node1);
				current.updateNode(node2);
				basestations[i] = current;
				displayAllChannels(node1);
				displayAllChannels(node2);
			}
			if(n < max-2 && n >= 2){ // Can assign 3 nodes
				Node node1 = current.findNode(allnodes[n].getName());
				Node node2 = current.findNode(allnodes[n+1].getName());
				Node node3 = current.findNode(allnodes[n+2].getName());

		//		cout << "NS Establising route between nodes " << node1.getName() << "," << node2.getName() << "," << node3.getName() << " and basestation " << basestations[i].getName() << endl;	
				generateRoute(node1,node2,node3,basestations[i]);
		
				current.updateNode(node1);
				current.updateNode(node2);
				current.updateNode(node3);
				basestations[i] = current;
				displayAllChannels(node1);
				displayAllChannels(node2);
				displayAllChannels(node3);
			}
			
		}			
			cout << endl;
		
		
	}
	 Node first = basestations[0].findNode("0");
	 Node second = basestations[0].findNode("1");
	 Node third = basestations[0].findNode("2");

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