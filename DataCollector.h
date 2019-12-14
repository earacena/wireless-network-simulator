//
// Project Name: Wireless Network Simulaor
// File: DataCollector.hpp
// File Description: This file contains the interface for the DataCollector 
//                   class and methods.
//
// Data format:
// ! # of nodes
// @ # of channels
// ^ # of randomization files
// % hops of gen 0 (original)
// % hops of gen 1
// % hops of gen 2
// % hops of gen 3
// ...
// %hops of gen n
// * switches of gen 0 (original)
// * switches of gen 1 
// * switches of gen 2 
// ...
// * switches of gen n
// $ channels utilized of gen 0 (original)
// $ channels utilized of gen 1
// ...
// $ channels utilized of gen n

#ifndef DATACOLLECTOR_HPP
#define DATACOLLECTOR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>
#include <tuple>

typedef std::tuple<std::string, int, std::string> Hop;

// DataCollector will record important performance metrics during simulation
// that will be used to generate graphs and visualizations.
class DataCollector {
public:

  DataCollector(const std::string & filename);
  void initialize(int num_of_nodes);

  /* Data collection */
  void collect_results(const std::vector<Hop> & path);

  // Write all collected data to file.
  void export_data();

private:
  std::string filename_;

  const int num_of_samples_ = 5;
  // Simulator graph parameters
  // Must be reset every scale up
  int num_of_nodes_;
  std::vector<int> hops_data_;
  std::vector<int> switches_data_;
  std::vector<int> channels_utilized_data_;
};

#endif // DATACOLLECTOR_HPP
