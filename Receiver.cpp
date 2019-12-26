// Project Name: Wireless Network Simulaor
// File: Receiver.cpp
// File Description: This file contains the implementations for the Receiver class. 

// Changes by AL:
// 12/13/19 
// - read_data_from_GUI now has 2 arguments: file_name (name of file) and vector<string>(where each line from file gets stored as string) 
// - default allocator now opens and parses those files automatically

#include "Receiver.h"

Receiver::Receiver() {  
}

void Receiver::read_data_from_GUI(const std::string & filename, std::vector<std::string> &file_data_) {
  std::ifstream file(filename);
  if (file.is_open()) {
    std::string line;
    std::cout << "Reading file data:" << std::endl;
    while (std::getline(file, line)) {
      // std::cout << "\t" << line << std::endl;
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
          // grid_size = grid_size;

        } else if (token == "BSN") {
          line.erase(0, line.find(' ') + 1);
          num_of_base_stations = std::stoi(line);
          std::cout << "Parsed number of base stations: " << num_of_base_stations << std::endl;
        } else if (token == "BSR") {
          line.erase(0, line.find(' ') + 1);
          base_station_radius = std::stoi(line);
          std::cout << "Parsed base station radius: " << base_station_radius
                    << std::endl;
          
        } else if (token == "NN") {
          line.erase(0, line.find(' ') + 1);
          num_of_nodes = std::stoi(line);
          std::cout << "Parsed number of nodes: " << num_of_nodes << std::endl;
        } else if (token == "NR") {
          line.erase(0, line.find(' ') + 1);
          node_radius = std::stoi(line);
          std::cout << "Parsed node radius: " << node_radius << std::endl;


        } else if (token == "NR") {
          line.erase(0, line.find(' ') + 1);
          node_radius = std::stoi(line);
          std::cout << "Parsed node radius: " << node_radius << std::endl;


        } else if (token == "B") {

          line.erase(0, line.find(' ') + 1);
          std::string name = line.substr(0, line.find(' '));
          line.erase(0, line.find(' ') + 1);
          int pos_x = std::stoi(line.substr(0, line.find(',')));
          line.erase(0, line.find(',') + 1);
          int pos_y = std::stoi(line);
          
          BaseStation basestation(name, base_station_radius);
          std::pair<int, int> position = {pos_x, pos_y};
          basestation.setPosition(position);
          basestations.push_back(basestation);
          
          std::cout << "Parsed base station: " << std::endl;
          std::cout << "\tbasestation name: " << basestation.getName() << std::endl
                    << "\tbasestation radius: " << basestation.getRadius() << std::endl
                    << "\tbasestation positon: (" << basestation.getPosition().first
                    << ", " << basestation.getPosition().second << ")" << std::endl;
          
        } else if (token == "N") {
          line.erase(0, line.find(' ') + 1);
          std::string name = line.substr(0, line.find(' '));
          line.erase(0, line.find(' ') + 1);
          int pos_x = std::stoi(line.substr(0, line.find(',')));
          line.erase(0, line.find(',') + 1);
          int pos_y = std::stoi(line);
          
          Node node;
          node.setName(name);
          std::pair<int, int> position = {pos_x, pos_y};
          node.setPosition(position);
          nodes.push_back(node);
          
          std::cout << "Parsed node: " << std::endl;
          std::cout << "\tnode name: " << node.getName() << std::endl
                    << "\tnode positon: (" << node.getPosition().first
                    << ", " << node.getPosition().second << ")" << std::endl;
          
        } else if (token == "R") {
          line.erase(0, line.find(' ') + 1);
          std::string srcId = line.substr(0, line.find(','));
          line.erase(0, line.find(',') + 1);
          std::string destId = line;
          Request request {srcId, destId};
          requests.push_back(request);
          std::cout << "Parsed route request: (" << request.first << " -> " << request.second
                    << ")" << std::endl;
        }
        std::cout << basestations.size() << std::endl;
        BSN_Pair_List.push_back(make_pair(nodes,basestations));

    }
    std::cout << BSN_Pair_List.size() << std::endl;
 //   std::cout << BSN_Pair_List.size().first << std::endl;
}
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
        } else if (token == "NR") {
          line.erase(0, line.find(' ') + 1);
          node_radius = std::stoi(line);
          std::cout << "Parsed node radius: " << node_radius << std::endl;


        } else if (token == "B") {

          line.erase(0, line.find(' ') + 1);
          std::string name = line.substr(0, line.find(' '));
          line.erase(0, line.find(' ') + 1);
          int pos_x = std::stoi(line.substr(0, line.find(',')));
          line.erase(0, line.find(',') + 1);
          int pos_y = std::stoi(line);
          
          BaseStation basestation(name, base_station_radius);
          std::pair<int, int> position = {pos_x, pos_y};
          basestation.setPosition(position);
          basestations.push_back(basestation);
          
          std::cout << "Parsed base station: " << std::endl;
          std::cout << "\tbasestation name: " << basestation.getName() << std::endl
                    << "\tbasestation radius: " << basestation.getRadius() << std::endl
                    << "\tbasestation positon: (" << basestation.getPosition().first
                    << ", " << basestation.getPosition().second << ")" << std::endl;
          
        } else if (token == "N") {
          line.erase(0, line.find(' ') + 1);
          std::string name = line.substr(0, line.find(' '));
          line.erase(0, line.find(' ') + 1);
          int pos_x = std::stoi(line.substr(0, line.find(',')));
          line.erase(0, line.find(',') + 1);
          int pos_y = std::stoi(line);
          
          Node node;
          node.setName(name);
          std::pair<int, int> position = {pos_x, pos_y};
          node.setPosition(position);
          nodes.push_back(node);
          
          std::cout << "Parsed node: " << std::endl;
          std::cout << "\tnode name: " << node.getName() << std::endl
                    << "\tnode positon: (" << node.getPosition().first
                    << ", " << node.getPosition().second << ")" << std::endl;
          
        } else if (token == "R") {
          line.erase(0, line.find(' ') + 1);
          std::string srcId = line.substr(0, line.find(','));
          line.erase(0, line.find(',') + 1);
          std::string destId = line;
          Request request {srcId, destId};
          requests.push_back(request);
          std::cout << "Parsed route request: (" << request.first << " -> " << request.second
                    << ")" << std::endl;
        }
    } 
}
