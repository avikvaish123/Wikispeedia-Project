#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <map>

using namespace std;

// In graph design, we decided to go with was an adjacency list
// We acheive this by creating Nodes that hold the data (article) and the next node (edge)

class Graph {
public:

    //This is the simple node structure that we followed
    struct Node {
        string article_;
        Node *next_;
    };

    // Constructor that holds the string relative paths to the tsv files
    Graph(string path_of_vertices, string path_of_edges);

    // Computes the adjacency list and stores it in a vector "vertices"
    void initialize_graph();

    // Computues the transpose of the graph and stores it in "vertices"
    void transpose_graph();

    // Performs a breadth-first search on two nodes
    // Returns a vector that stores the path between the Nodes
    // E.g. {Node2, Node5, Node3} <- Would be the shortest path between Node2 and Node3
    vector<string> bfs(Node* startingNode, Node* endingNode);

    // Accessor function that returns the adjacency list
    vector<Node *> getVertices();

    // Helper function that prints the adjacency list to the terminal
    // Used for testing as well as debugging any issues in our algorithms
    void printGraph();

    // Helper function that adds an article to the end of the linked list
    void push_back(Node *head, string article);

private:
    // Helper function that gets the edges "neighbors" of a vertex (article)
    Node* getEdges(string article);

    // Gets the index of a vertex in the adjacency list
    int getIndex(Node* node);

    // Stores the relative path to the tsv files
    string relative_path_of_vertices;
    string relative_path_of_edges;

    // Adjacency list stores as a vector of nodes
    vector<Node *> vertices;
};