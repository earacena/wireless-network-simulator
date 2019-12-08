//
// Project Name: Wireless Network Simulaor
// File: Sender.cpp
// File Description: This file contains the implementations for the Sender class.
//                   Assumed data results format:
//                     typedef std::tuple<std::string, int, std::string> Hop;
//                     std::vector< std::vector<Hop> >;
#include "Sender.h"

Sender::Sender(const std::string & filename) : filename_(filename) {}

void Sender::export_data(const std::vector<std::vector<Hop>> & results) {
  std::ofstream file(filename_);
  std::string srcId = "";
  int channel = 0;
  std::string destId = "";
  
  if (file.is_open()) {
    for (std::vector<Hop> path : results) {
      for (Hop hop : path) {
        srcId = std::get<0>(hop);
        channel = std::get<1>(hop);
        destId = std::get<2>(hop);

        file << srcId << "," << channel << "," << destId << ",";
      }
      file << "\n";
    }
    file.close();
  } else {
    std::cout << "[ERROR] Failed to open [" + filename_ + "]..." << std::endl;
  } 
}
