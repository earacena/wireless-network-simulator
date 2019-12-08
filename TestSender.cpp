//
// Project: Wireless Network Simulator
// Description: This program tests proper parsing of results into a file following specified format.
//              Data format, every line is a new path:
//                srcId,channel,destId,...\n
//                ..
//
// How to build:
// g++ TestSender.cpp Sender.cpp -o testsender
//
#include <iostream>
#include "Sender.h"

typedef std::tuple<std::string, int, std::string> Hop;

int main() {

  Sender sender("test-sender-results.txt");

  // Make dummy data
  std::vector<std::vector<Hop>> results;
  // path1
  Hop path1_hop1, path1_hop2, path1_hop3;

  path1_hop1 = std::make_tuple("A", 1, "B");
  path1_hop2 = std::make_tuple("B", 2, "C");
  path1_hop3 = std::make_tuple("C", 3, "D");

  std::vector<Hop> path1 = {path1_hop1, path1_hop2, path1_hop3};
  
  // path2
  Hop path2_hop1, path2_hop2, path2_hop3, path2_hop4;

  path2_hop1 = std::make_tuple("B", 1, "A");
  path2_hop2 = std::make_tuple("A", 2, "C");
  path2_hop3 = std::make_tuple("C", 1, "D");
  path2_hop4 = std::make_tuple("D", 4, "F");

  std::vector<Hop> path2 = {path2_hop1, path2_hop2, path2_hop3, path2_hop4};

  // Store in expected container
  results.reserve(3);
  results.push_back(path1);
  results.push_back(path2);
  
  // Save data
  sender.export_data(results);

  return 0;
}
