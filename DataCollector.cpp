// Project Name: Wireless Network Simulaor
// File: DataCollector.cpp
// File Description: This file contains the implementations for the DataCollector 
//                   class and methods.
//

#include "DataCollector.h"

DataCollector::DataCollector(const std::string & filename) { filename_ = filename; }

void DataCollector::initialize(int grid_size, int num_of_channels,
                               int num_of_devices, 
                               const std::vector<std::pair<int, int> > & node_pos,
                               const std::vector<std::pair<int, int> > & station_pos) {
  grid_size_ = grid_size;
  num_of_channels_ = num_of_channels;
  num_of_devices_ = num_of_devices;
  node_positions = node_pos;
  station_positions = station_pos;
}
 
// void storePath() { }

void update_hops_for_session(int hops) { num_of_hops_.push_back(hops); }

void update_switches_for_session(int switches) { num_of_switches.push_back(switches); }

void export_data() {
  std::ofstream file(filename_);
  // Simulator parameters
  file << "[parameters]\n"
  file << grid_size_ << "\n";
  file << num_of_devices_ << "\n";
  file << num_of_channels_ << "\n";

  // Node positions
  file << "[nodes]\n";
  for (std::pair<int, int> & position : nodes_positions) 
    file << position.first << " " << position.second << "\n";

  // Station positions
  file << "[stations]\n";
  for (std::pair<int, int> & position: station_positions)
    file << position.first << " " << position.second << "\n";

  // Performance metrics
  file << "[performance]\n";
  file << "[hops]\n";
  for (int value : num_of_hop_)
    file << value << "\n";

  file << "[switches]\n";
  for(int value: num_of_channel_switches) 
    file << value << "\n";
}
