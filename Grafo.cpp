//
// Created by andre on 28/02/2023.
//
#include "Grafo.h"

// Node structure to represent a vertex in the graph
struct Node {
    string name;
    vector<Node*> neighbors;
};

// Graph class to represent a graph
class Graph {
public:
    unordered_map<string, Node*> nodes;

    void addNode(string name) {
        Node* node = new Node;
        node->name = name;
        nodes[name] = node;
    }

    void addEdge(string node1, string node2) {
        nodes[node1]->neighbors.push_back(nodes[node2]);
        nodes[node2]->neighbors.push_back(nodes[node1]);
    }
};

// Function to split a string by a delimiter
vector<string> split(string str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to read from a CSV file and create a graph
Graph readCSV(string filename) {
    Graph graph;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        string node1 = tokens[0];
        string node2 = tokens[1];
        if (graph.nodes.find(node1) == graph.nodes.end()) {
            graph.addNode(node1);
        }
        if (graph.nodes.find(node2) == graph.nodes.end()) {
            graph.addNode(node2);
        }
        graph.addEdge(node1, node2);
    }
    return graph;
}