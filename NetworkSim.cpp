#include <iostream>
#include <utility>
#include <string>
#include <vector>

#include "Node.h"
#include "BaseStation.h"

using namespace std;

typedef pair<int,int> Pair;

void getChannel(Node &node,BaseStation &bs){

	int total_channels = 8; 
	auto values = bs.poisson(total_channels);
	node.setChannels(total_channels,values);
	vector<int> n1channelweights = node.getChannelWeights();
	auto n1availchann = node.getAllChannels();
	auto bestchann = node.getBestAvailableChannel(); // Use the best channel with highest weight
	cout << "the best channel is " << bestchann << endl;
}

void displayAllChannels(Node node){
	auto allchan = node.getAllChannels();
	cout << "All channels for " << node.getName() << " ";
	for (size_t i = 0; i < allchan.size(); i++)
	{
		cout << allchan[i];
	}
	cout << endl;
}

void generateRoute(Node &n1, Node &n2,BaseStation &bs){
	cout << "generating route" << endl << endl;
	bool valid = bs.createRoute(n1,n2);
	cout << "valid route? " << valid << endl;
	int count = 0;
	int max_tries = n1.getAllChannels().size();
	while(!valid && count <= max_tries){ // No point trying more than the number of channels avail on one node
		cout << "Current route invalid trying again" << endl;
		valid = bs.createRoute(n1,n2);
		count += 1;	}
	if(!valid && count > max_tries){
		cout << "No route possible, implement logic later -_-" << endl;
		// need to 
	}
}
void generateRoute(Node &n1, Node &n2,Node &n3,BaseStation &bs){
	cout << "generating route for 3 nodes" << endl << endl;
	bool valid = bs.createRoute(n1,n2,n3);
	cout << "valid route? " << valid << endl;
	int count = 0;
	int max_tries = n2.getAllChannels().size();
	while(!valid && count <= max_tries){ // No point trying more than the number of channels avail on one node
		cout << "Current route invalid trying again" << endl;
		valid = bs.createRoute(n1,n2,n3);
		count += 1;	}
	if(!valid && count > max_tries){
		cout << "No route possible, implement logic later -_-" << endl;
		// need to 
	}
}

int main(){

	// sample basestations
	BaseStation bs1("BS1");
	Pair bs1loc(5,8);
	bs1.setPosition(bs1loc);

	BaseStation bs2;
	Pair bs2loc(1,5);
	bs2.setPosition(bs2loc);

	BaseStation bs3;
	Pair bs3loc(3,9);
	bs3.setPosition(bs3loc);

	// sample for setting node position using pair
	Node node1("node1");

	Pair sample1(8,9);
	node1.setPosition(sample1);

	// temporary channel amount

	Pair test1 = node1.getPosition();

	cout << test1.first << "," << test1.second << endl;


	// sample for setting node position using 2 int args
	Node node2("node2");
	node2.setPosition(2,3);

	Pair test2 = node2.getPosition();

	cout << test2.first << "," << test2.second << endl;


	// sample for setting node(pair, int radius)
	Pair sample3(4,5);
	Node node3(sample3, 5);
	node3.setName("node3");

	Pair test3 = node3.getPosition();
	cout << test3.first << "," << test3.second << "," << node3.getRadius() << endl;

	// sample for setting node(x, y, radius)
	Node node4(1,2,3);
	Pair test4 = node4.getPosition();
	cout << test4.first << "," << test4.second << "," << node3.getRadius() << endl;

	getChannel(node1,bs1);
	getChannel(node2,bs1);
	getChannel(node3,bs1);
	getChannel(node1,bs1);

	node1.setBasestation(bs1.getName());
	node2.setBasestation(bs1.getName());
	node3.setBasestation(bs1.getName());

	displayAllChannels(node1);
	displayAllChannels(node2);
	generateRoute(node1,node2,bs1);
	displayAllChannels(node1);
	displayAllChannels(node2);
	generateRoute(node2,node3,bs1);
	generateRoute(node1,node2,bs1);
	generateRoute(node1,node2,node3,bs1);
	displayAllChannels(node1);
	displayAllChannels(node2);
	displayAllChannels(node3);

}