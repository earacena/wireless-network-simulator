//
// Project Name: Wireless Network Simulaor
// File: Sender.h
// File Description: This file contains the interface for the Sender class. The
//                   Sender class takes the computation results from the 
//                   implemented algorithms and exports it to the GUI for
//                   display.

#ifndef SENDER_H
#define SENDER_H

#include <string>

class Sender {
  Sender(const std::string filename);
  
  void read_data();

  void export_data();

};

#endif // SENDER_H
