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

void populateBaseStations(vector<BaseStation> &basestations, int number_of_nodes){
	for (size_t i = 0; i < basestations.size(); i++)
	{
		BaseStation current = basestations[i]; // adding nodes the the basestation
		for (size_t n = 0; n < number_of_nodes; n++)
		{
			string name = to_string(n);
			Node newnode;
			newnode.setName(name);
			assignChannels(newnode,current);
			cout << "Adding a new node " << name << " to " << current.getName() << endl;
			current.addNode(newnode);	
			basestations[i] = current;		
		//	displayAllChannels(newnode);
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
	populateBaseStations(basestations,number_of_nodes); // populate the base stations

	vector<Node> allnodes;
		for (size_t i = 0; i < 1; i++)// for testing with just 1 basestation
	{
		BaseStation current = basestations[i]; // adding nodes the the basestation
		allnodes = current.get_Nodes();
		for (size_t n = 0; n < number_of_nodes-1; n++) // This whole section can change once data passed in
		{
			if(n < number_of_nodes-2){ // Can assign 3 nodes

			Node node1 = current.findNode(allnodes[n].getName());
			Node node2 = current.findNode(allnodes[n+1].getName());
			Node node3 = current.findNode(allnodes[n+2].getName());

	//		cout << "NS Establising route between nodes " << node1.getName() << "," << node2.getName() << "," << node3.getName() << " and basestation " << basestations[i].getName() << endl;	
			generateRoute(node1,node2,node3,basestations[i]);
		
			current.updateNode(node1);
			current.updateNode(node2);
			current.updateNode(node3);
			basestations[i] = current;
			}
			else
			{
				Node node1 = current.findNode(allnodes[n].getName());
				Node node2 = current.findNode(allnodes[n+1].getName());
				generateRoute(node1,node2,basestations[i]);

				current.updateNode(node1);
				current.updateNode(node2);

				basestations[i] = current;

			}
			
		}
			Node node1 = basestations[0].findNode("0");
			Node node2 = basestations[0].findNode("1");
			Node node3 = basestations[0].findNode("2");
			Node node4 = basestations[0].findNode("3");
			Node node5 = basestations[0].findNode("4");						
			displayAllChannels(node1);
			displayAllChannels(node2);
			displayAllChannels(node3);
			displayAllChannels(node4);
			displayAllChannels(node5);
			cout << endl;
		
		
	}
	 Node first = basestations[0].findNode("0");
	 Node second = basestations[0].findNode("1");
	 Node third = basestations[0].findNode("2");

	  BaseStation firstbs = basestations[0];
	  cout << "Generating route between" << first.getName() << " | " << second.getName() <<endl; 
	  generateRoute(first,second,basestations[0]);
	  cout << endl;
	  cout << "Generating route between node 2 and 3" <<endl; 
	  cout << endl;
	  generateRoute(second,third,firstbs);
	  cout << endl;
	  generateRoute(first,second,firstbs);
	  cout << endl;
	  generateRoute(first,second,third,firstbs);
	  cout << "Generating route between node 1,2 and 3" <<endl; 
	  displayAllChannels(first);
	  displayAllChannels(second);
	  displayAllChannels(third);
	  cout << endl;


	  auto allweights = firstbs.weightBetweenTwoNodes(first,second);

	  generateRoute(first,second,third,firstbs);
	  generateRoute(first,second,third,firstbs);
	  generateRoute(first,second,third,firstbs);
	  generateRoute(first,second,third,firstbs);
	  generateRoute(first,second,third,firstbs);
	  displayAllChannels(first);
	  displayAllChannels(second);
	  displayAllChannels(third);

}