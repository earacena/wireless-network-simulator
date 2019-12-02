//
// Project Name: Wireless Network Simulaor
// File: Sender.cpp
// File Description: This file contains the implementations for the Sender class.

#include "Sender.h"

Sender::Sender() {  }

void Sender::read_data() { }

void Sender::export_data() {
  std::string filename = "routes.txt";

  std::fstream file(filename);
  if (s.is_open()) {
    // s << data;
  } else {
    std::cout << "[ERROR] Failed to open " + filename + "...";
  }
  
}
