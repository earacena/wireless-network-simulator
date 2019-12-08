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
		Channels[i].id = i;
	}
}
void Node::setDestination(Node &src, Node &dest){
}

string Node::getDestination(){}

void Node::setSource(Node &src, Node &dest){}

string Node::getSource(){}

bool Node::getBiggerWeight(Pair w1, Pair w2){
	
	return(w1.second > w2.second);

}

void Node::sortWeights(){

}

vector<int> Node::SortedWeightsByBest(){
	pair <int,int> channelandweight;
	vector<pair<int,int>> channelsandweights;
	for (size_t i = 0; i < Channels.size(); i++)
	{
		channelandweight.second = i; //id of the channel
		channelandweight.first = Channels[i].weight; // weight of the channel
		channelsandweights.push_back(channelandweight);
	}

	sort(channelsandweights.begin(),channelsandweights.end(),greater<Pair>()); // Sort by descending order


	vector<int> bestchannels;
	for (size_t i = 0; i < channelsandweights.size(); i++)
	{
	//	cout << "The best avail channel is " << channelsandweights.at(i).second << "with weight" << channelsandweights.at(i).first << endl;
		bestchannels.push_back(channelsandweights.at(i).second);
	}
//	cout << "found the best channels for node " << getName() << endl;
	bestChannelIds = bestchannels;
	return bestchannels;
}
vector<int> Node::getChannelWeights(){// get the channel weights for current node
	vector<int> currentChannelsWeights;
	cout << getName() << " channel weights are: " << endl;
	for(int i = 0; i < Channels.size(); i++){
//		cout << "Weight for Channel " << i << " is " << Channels[i].weight << " " << endl;
		currentChannelsWeights.push_back(Channels[i].weight);
	}
	return currentChannelsWeights;
}
vector<bool> Node::getAllChannelsStatus(){ // get all the channel use status for the current node
	vector<bool> currentChannelUse;
	for(int i = 0; i < Channels.size(); i++){
		currentChannelUse.push_back(checkChannelStatus(i));
	}
	return currentChannelUse;
}
vector<int> Node::getAllAvailableChannels(){// get all the free channels
	vector<int> freechannels;
	vector<bool> allchannels = getAllChannelsStatus();

	for (size_t i = 0; i < allchannels.size(); i++)
	{
		if(checkChannelStatus(i) == 0){
			freechannels.push_back(i); // push back if channel is free
		}
	}
	
	return freechannels;
}
int Node::getBestAvailableChannel(){ // get the best currently available channel for current node
	vector<int> bestChannels = bestChannelIds;
	for(int i = 0; i < Channels.size(); i++){
		if(checkChannelStatus(bestChannels[i]) == 0)// Channel available
		{
		//	cout << bestChannels[i] << " is the best available channel for node: " << getName() << endl;
			return bestChannels[i];
		}
	}
	return -1;
}
int Node::getBestAvailableChannel(int channeltoskip){ // get the best currently available channel for current node
	vector<int> bestChannels = getSortedChannelsByWeights();
	bool channelfound = false;
	int bestchannel = -1;
	for(int i = 0; i < bestChannels.size(); i++){
		if(bestChannels[i] != channeltoskip && channelfound ==false && checkChannelStatus(bestChannels[i]) == 0)// Channel available
		{
		//	cout << bestChannels[i] << " is the best available channel for node: " << getName() << endl;
			channelfound = true;
			bestchannel = bestChannels[i];
			return bestchannel;
		}
	}
	if(!channelfound){
	cout << "No Free Channels" << endl;
		return -1;
	}
	else
		return bestchannel;
}
bool Node::reserveChannel(int num){
	if(num > Channels.size()){
		cout << "Error that channel doesnt exist";
		return false;
	}
	else
	{
		cout << " Reserving the requested channel " << num << " for node " << getName() << endl;
		Channels[num].used = true;
		return true;
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
		cout << "Error that channel doesnt exist " << num << endl;
		return -1;
	}
	else if (Channels.size() > 11){
		cout << "problem" << 1 << endl;
		return -1;
	}
	else
	{	
	//	cout << " Checking status of channel " << num << " | " << "for node" << getName() << endl;
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

vector<int> Node::getSortedChannelsByWeights(){
	auto test = SortedWeightsByBest();
	//cout << " getting sorted weights of " << getName() << " " << bestChannelIds.size() << " " << test.size()<< endl;
	return bestChannelIds;
}

