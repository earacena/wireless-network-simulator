// Project Name: Wireless Network Simulaor
// File: Receiver.h
// File Description: This file contains the interface for the Receiver class. 
//                   The class reads the data generated by the GUI and parses
//                   it into the Grid class, for further computation.
//
// Changes by AL:
// 12/13/19 
// - read_data_from_GUI now has 2 arguments: file_name (name of file) and vector<string>(where each line from file gets stored as string) 
// - default allocator now opens and parses those files automatically

#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>

#include "Node.h"
#include "BaseStation.h"

typedef std::pair<std::string, std::string> Request;

class Receiver {
  public:
  Receiver();

  void read_data_from_GUI(const std::string & filename, std::vector<std::string> &file_data);
  void parse_data(const std::vector<std::string> &data_name);
  void print_file_data();

  // Accessible to other classes
  int grid_size;
  int num_of_base_stations;
  int base_station_radius;
  int num_of_nodes;
  int node_radius;

  std::vector<BaseStation> basestations;
  std::vector<Node> nodes;
  std::vector<Request> requests;
  
  private:
  std::vector<std::string> file_data_;

  // AL Changes
  std::vector<std::string> read_data;
  std::vector<std::string> read_data1;
  std::vector<std::string> read_data1B;
  std::vector<std::string> read_data2;
  std::vector<std::string> read_data2B;
  std::vector<std::string> read_data3B;

};

#endif // RECEIVER_H
