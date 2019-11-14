#pragma
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Grid{
	public:
		Grid();
		Grid(int BSn, int DVn);
		void Add_BS(pair<int,int> coord);//A-C
		void Add_DV(char BSID);//0-9
		void printGrid();//Output grid to command line
		vector<pair<int,int> > get_BS_pos();
		vector<pair<int,int> > get_DV_pos();
		vector<pair<int,int> > get_DVs_at_BS(char id);//Gets coords of devices in the base station radius
		bool check_proximity(pair<int,int> A, pair<int,int> B);
		char grid_index(int x, int y);
		pair<int,int> random_DV_coord(char BSID);
	private:
		int max_BS;
		int BS_n;
		int max_DV;
		int DV_n;
		int grid_dim;
		int radius;
		vector<vector<char> > grid;//grid_dim x grid_dim vector
		vector<pair<int,int> > BS_pos;
		vector<pair<int,int> > DV_pos;
};
