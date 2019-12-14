// Project Name: Wireless Network Simulaor
// File: Receiver.cpp
// File Description: This file contains the implementations for the Receiver class. 

// Changes by AL:
// 12/13/19 
// - read_data_from_GUI now has 2 arguments: file_name (name of file) and vector<string>(where each line from file gets stored as string) 
// - default allocator now opens and parses those files automatically

#include "Receiver.h"

Receiver::Receiver() {
  // reads all data from all 6 files
  read_data_from_GUI("data.txt", read_data);
  read_data_from_GUI("data1.txt", read_data1);
  read_data_from_GUI("data1B.txt", read_data1B);
  read_data_from_GUI("data2.txt", read_data2);
  read_data_from_GUI("data2B.txt", read_data2B);
  read_data_from_GUI("data3B.txt", read_data3B);

  // output all data from all 6 files
  parse_data(read_data);
  parse_data(read_data1);
  parse_data(read_data1B);
  parse_data(read_data2);
  parse_data(read_data2B);
  parse_data(read_data3B);
  
}

void Receiver::read_data_from_GUI(const std::string & filename, std::vector<std::string> &file_data) {
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

void Receiver::parse_data(const std::vector<std::string> &data_name) {
    std::string token;

    for(std::string line : data_name) {  
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
