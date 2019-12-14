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
    def __init__(self, filename):
        print("[METRICS] Parsing incoming data from file '{}'".format(filename))
        self.parsed = parse_incoming_data(filename)

        print("[METRICS] Results of parsing: {}".format(self.parsed))

    def generate_hops_vs_devices(self):
        print("[METRICS] Generating graph 'hops vs nodes' with dataset {}.".format(self.parsed))

        num_of_nodes = []
        for data in self.parsed:
            print("{}".format(data))
            num_of_nodes.append(data[1])

        num_of_hops = []
        for data in self.parsed:
            num_of_hops.append(data[3])

        # Find largest node count to create the labels on left (hops)
        largest_hops = 0
        for hops in num_of_hops:
            if hops > largest_hops:
                largest_hops = hops

        # Find largest  node count to create the labels on bottom ()
        largest_nodes = 0
        for nodes in num_of_nodes:
            if nodes > largest_nodes:
                largest_nodes = nodes


        print("[Metrics] Hops: {}".format(num_of_hops))
        print("[Metrics] Nodes: {}".format(num_of_nodes))
        y_pos = np.arange(len(num_of_nodes))        
        #num_of_hops = [str(i) for i in num_of_hops]
        plt.bar(y_pos, num_of_hops, align='center', alpha=0.5)
        plt.xticks(y_pos, num_of_nodes)
        plt.xlabel("Number of Nodes")
        plt.ylabel("Number of Hops")
        plt.title("Number of Hops vs. Number of Nodes")

        #plt.show()
        plt.savefig("graph-hops-nodes.png")

    def generate_switches_vs_channels(self):
        print("[METRICS] Generating graph 'switches vs channels' with dataset {}.".format(self.parsed))

        num_of_channels = []
        for data in self.parsed:
            print("{}".format(data))
            num_of_channels.append(data[4])

        num_of_switches = []
        for data in self.parsed:
            num_of_switches.append(data[5])

        # Find largest switches count to create the labels on left (switches)
        largest_switches = 0
        for switches in num_of_switches:
            if switches > largest_switches:
                largest_switches = switches

        # Find largest channel count to create the labels on bottom (channels)
        largest_channels = 0
        for channels in num_of_channels:
            if channels > largest_channels:
                largest_channels = channels


        print("[Metrics] Switches: {}".format(num_of_switches))
        print("[Metrics] Channels: {}".format(num_of_channels))
        y_pos = np.arange(len(num_of_channels))        
        plt.clf()
        plt.bar(y_pos, num_of_switches, align='center', alpha=0.5)
        plt.xticks(y_pos, num_of_channels)
        plt.xlabel("Number of Channels")
        plt.ylabel("Number of Switches")
        plt.title("Number of Switches vs. Number of Channels")

        #plt.show()
        plt.savefig("graph-switches-channels.png")
 
def parse_incoming_data(filename):
    """
    Read data from specified file and parse into sublists.
    Data Format:
        # of nodes
        # of channels
        # of randomization samples
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
            if '@' in line:
                num_of_channels = int(line.strip('\n').strip('@').strip(' '))
            if '^' in line:
                num_of_samples = int(line.strip('\n').strip('^').strip(' '))
            if '%' in line:
                hops.append(int(line.strip('\n').strip('%').strip(' ')))
            if '*' in line:
                switches.append(int(line.strip('\n').strip('*').strip(' ')))
            if '%' in line:
                channels_utilized.append(int(line.strip('\n').strip('$').strip(' ')))

    dataset = [num_of_nodes, num_of_channels, num_of_samples, hops, switches, channels_utilized]
    return dataset

def main():
    """ Main function. """
    filename = "test-metrics-data"

    metrics = Metrics(filename)

    # Generate plots
    metrics.generate_hops_vs_devices()
    metrics.generate_switches_vs_channels()
