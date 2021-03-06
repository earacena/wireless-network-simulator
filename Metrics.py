"""
Project Name: Wireless Network Simulator

Description: Script will generate various charts using parsed data from
simulator.
"""
from __future__ import print_function

import matplotlib
import matplotlib.pyplot as plt
import numpy as np

class Metrics:
    def __init__(self):
        self.filenames = ["data-metrics.txt", "data1-metrics.txt", "data2-metrics.txt", 
                          "data1B-metrics.txt", "data2B-metrics.txt", "data3B-metrics.txt"]

        print("[METRICS] Parsing incoming data from file(s) '{}'".format(self.filenames))
        self.full_dataset = []
        
        for filename in self.filenames:
            self.full_dataset.append(parse_incoming_data(filename))

        # group with n nodes
        self.group1 = [self.full_dataset[0], self.full_dataset[1], self.full_dataset[2]]

        # group with n+1 nodes
        self.group2 = [self.full_dataset[3], self.full_dataset[4], self.full_dataset[5]]

        print("[METRICS] Results of parsing: {}".format(self.full_dataset))

    def generate_hops_vs_nodes(self):
        """ Create and save an image of a graph of avg. number of hops vs number of nodes. """
        # calculate group1 averages
        group1_node_count = self.group1[0][0]
        group1_hops = []
        for dataset in self.group1:
            group1_hops = group1_hops + dataset[3]
    
        group1_average = average(group1_hops)
        print("[Metrics] Group 1, Nodes: {}, Avg. Hops: {}".format(group1_node_count, group1_average))
                
        group2_node_count = self.group2[0][0]
        group2_hops = []
        for dataset in self.group2:
            group2_hops = group2_hops + dataset[3]

        group2_average = average(group2_hops)
        print("[Metrics] Group 2, Nodes: {}, Avg. Hops: {}".format(group2_node_count, group2_average))

        x_axis = [group1_node_count, group2_node_count]
        y_axis = [group1_average, group2_average]
 
        x_pos = np.arange(len(x_axis))
        plt.bar(x_pos, y_axis, align='center', alpha=0.5)
        plt.xticks(x_pos, x_axis)
        plt.xlabel("Number of Nodes")
        plt.ylabel("Avg. number of Hops")
        plt.title("Avg. Number of Hops vs. Number of Nodes")

        #plt.show()
        plt.savefig("graph-hops-nodes.png")

    def generate_switches_vs_nodes(self):
        """ Create a graph of channel switches vs number of nodes """
        plt.clf()
        # calculate group1 averages
        group1_node_count = self.group1[0][0]
        group1_switches = []
        for dataset in self.group1:
            group1_switches = group1_switches + dataset[3]
    
        group1_average = average(group1_switches)
        print("[Metrics] Group 1, Nodes: {}, Avg. Channel Switches: {}".format(group1_node_count, group1_average))
                
        group2_node_count = self.group2[0][0]
        group2_switches = []
        for dataset in self.group2:
            group2_switches = group2_switches + dataset[3]

        group2_average = average(group2_switches)
        print("[Metrics] Group 2, Nodes: {}, Avg. Channel Switches: {}".format(group2_node_count, group2_average))

        x_axis = [group1_node_count, group2_node_count]
        y_axis = [group1_average, group2_average]
 
        x_pos = np.arange(len(x_axis))
        plt.bar(x_pos, y_axis, align='center', alpha=0.5)
        plt.xticks(x_pos, x_axis)
        plt.xlabel("Number of Nodes")
        plt.ylabel("Avg. Number of Channel switches")
        plt.title("Avg. Number of Switches vs. Number of Nodes")

        #plt.show()
        plt.savefig("graph-switches-nodes.png")
 
    def generate_utilized_vs_nodes(self):
        """ Create a graph of channel utilized vs number of nodes """
        plt.clf()
        # calculate group1 averages
        group1_node_count = self.group1[0][0]
        group1_utilized = []
        for dataset in self.group1:
            group1_utilized = group1_utilized + dataset[4]
    
        group1_average = average(group1_utilized)
        print("[Metrics] Group 1, Nodes: {}, Avg. Channel Utilized: {}".format(group1_node_count, group1_average))
                
        group2_node_count = self.group2[0][0]
        group2_utilized = []
        for dataset in self.group2:
            group2_utilized = group2_utilized + dataset[4]

        group2_average = average(group2_utilized)
        print("[Metrics] Group 2, Nodes: {}, Avg. Channel utilized: {}".format(group2_node_count, group2_average))

        x_axis = [group1_node_count, group2_node_count]
        y_axis = [group1_average, group2_average]
 
        x_pos = np.arange(len(x_axis))
        plt.bar(x_pos, y_axis, align='center', alpha=0.5)
        plt.xticks(x_pos, x_axis)
        plt.xlabel("Number of Nodes")
        plt.ylabel("Avg. Number of Channels Utilized")
        plt.title("Avg. Number of Channels Utilized vs. Number of Nodes")

        #plt.show()
        plt.savefig("graph-utilized-nodes.png")

def average(list_of_numbers):
    """ Calculates the average of a list of numbers. """
    average = 0
    sum = 0

    for number in list_of_numbers:
        sum = sum + number
    average = sum / len(list_of_numbers)

    return average

def parse_incoming_data(filename):
    """
    Read data from specified file and parse into sublists.
    Data Format:
        ! # of nodes
        @ # of channels
        ^ # of randomization samples
        % hops of gen 0 (original graph)
        % hops of gen 1 (rand)
        % hops of gen 2 (rand)
        ...
        % hops of gen n (rand)
        * switches of gen 0 (original)
        * switches of gen 1 (rand)
        * switches of gen 2 (rand)
        ...
        * switches of gen n (rand)
        $ channels utilized of gen 0 (original)
        $ channels utilized of gen 1 (rand)
        $ channels utilized of gen 2 (rand)
        ...
        $ channels utilized of gen n (rand)

    """
    num_of_nodes = 0
    num_of_channels = 0
    num_of_samples = 0
    hops = []
    switches = []
    channels_utilized = []

    with open(filename) as data:
        for line in data:
            if '!' in line:
                num_of_nodes = int(line.strip('\n').strip('!').strip(' '))
            elif '@' in line:
                num_of_channels = int(line.strip('\n').strip('@').strip(' '))
            elif '^' in line:
                num_of_samples = int(line.strip('\n').strip('^').strip(' '))
            elif '%' in line:
                hops.append(int(line.strip('\n').strip('%').strip(' ')))
            elif '*' in line:
                switches.append(int(line.strip('\n').strip('*').strip(' ')))
            elif '$' in line:
                channels_utilized.append(int(line.strip('\n').strip('$').strip(' ')))

    dataset = [num_of_nodes, num_of_channels, num_of_samples, hops, switches, channels_utilized]
    print("[METRICS] Data parsed from '{}' file, : {}".format(filename, dataset))

    return dataset

def main():
    """ Main function. """

    metrics = Metrics()

    # Generate plots
    metrics.generate_hops_vs_nodes()
    metrics.generate_switches_vs_nodes()
    metrics.generate_utilized_vs_nodes()

main()
