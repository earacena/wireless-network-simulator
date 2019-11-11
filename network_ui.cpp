#include <vector>
#include <string>
#include <iostream>
#include "Grid.h"
using namespace std;
	
int user_input_num(string type,int range_start,int range_end){
	int n;
	cout << "Select number of " << type << " between " << range_start << "-" << range_end << ": ";
	cin >> n;
	if(n >= range_start && n <= range_end){
		cout<< n << " " << type << " selected." << endl;
		return n;
	}
	else{
		while(!(n >= range_start && n <= range_end)){
			cout << "Enter a valid number: ";
			cin >> n;
		}
		return n;
	}
}//User input for a number of devices/base stations

void print_route(vector<int> route_list){
	for(int i = 0; i < route_list.size(); i++){
		if(i==0){
			cout << route_list[i] ;
		}
		else{
			cout << "->" << route_list[i];
		}
	}
	cout << endl;
}

int main(){
	int bs = user_input_num("base stations", 1, 3);
	int dv = user_input_num("devices", 1, 10);
	//Populate grid with base stations, devices
	//Ask for source and destination
	//Return route
	vector<int> test(5,8);
	print_route(test);
	Grid testgrid;
	testgrid.printGrid();
	testgrid.Add_BS(5, 20);
	testgrid.Add_DV(18, 40);
	testgrid.printGrid();
	return 0;
}
