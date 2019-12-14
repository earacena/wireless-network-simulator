// Project Name: Wireless Network Simulaor
// File: DataCollector.cpp
// File Description: This file contains the implementations for the DataCollector 
//                   class and methods.
//

#include "DataCollector.h"

DataCollector::DataCollector(const std::string & filename) : filename_(filename) {};

void DataCollector::initialize(int num_of_nodes) {
  // Delete previous file of same filename to prevent data being overwritten
  num_of_nodes_ = num_of_nodes;
}

void DataCollector::collect_results(const std::vector<Hop> & path) {
  hops_data_.push_back(path.size());

  std::vector<int> channels;
  int switches = 0;
  int utilized = 0;
  for (const Hop & hop : path) {
    if (std::find(channels.begin(), channels.end(), std::get<1>(hop)) == channels.end())
      channels.push_back(std::get<1>(hop));
  }
  utilized = channels.size();
  channels.clear();
  for (const Hop & hop : path) {
    if (std::find(channels.begin(), channels.end(), std::get<1>(hop)) == channels.end()) {
      channels.push_back(std::get<1>(hop)); 
    }
  }
  switches = channels.size() - 1;

  switches_data_.push_back(switches);
  channels_utilized_data_.push_back(utilized);
}

void DataCollector::export_data() {
  std::ofstream file(filename_);
  if (file.is_open()) {
    file << num_of_nodes_ << std::endl;
    file << num_of_samples_ << std::endl;

    // process hops
    for (int hops : hops_data_) 
      file << "% " << hops << std::endl;
      
    // process switches
    for (int switches : switches_data_) 
      file << "* " << switches << std::endl;
    
    // process channels utilized
    for (int utilized : channels_utilized_data_) 
      file << "$ " << utilized << std::endl; 
    
    file.close();
  } else {
    std::cout << "[Error] Creating file named [" + filename_ + "]..." << std::endl;
  }
}
