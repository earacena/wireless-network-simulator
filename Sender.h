//
// Project Name: Wireless Network Simulaor
// File: Sender.h
// File Description: This file contains the interface for the Sender class. The
//                   Sender class takes the computation results from the 
//                   implemented algorithms and exports it to the GUI for
//                   display.

#ifndef SENDER_H
#define SENDER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>

typedef std::tuple<std::string, int, std::string> Hop;

class Sender {
 public:
  Sender(const std::string & filename);
    
  void export_data(const std::vector<std::vector<Hop>> & results);

 private:
  std::string filename_;
};

#endif // SENDER_H
