#pragma
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Grid{
	public:
		Grid();
		void Add_BS(int x, int y);//A-C
		void Add_DV(int x, int y);//0-9
		void printGrid();//Output grid to command line
		vector<pair<int,int> > get_BS_pos();
		vector<pair<int,int> > get_DV_pos();
	private:
		int max_BS;
		int BS_n;
		int max_DV;
		int DV_n;
		int grid_dim;
		vector<vector<char> > grid;//grid_dim x grid_dim vector
		vector<pair<int,int> > BS_pos;
		vector<pair<int,int> > DV_pos;
};
