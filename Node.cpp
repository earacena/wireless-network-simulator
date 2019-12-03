#include <iostream>
#include <utility>
#include <vector>
#include "Node.h"

using namespace std;

typedef pair<int,int> Pair;


Node::Node(){	// default constructor
	position.first = 0;
	position.second = 0;
	radius = 0;
}

Node::Node(Pair p, int r){	// 2 arg constructor 
	position = p;
	radius = r;
}

Node::Node(int x, int y, int r){ // 3 arg contructor
	position.first = x;
	position.second = y;
	radius = r;
}
Node::Node(string nodename){ 
	position.first = 0;
	position.second = 0;
	radius = 0;
	name = nodename;
}

Pair Node::getPosition(){	//returns a Pair of position
	return position;
}
	
void Node::setPosition(Pair pos){	// sets position of node, pair version
	position = pos;
}

void Node::setPosition(int x, int y){			// sets position of node, separate entry
	position.first = x;
	position.second = y;
}
void Node::setBasestation(string station){ // assigns node to given basestation		
	basestation = station;
}
string Node::getBasestation(){ // gets the basestation of current node
	return basestation;
}
void Node::setName(string nodename){
	name = nodename;}

string Node::getName(){ // gets node name
	return name;
}
int Node::getRadius(){	// return radius of node
	return radius;
}

void Node::setRadius(int r){	// set radius of node
	radius = r; 
}
void Node::setChannels(int n,vector<int> &weight){ // set the number of channels and their weights
	Channels.resize(n);
	for(int i = 0; i < Channels.size(); i++){
		Channels[i].weight = weight[i];
	}
}
vector<int> Node::getChannelWeights(){// get the channel weights for current node
	vector<int> currentChannelsWeights;
	for(int i = 0; i < Channels.size(); i++){
		cout << "Weight for Channel " << i << " is " << Channels[i].weight << endl;
		currentChannelsWeights.push_back(Channels[i].weight);
	}
	return currentChannelsWeights;
}
vector<bool> Node::getAllChannels(){ // get all the channels for current node
	vector<bool> currentChannelUse;
	for(int i = 0; i < Channels.size(); i++){
		currentChannelUse.push_back(checkChannelStatus(i));
	}
	return currentChannelUse;
}
int Node::getBestAvailableChannel(){ // get the best currently available channel for current node
	int bestChannelWeight = 0;
	int bestChannel = 0;
	cout << "Current node " << getName() << endl;
	for(int i = 0; i < Channels.size(); i++){
		if(checkChannelStatus(i) == 0){// Channel available
			if (checkChannelWeight(i) > bestChannelWeight){
				bestChannelWeight = Channels[i].weight;
				bestChannel = i;
			}
		}
	}
	cout << bestChannel<< " is the best available channel" << endl;
	return bestChannel;
}
int Node::getBestAvailableChannel(int channeltoskip){ // get the best currently available channel for current node
	int bestChannelWeight = 0;
	int bestChannel = 0;
	bool channelfound = false;
	cout << "Avoiding the same channel for node:  " << getName() << endl;
	for(int i = 0; i < Channels.size(); i++){
		if(!checkChannelStatus(i)){// Channel available
			if (checkChannelWeight(i) > bestChannelWeight && i != channeltoskip){
				bestChannelWeight = Channels[i].weight;
				bestChannel = i;
				channelfound = true;
				//cout << bestChannel<< " is the best avail channel" << endl;
			}
		}
	}
	if(!channelfound){
	cout << "No Free Channels" << endl;
		return -1;
	}
	else
		return bestChannel;
}
void Node::reserveChannel(int num){
	if(num > Channels.size()){
		cout << "Error that channel doesnt exist";
	}
	else
	{
	//	cout << "Reserving the requested channel " << num << endl;
		Channels[num].used = true;
	}
	

}

void Node::releaseChannel(int num){
	if(num > Channels.size()){
		cout << "Error that channel doesnt exist";
	}
	else
	{
		Channels[num].used = false;
	}

}

bool Node::checkChannelStatus(int num){ // check status of a channel
	if(num > Channels.size()){
		cout << "Error that channel doesnt exist";
		return -1;
	}
	else
	{
	//	cout << "Checking status of channel " << num << endl;
		return Channels[num].used;
	}
}
int Node::checkChannelWeight(int num){ // check weight of a channel
	if(num > Channels.size()){
		cout << "Error that channel doesnt exist";
		return -1;
	}
	else
	{
		return Channels[num].weight;
	}
}

