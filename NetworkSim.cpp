#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include "Entities.h"

using namespace std;

typedef pair<int,int> Pair;

int main(){

	// sample for setting node position using pair
	Node node1;

	Pair sample1(8,9);
	node1.setPosition(sample1);

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