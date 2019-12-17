//all route finder algorithm


/********************************************************************************
Author: Shonel 
About: Driver file to test my route finding algorithms

I used a mini version of the node class with the bare essentials. I basically
make a random graph in the main by connecting all the nodes generated randomly.

All the nodes are generated dynamically. Idk dumb move i guess.
Everything is done using pointers because the nodes are dynamic so the only way
to access them is using the "graph" vector which holds their addresses

The input are hard coded string names in the main.
BFS will return a vector of the hops needed to get from the source node to the 
destination node. 


**********************************************************************************/

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <time.h>
#include <queue>
#include <stdlib.h>

using namespace std;

//==================================psuedo-Node Class================================//
class Node {
public:
		// default constructor
	Node() = default;// default constructor
		//constructor given the name of the node
	Node(string given_id){
		name = given_id;
	};
		//returns the node name
	string getName(){
		return name;
	};
		//conceptually this will be all the nodes in range of the node
	vector<Node*> adjacent_nodes; 
		//populates the adjacent node vector
	void assert_in_range(Node* new_node){
		Node* p = new_node;
		adjacent_nodes.push_back(p);
	};
	bool is_adjacent_to(Node* test_node){
		for(int i=0; i < adjacent_nodes.size(); i++){
			if(test_node == adjacent_nodes[i]){
				return true;
			}
		}

		return false;

	};

	/*----- ~ the following variables are just for the BFS implementation ~ ------*/
		//tracker to see if the node has been discovered; 
		//0 = UNDISCOVERED, 1 = NEIGHBORS UNDISCOVERED, 2 = FULLY DISCOVERED
	int discovered = 0;
		//the number of hops; initialized to 100 to imitate infinity
	int hops = 100;
		//when running BFS we need to see the parent node
	Node* previous_hop = nullptr;
	/*----------------------------------------------------------------------------*/

private:
		//name of node
	string name;
};

//=================================================================================//








/*============================== Functions =======================================*/

//prints out the entire graph, so we can trace it by hand to check work
void print_graph(vector<Node*> graph, int number_of_nodes){
	for(int i = 0; i < number_of_nodes; i++){
		cout<< graph[i]->getName() << endl << "\t";

		for(int j=0; j < graph[i]->adjacent_nodes.size(); j++){
			cout<< graph[i]->adjacent_nodes[j]->getName()
				<< " ";
		}

		cout<< endl;
	}
}

//prints the route when given a vector of pointers to nodes
void print_route(vector<Node*> route_vector){
	//if the route vector is empty there, the node is not in the graph
	if(route_vector.size() == 0){
		cout<< "there is no such node in the current graph :( \n";
		return;
	}
	//else: print out the graph
	for(int i = 0; i < route_vector.size(); i++){
		cout<<route_vector[i]->getName()<<"->";
	}
	cout<< endl;
}

//passing the src node and the list of all nodes which is our graph
vector<Node*> BFS( vector<Node*> graph, string src_node_name, string dest_node_name){
	//the vector that holds the route backwards; dest -> src. Basically a stack
	//I swap it at the end
	vector<Node*> shortest_route;
//------------------------------------error handling--------------------------------
	//find index of the source node
	int src_index = -1;
	for(int i = 0; i < graph.size(); i++ ){
		if( graph[i]->getName() == src_node_name){
			src_index = i;
		}
	}
	//check if the node is even in the graph
	if (src_index == -1){
		return shortest_route; //node is not in the graph; returns an empty vector
	}
	
	//find the index of the destination node
	int dest_index = -1;
	for(int i = 0; i < graph.size(); i++ ){
		if( graph[i]->getName() == dest_node_name){
			dest_index = i;
		}
	}
	if (dest_index == -1){
		return shortest_route; 
	}
//-------------------------actually starting the algorithm--------------------------
	//for each node that is not the src node, set them to be undiscovered
	for(int i = 0; i < graph.size(); i++){
		if(i != src_index){
			graph[i]->discovered = 0;
			graph[i]->hops = 100;
			graph[i]->previous_hop = nullptr;
		}
	}
	//using index of src to initialize the src node variables
	graph[src_index]->discovered = 1;
	graph[src_index]->hops = 0;
	graph[src_index]->previous_hop = nullptr;

	//this is a queue to keep track of nodes that have not been fully discovered
	queue<Node*> Q_needs_discovering;
	Q_needs_discovering.push(graph[src_index]);
	//this is just a temporary pointer
	Node* curr_node = nullptr; 
	while(!Q_needs_discovering.empty()){
		//pointer to the top node in the Queue
		curr_node = Q_needs_discovering.front();
		//cout<< curr_node->adjacent_nodes.size() << endl;
		for(int i = 0; i < curr_node->adjacent_nodes.size(); i++){
			//pointer to the current adjacent node
			Node* adj_node = curr_node->adjacent_nodes[i];
			if(adj_node->discovered == 0){ //if the adjacent node is undiscovered
				adj_node->discovered = 1;
				adj_node->hops = curr_node->hops + 1;
				adj_node->previous_hop = Q_needs_discovering.front();
				Q_needs_discovering.push(curr_node->adjacent_nodes[i]);
				adj_node = nullptr; 
			}
		}
		//we have accessed every adjacent node thus this current node is fully discovered
		curr_node->discovered = 2;
		Q_needs_discovering.pop();
	}
	curr_node = nullptr;

	//:::::::::::::::: above we find the route, below we prepare the output :::::::::::::::://

	curr_node = graph[dest_index]; //starting from the destination we're working backwards
	//reminder: { vector<Node*> shortest_route } the vector that holds the route backwards
	vector<Node*> return_route; //the vector that will be returned
	shortest_route.push_back(graph[dest_index]); //push the destination in

	//Im checking if destination is even reachable from the source; 
	//100 is a placeholder for infinity
	if(curr_node->hops < 100){ 
		while(curr_node->previous_hop != nullptr){
    		shortest_route.push_back(curr_node->previous_hop);
    		curr_node = curr_node->previous_hop;
		}
		//the vector was populated backwards so I'm just swapping indices
		int length = shortest_route.size();
		for(int i = 0; i < length; i++){
			return_route.push_back(shortest_route.back());
			shortest_route.pop_back();
		}
	}

	for(int i = 0; i < return_route.size(); i++){
		cout<<return_route[i]->getName()<<endl;
	}
	curr_node = nullptr;
	return return_route;
}	


/*=================================================================================*/







//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main() ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

int main(){
		//number of nodes in this system
	int number_of_nodes = 5;
		//list of all the nodes
	vector<Node*> graph;

		//initializes the nodes
	char letter = 'A';
	for(int i = 0; i < number_of_nodes; i++){
		//creates new node, names it a letter, stores it in the graph
		graph.push_back( new Node(string(1,letter)) );
		letter++;
	}
		//makes a graph of the nodes
	for(int i = 0; i < number_of_nodes; i++){
		for(int j = i; j < number_of_nodes; j++){
			Node* current_node = graph[i];
			Node* target_node = graph[j];
			int target_node_index = j;

			if( i == target_node_index){ //the random node selected is the src
				//do nothing
			}
			else if (current_node->is_adjacent_to(target_node)){
				//also do nothing; the node is already adjacent
			}
			else{
				current_node->assert_in_range(target_node);
				target_node->assert_in_range(current_node);
			}

			current_node = nullptr;
			target_node = nullptr;
			j++;
		}
	}
	print_graph(graph, number_of_nodes);


/*========================= ~ the actual algorithims ~ ==============================*/

/*------------------------- ~ all route generation ~ -------------------------------*/
	
	//list of nodes with the same number of hops
	vector<string> list_of_routes_with_equal_hops;
	//an array with with 10 indices; because the largest number of hops is 10
	vector<string> sorted_array_of_all_routes[11];

	//pass the array to be populated
	//populate_Route_List( name of array )
		//start a vector to hold the nodes
		//function that runs (list, node )
			//if this is the dest node: stop
				//push the node into the vector
			//else if the node is in the vector: stop
			//else: run the function on each adjacent node
				//push the node into the vector

/*----------------------- ~ shortest hops generator (BFS) ~ ------------------------*/
	string source = "Z";
	string destination = "E";
	vector<Node*> vec = BFS(graph, source, destination);
	print_route(vec);

	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//







