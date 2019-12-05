// Project Name: Wireless Network Simulaor
// File: Receiver.cpp
// File Description: This file contains the implementations for the Receiver class. 

#include "Receiver.h"

Receiver::Receiver() {  }

void Receiver::read_data_from_GUI(const std::string & filename) {
  std::ifstream file(filename);
  if (file.is_open()) {
    std::string line;
    std::cout << "Reading file data:" << std::endl;
    while (std::getline(file, line)) {
      std::cout << "\t" << line << std::endl;
      file_data_.push_back(line);
    }
  }
}

void Receiver::parse_data() {
    std::string token;
    for(std::string line : file_data_) {
        token = line.substr(0, line.find(' '));
        if (token == "GD") {
          line.erase(0, line.find(' ') + 1);
          grid_size = std::stoi(line);
          std::cout << "Parsed grid size: " << grid_size << std::endl;

        } else if (token == "BSN") {
          line.erase(0, line.find(' ') + 1);
          num_of_base_stations = std::stoi(line);
          std::cout << "Parsed number of base stations: " << num_of_base_stations
                    << std::endl;
        } else if (token == "BSR") {
          line.erase(0, line.find(' ') + 1);
          base_station_radius = std::stoi(line);
          std::cout << "Parsed base station radius: " << base_station_radius
                    << std::endl;
          
        } else if (token == "NN") {
          line.erase(0, line.find(' ') + 1);
          num_of_nodes = std::stoi(line);
          std::cout << "Parsed number of nodes: " << num_of_nodes << std::endl;

        } else if (token == "B") {
          unparsed_bs_data.push_back(line);
          std::cout << "Parsed base station: " << line << std::endl;

        } else if (token == "N") {
          std::cout << "Parsed node: " << line << std::endl; 
          
        } else if (token == "R") {
          std::cout << "Parsed route request: " << line << std::endl;
        }
    } 
}

void print_file_data() {

}
