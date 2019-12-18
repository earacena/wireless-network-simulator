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

 // std::cout << "some Poisson-distributed results (mean=numofchannels: ";
  vector<int> values;
  for (int i=0; i<numofchannels; ++i){
	  values.push_back(distribution(generator));
  }
  return values;
}
Node findNodeInBasestation(Node &nodetofind,vector<BaseStation> &basestations){
		cout << "Looking for a node in the basestation node = " << nodetofind.getName() << endl;
		for (size_t i = 0; i < basestations.size(); i++)
		{
			BaseStation current = basestations[i]; 
			auto allnodes = current.get_Nodes();
			for (size_t i = 0; i < allnodes.size(); i++)
			{
				if(allnodes.at(i).getName() == nodetofind.getName()){
					cout << "Found " << allnodes.at(i).getName();
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
				cout << "Adding a new node " << nodes[n].getName() << " to " << current.getName() << endl;
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
		cout << "Current requested is " << curReqSrcId << " | " << curReqDestId << endl;

		Node srcnode;
		Node destnode;

		cout <<" TEST SRCNODE " << endl;
		srcnode.getChannelWeights();
		
		srcnode.setName(curReqSrcId);
		destnode.setName(curReqDestId);

		Node test1;
		Node test2;
		cout <<" TEST1 values " << endl;
		test1.getChannelWeights();
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
			cout <<" TEST bs srcnodes vals " << endl;
			srcnode.getChannelWeights();
			destnode.getChannelWeights();
			string srcbs = srcnode.getBasestation();
			string destbs = destnode.getBasestation();

			cout << "Going through the Basestations " << " | " << srcbs << " | " << destbs << endl;

			if(!routeGenerated){
				//cout << "Source and Dest Basestation is " << current.getName() <<endl;

				test1 = findNodeInBasestation(test1,basestations);
				test2 = findNodeInBasestation(test2,basestations);
				cerr << "Generating route for " << test1.getName() << " and " << test2.getName() << endl;
				srcnode.testRouteGen(test1,test2);	

				routeGenerated = srcnode.createRoute(destnode);

				cout << "was the route generation done ? " <<  routeGenerated << endl;

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
						current.updateNode(*col);
						cout << col->getName() << " Just updated that node " << endl;
						allresults = col->getResults();
						cout << "all results = " << allresults.size() << endl;
					}	
				basestations[i] = current;	
				}	
			}	
			}				
			//displayAllChannels(srcnode);
		}
		cout << "Finshed Dealing with all requests" << endl;	
		// Display all channels and all weights
		for (size_t i = 0; i < basestations.size(); i++)
		{
			//	cout << "Displaying all weights for bs " << basestations[i].getName() << endl;
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


		//Begin outputting results to Sender
		for (size_t i = 0; i < basestations.size(); i++)
		{
			BaseStation current = basestations[i];	
			auto allnodes = current.get_Nodes();	
			for (size_t j = 0; j < allnodes.size(); j++)
			{
				Node currentNode = findNodeInBasestation(allnodes[j],basestations);
				int resultslength = currentNode.getResults().size();
				if(resultslength != 0){
					Sender sender("routes.txt");
					sender.export_data(currentNode.getResults());	
				}
	
			}	
		}			
	}
}
