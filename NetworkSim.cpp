#include <iostream>
#include <utility>
#include <string>
#include <vector>

#include "Node.h"
#include "BaseStation.h"

using namespace std;

typedef pair<int,int> Pair;

int main(){

	// sample basestations
	BaseStation bs1;
	Pair bs1loc(5,8);
	bs1.setPosition(bs1loc);

	BaseStation bs2;
	Pair bs2loc(1,5);
	bs2.setPosition(bs2loc);

	BaseStation bs3;
	Pair bs3loc(3,9);
	bs3.setPosition(bs3loc);

	// sample for setting node position using pair
	Node node1;

	Pair sample1(8,9);
	node1.setPosition(sample1);

	// temporary channel amount
	int total_channels = 8; 
	auto values = bs1.poisson(total_channels);
	node1.setChannels(total_channels,values);
	vector<int> n1channelweights = node1.getChannelWeights();


	auto n1availchann = node1.getAllChannels();
	auto bestchann = node1.getBestAvailableChannel(); // Use the best channel with highest weight
	cout << "the best channel is " << bestchann << endl;
		//reserve a channel
	cout << "Reserving the best channel" << endl;
	node1.reserveChannel(bestchann);
	n1availchann = node1.getAllChannels();

	Pair test1 = node1.getPosition();

	cout << test1.first << "," << test1.second << endl;


	// sample for setting node position using 2 int args
	Node node2;
	node2.setPosition(2,3);

	Pair test2 = node2.getPosition();

	cout << test2.first << "," << test2.second << endl;


	// sample for setting node(pair, int radius)
	Pair sample3(4,5);
	Node node3(sample3, 5);

	Pair test3 = node3.getPosition();
	cout << test3.first << "," << test3.second << "," << node3.getRadius() << endl;

	// sample for setting node(x, y, radius)
	Node node4(1,2,3);
	Pair test4 = node4.getPosition();
	cout << test4.first << "," << test4.second << "," << node3.getRadius() << endl;

}