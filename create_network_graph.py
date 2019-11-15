
"""
    Project Name: Wireless Network Simulator
    File: create_network_graph.py
    Description: This file will take a data file created by the simulator
                 in order to create a graph based on the data.
"""
import networkx as nx
import matplotlib.pyplot as plt



def main():
    filename = "simulator-data.txt"
    data = []
    with open(filename, "r") as file:
        for line in file:
            data.append(line)

    print(data)

main()
