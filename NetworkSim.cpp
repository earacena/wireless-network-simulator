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
		cout << "Looking for a node in the basestation " << endl;
		for (size_t i = 0; i < basestations.size(); i++)
		{
			BaseStation current = basestations[i]; 
			auto allnodes = current.get_Nodes();
			cerr << "test3 " << current.getName() << " || " << nodetofind.getName() << endl;	
			for (size_t i = 0; i < allnodes.size(); i++)
			{
				if(allnodes.at(i).getName() == nodetofind.getName()){
					cerr << "test4" << endl;
					return allnodes.at(i);
				}
			}
		}		

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
	bool valid = n1.createRoute();
	bs.updateNode(n1);
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
			string srcbs = srcnode.getBasestation();
			string destbs = destnode.getBasestation();

			cout << "Going through the Basestations " << " | " << srcbs << " | " << destbs << endl;

			if(!routeGenerated && current.getName() == srcbs && current.getName() == destbs ){
				cout << "Source and Dest Basestation is " << current.getName() <<endl;


				test1 = findNodeInBasestation(test1,basestations);
				cout <<" New test1 values " << endl;
				test2 = findNodeInBasestation(test2,basestations);
				
				srcnode.testRouteGen(srcnode,test1,test2);
		
				routeGenerated = srcnode.createRoute();
				auto test = srcnode.getAllChannelsStatus();
				for (size_t i = 0; i < test.size(); i++)
				{
				//	cout << i << " the status of the src nodes channel " << test[i] << endl;
				}

				cout << "was the route generation done ? " <<  routeGenerated << endl;
				//if(srcnode.inNodeRadius(destnode)){
				//Generate routes for the path chosen

				allnodes = current.get_Nodes();
				vector<vector<Node>>  NodesinPath = srcnode.getRoutes();
				vector<vector<Node>>::iterator row;
				vector<Node>::iterator col;
	
					// update nodes and basestations
					for(row = NodesinPath.begin(); row !=NodesinPath.end(); row++){
						for (col =row->begin(); col != row->end(); col++)
						{
							current.updateNode(*col);
							cout << col->getName() << " Just updated that node " << endl;
							auto test = col->getAllChannelsStatus();
							for (size_t i = 0; i < test.size(); i++)
							{
					//			cout << i << " the status of that channel " << test[i] << endl;
							}							
						}					
					}	
					basestations[i] = current;			
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
						srcnode = findNodeInBasestation(srcnode,basestations);
						test1 = findNodeInBasestation(test1,basestations);
						test2 = findNodeInBasestation(test2,basestations);
						srcnode.testRouteGen(srcnode,test1,test2);
						routeGenerated = srcnode.createRoute();

						cout << "was the route generation done ? " << routeGenerated << endl;
					//	routeGeneratedOtherBS = generateRoute(destnode,second);	

						for (size_t n = 0; n < allnodes.size(); n++)
						{
							cout << "Updating nodes with new values " << endl;
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


	//Being outputting results to Sender
	typedef std::tuple<std::string, int, std::string> Hop;
    std::vector< std::vector<Hop> > Path;

}