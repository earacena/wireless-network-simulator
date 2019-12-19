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
Node findNodeInBasestation(Node &nodetofind,vector<BaseStation> &basestations){
		for (size_t i = 0; i < basestations.size(); i++)
		{
			BaseStation current = basestations[i]; 
			auto allnodes = current.get_Nodes();
			for (size_t i = 0; i < allnodes.size(); i++)
			{
				if(allnodes.at(i).getName() == nodetofind.getName()){
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
 	vector<Request> requests = receiver.requests;
	cout << "Total number of requests are" << requests.size() << endl;
	for (size_t r = 0; r < requests.size(); r++){

		string curReqSrcId = requests.at(r).first;
		string curReqDestId = requests.at(r).second;

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
		
		for (size_t i = 0; i < basestations.size(); i++)
		{
			BaseStation current = basestations[i]; 
			
			// Both nodes in one basestation
			srcnode = findNodeInBasestation(srcnode,basestations);
			destnode = findNodeInBasestation(destnode,basestations);
			srcnode.getChannelWeights();
			destnode.getChannelWeights();
			string srcbs = srcnode.getBasestation();
			string destbs = destnode.getBasestation();


			if(!routeGenerated){

				test1 = findNodeInBasestation(test1,basestations);
				test2 = findNodeInBasestation(test2,basestations);
				srcnode.testRouteGen(test1,test2,destnode);	

				routeGenerated = srcnode.createRoute(destnode);

				allnodes = current.get_Nodes();
				vector<vector<Node>>  NodesinPath = srcnode.getRoutes();
				vector<vector<Node>>::iterator row;
				vector<Node>::iterator col;
	
			if(routeGenerated){
				vector<vector<Hop>> allresults;
				vector<Hop> allHops;
				// update nodes and basestations
				for(row = NodesinPath.begin(); row !=NodesinPath.end(); row++){
					for (col =row->begin(); col != row->end(); col++)
					{	
						allresults = col->getResults();		
							current.updateNode(*col);

					}	
				basestations[i] = current;	
				}	
			}	
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


		vector<vector<Hop>> everyhop;
		vector<Hop> allhops;
		cout << "Begin outputting results to Sender" << endl;
		for (size_t i = 0; i < basestations.size(); i++)
		{
			BaseStation current = basestations[i];	
			auto allnodes = current.get_Nodes();	
			for (size_t j = 0; j < allnodes.size(); j++)
			{
				Node currentNode = findNodeInBasestation(allnodes[j],basestations);
				int resultslength = currentNode.getResults().size();
				if(resultslength != 0){
					auto allresults = currentNode.getResults();
					for (size_t k = 0; k < allresults.size(); k++)
					{
						for (size_t l = 0; l <allresults.at(k).size(); l++)
						{
							allhops.push_back(allresults.at(k).at(l));
						}						
					}					
				}	
			}
		}
		everyhop.push_back(allhops);		
		Sender sender("routes.txt");
		sender.export_data(everyhop);			
	}
}
