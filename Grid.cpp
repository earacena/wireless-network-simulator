#include "Grid.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
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
	//cout << grid[0].size();
	cout << "Initialized Grid" << endl;
}

Grid::Grid(int BSn, int DVn){
cout << "BS: " << BSn << endl;
cout << "DVn: " << DVn << endl;
        max_BS = 3;
        BS_n = 0;
        max_DV = 10;
        DV_n = 0;
        grid_dim = 50;
        radius = 15;
        for(int i = 0; i < grid_dim; i++){
                vector<char> v(grid_dim, '-');
                grid.push_back(v);
        }//Initialize blank grid
	for(int i = 0; i < BSn; i++){
		srand(i+1);
		int x = rand()%(2+(grid_dim));
	//	srand(time(NULL));
		int y = rand()%(2+(grid_dim));
cout << "Adding BS" << endl;
		Add_BS(pair<int,int>(x,y));
	}//Place n random BS
	for(int i = 0; i < DVn; i++){
		srand(i+(grid_dim*(i+1)));
		int BS_num = 65+(rand()%BS_n);
		//if(BSn ==1){BS_num = 65;}
cout << "Adding device at BS [" << char(BS_num) << "]\n";
		Add_DV(char(BS_num));
	}//Place n devices randomly in a random BS radius
	cout << "Grid Intialized" << endl
	<< "Number of Base Stations: " << BS_n << endl
	<< "Number of Nodes: " << DV_n << endl;
}

void Grid::Add_BS(pair<int,int> coord){
        int x = coord.first;
        int y = coord.second;
	if(BS_n < max_BS && grid[x][y] == '-'){
		char BSID = char(BS_n+65);
		grid[x][y] = BSID;
		BS_n++;
		pair<int,int> position (x,y);
		BS_pos.push_back(position);
        cout << "BS [" << BSID << "] Added at (" << x << "," << y << ")" << endl;
	}
	else{
		cout << "BS add failed" << endl;
	}
}


void Grid::Add_DV(char BSID){
	/*pair<int,int> coord = random_DV_coord(BSID);
	int x = coord.first;
	int y = coord.second;*/
	//srand(time(NULL));
	for(int i = 0; i < BS_pos.size(); i++){
		if(grid[BS_pos[i].first][BS_pos[i].second] == BSID){
			int x = (BS_pos[i].first-(radius/2))+((rand()%radius)%grid_dim);
			int y = (BS_pos[i].second-(radius/2))+(rand()%radius)%grid_dim;
			if(x > grid_dim){x = grid_dim - (x-grid_dim);}
			if(y > grid_dim){y = grid_dim - (y-grid_dim);}
		       	if(DV_n < max_DV && grid[x][y] == '-'){
				grid[x][y] = char(DV_n+48);
                		pair<int,int> position (x,y);
                		DV_pos.push_back(position);
				DV_n++;
cout << "Device " << DV_n-1 << " Added in "<< BSID << " (" << x << "," << y << ")" << endl;

        		}
			else{
                        	cout << "Device add failed" << " (" << x << "," << y << ")" << endl;
                	}
		}
	}
}

void Grid::printGrid(){
	for(int i = 0; i < grid.size(); i++){
                for(int j = 0; j < grid[i].size(); j++){
                        cout << grid[i][j] << ' ';
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

pair<int,int> Grid::random_DV_coord(char BSID){
	int x;
        int y;
        pair<int,int> pos;
	if(BS_pos.size() == 0){cout<<"NO BS Found"<<endl;return pos;}
        for(int i = 0; i < BS_pos.size(); i++){//Find BS
                x = BS_pos[i].first;
                y = BS_pos[i].second;
                if(grid[x][y]==BSID){
			pos.first = rand()%(radius*2)+(x-(radius));
			pos.second = rand()%(radius*2)+(y-(radius));
			while(pos.first>=0 && pos.first < grid_dim && pos.second>=0 && pos.second < grid_dim && !check_proximity(BS_pos[i], pos)){
				pos.first = rand()%(radius*2)+(x-(radius));
                        	pos.second = rand()%(radius*2)+(y-(radius));
			}
		}
        }
        return pos;
}

