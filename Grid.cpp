#include "Grid.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
Grid::Grid(){
	max_BS = 3;
	BS_n = 0;
	max_DV = 10;
	DV_n = 0;
	grid_dim = 50;
	radius = 15;
	for(int i = 0; i < grid_dim; i++){
		vector<char> v(grid_dim, '-');
		grid.push_back(v);
	}
	cout << grid[0].size();
	cout << "Initialized Grid" << endl;
}

void Grid::Add_BS(int x, int y){
	if(BS_n < max_BS && grid[x][y] == '-'){
		char BSID = char(BS_n+65);
		grid[x][y] = BSID;
		BS_n++;
		pair<int,int> position (x,y);
		BS_pos.push_back(position);
	}
	cout << "BS Added at (" << x << "," << y << ")" << endl;
}


void Grid::Add_DV(int x, int y){
	if(DV_n < max_DV && grid[x][y] == '-'){
		char BSID = char(DV_n+48);
		grid[x][y] = BSID;
		DV_n++;
		pair<int,int> position (x,y);
		DV_pos.push_back(position);
	}
        cout << "Device Added at (" << x << "," << y << ")" << endl;
}

void Grid::printGrid(){
	for(int i = 0; i < grid.size(); i++){
                for(int j = 0; j < grid[i].size(); j++){
                        cout << grid[i][j];
                }
		cout << endl;
        }
}

vector<pair<int,int> > Grid::get_BS_pos(){
	return BS_pos;
}

vector<pair<int,int> > Grid::get_DV_pos(){
        return DV_pos;
}

vector<pair<int,int> > Grid::get_DVs_at_BS(char id){
	int x;
	int y;
	vector<pair<int,int> > dvs;
	for(int i = 0; i < BS_pos.size(); i++){
		x = BS_pos[i].first;
		y = BS_pos[i].second;
		if(grid[x][y]==id){
cout << "Checking for devices near " << id << "..."<< endl;
			for(int j = 0; j < DV_pos.size(); j++){
				if(check_proximity(BS_pos[i], DV_pos[j])){
					dvs.push_back(DV_pos[j]);	
					cout << grid_index(DV_pos[j].first,DV_pos[j].second) << endl;
				}
			}	
		}
	}
	return dvs;
}

bool Grid::check_proximity(pair<int,int> A,pair<int,int> B){//A origin point, B point of DV
	int a = abs(A.first-B.first);
	int b = abs(A.second-B.second);
	float c = sqrt((a*a)+(b*b));
cout << "Dist: " << c << endl;
	if(c <= radius)
		return true;
	else
		return false;
}

char Grid::grid_index(int x, int y){
	return grid[x][y];
}
