//
// Project Name: Wireless Network Simulaor
// File: DataCollector.hpp
// File Description: This file contains the interface for the DataCollector 
//                   class and methods.
//

#ifndef DATACOLLECTOR_HPP
#define DATACOLLECTOR_HPP

#include <string>
#include <pair>
#include <fstream>
<<<<<<< HEAD
=======
#include "Grid.h"
>>>>>>> 483c886175ccbe1b032dbd0856e105c099247159

// DataCollector will record important performance metrics during simulation
// that will be used to generate graphs and visualizations.
class DataCollector {
public:

  DataCollector(const std::string & filename);
  void initialize(int grid_size, int num_of_channels, int num_of_devices,
                  const std::vector<std::pair<int, int> > & node_pos,
                  const std::vector<std::pair<int, int> > & station_pos);

  /* Data collection */
  // Store computed path as a Path object in a vector.
  // post: Path object is stored in DataCollector.nodePaths.
  // void storePath();

  // After finishing a path computation, update the vector containing hops across
  // n transmissions by recording the value.
  void update_hops_for_session(int hops);

  // After finishing a path computation, update the vector containing channel switches
  // across n transmissions by recording the value.
  void update_switches_for_session(int switches);

  // Write all collected data to file.
  void export_data();

<<<<<<< HEAD
=======
  // Fill these directly from Grid class.
  std::vector<std::pair<int, int> > node_positions;
  std::vector<std::pair<int, int> > station_positions;

>>>>>>> 483c886175ccbe1b032dbd0856e105c099247159
private:
  std::string filename_;

  // Simulator session parameters
  int grid_size_;
  int num_of_channels_;
  int num_of_devices_;

  // Performance metrics
  std::vector<int> num_of_hops_;
  int num_of_channel_switches_;
<<<<<<< HEAD

  // Fill these directly from Receiver class.
  std::vector<std::pair<int, int> > node_positions;
  std::vector<std::pair<int, int> > station_positions;
=======
>>>>>>> 483c886175ccbe1b032dbd0856e105c099247159
};

#endif // DATACOLLECTOR_HPP
