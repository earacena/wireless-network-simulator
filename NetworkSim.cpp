#include <iostream>
#include <utility>
#include <string>
#include <vector>

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
Node& findNode(string nodename,vector<Node> &allnodes){
		for (size_t i = 0; i < allnodes.size(); i++)
		{
			if(allnodes.at(i).getName() == nodename){
			//	cout << "Found node " << nodename << endl;
				return allnodes.at(i);
			}
		}		
}
void updateNode(Node &node){

}

void assignChannels(Node &node,BaseStation &bs,vector<int> &values){

	int total_channels = 5; 
	//cout << "assigning " << total_channels <<" channels for " << node.getName() << endl;
	node.setChannels(total_channels,values);
	node.setBasestation(bs.getName());
}

void displayAllChannels(Node &node){
	auto allchan = node.getAllChannelsStatus();
	//cout << "All channels for " << node.getName() << " " << endl;
	for (size_t i = 0; i < allchan.size(); i++)
	{
	//	cout << " |Channel: " << i;
	//	cout << " |Channel Use Status: " << allchan[i];
	//	cout << " |With weight: " <<node.checkChannelWeight(i);
	//	cout << endl;
	}
	//cout << endl;
}

void populateBaseStations(vector<BaseStation> &basestations,vector<Node> &nodes,int noderadius,int numofchannels){
	auto values = poisson(numofchannels);
	string allnodenames;
	for (size_t i = 0; i < nodes.size(); i++)
	{
		allnodenames += nodes.at(i).getName();
	}
	
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

int main(){

	
	//Parse the initial gui text file and initialize all basestations and nodes

	Receiver receiver;
  
  	receiver.read_data_from_GUI("data.txt");
  	receiver.parse_data();
	
	cout << "Finished Parsing Data" << endl;

	vector<BaseStation> basestations = receiver.basestations;
	int basestation_radius = receiver.base_station_radius;
	int total_basestations = receiver.num_of_base_stations; // Parse number of basestations from file

	int number_of_nodes = receiver.num_of_nodes;
	int node_radius = receiver.node_radius;
	int number_of_channels = 5;
	bool foundadjnodes = false;

	vector<Node> allnodes = receiver.nodes;
	populateBaseStations(basestations,allnodes,node_radius,number_of_channels); // populate the base stations

	vector<Node> nodup;

	nodup.push_back(allnodes.at(0));
	for (size_t i = 0; i < allnodes.size(); i++)
	{
		for (size_t j = 0; j < nodup.size(); j++)
		{
			if(nodup.at(j).getName() == allnodes.at(i).getName()){

			}
		}
		
	}
	
	cout << "Finished Populating all basestations" <<endl;

	//go through all requests
	// then go through each basestation
	// then go through each node to find match

	vector<vector<Hop>> everyhop;
	vector<Hop> allhops;	
 	vector<Request> requests = receiver.requests;
	cout << "	number of requests are" << requests.size() << endl;
	for (size_t r = 0; r < requests.size(); r++){

		cout << "Currently on request " << r+1 << endl;
		string curReqSrcId = requests.at(r).first;
		string curReqDestId = requests.at(r).second;

		Node srcnode;
		Node destnode;

		srcnode.getChannelWeights();
		
		srcnode.setName(curReqSrcId);
		destnode.setName(curReqDestId);

		bool routeGenerated = false;
		bool routeGeneratedOtherBS = false;

		// Both nodes in one basestation
		srcnode = findNode(curReqSrcId,allnodes);
		destnode = findNode(curReqDestId,allnodes);
		srcnode.getChannelWeights();
		destnode.getChannelWeights();
		string srcbs = srcnode.getBasestation();
		string destbs = destnode.getBasestation();

		if(!foundadjnodes){
			srcnode.nodesInRange(allnodes);// srcnode isint changed here
			foundadjnodes = true;
		}
		
		srcnode = findNode(curReqSrcId,allnodes);		
		srcnode.graphGenerationAlgo(srcnode,destnode,allnodes);
		destnode.graphGenerationAlgo(destnode,srcnode,allnodes);
		for (size_t i = 0; i < allnodes.size(); i++)
		{
			if(allnodes.at(i).getName() == srcnode.getName())
			allnodes.at(i) = srcnode;
		}			
		srcnode = findNode(curReqSrcId,allnodes);	
		destnode = findNode(curReqDestId,allnodes);


		if(!routeGenerated){
			//cerr << "Help b4 route gen " << endl;
			routeGenerated = srcnode.createRoute(destnode,allnodes);
			//cout << "was the route generated " << routeGenerated << endl;
			if(!routeGenerated){
			//	cout << "No route was possible on this given request" << endl;
				Hop hop1;
				hop1 = make_tuple(srcnode.getName(),-1,destnode.getName());
				std::vector<Hop> path = {hop1};
				for (size_t i = 0; i < allnodes.size(); i++)
				{
					if(allnodes.at(i).getName() == srcnode.getName())
						allnodes.at(i).addToResults(path);
				}	
			}			
		}
	}
	cout << "Begin outputting results to Sender" << endl;
	for (size_t i = 0; i < allnodes.size(); i++)
		{
			auto test = allnodes.at(i).getResults();
			everyhop = test;
			Sender sender("routes.txt");
			sender.export_data(everyhop);	
		}
	
}
