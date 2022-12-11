#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <map>

using namespace std;

class Graph
{
public:
    struct Node
    {
        string article_;
        Node *next_;
    };

    Graph(string path_of_vertices, string path_of_edges);
    void initialize_graph();

    vector<string> bfs(Node* startingNode, Node* endingNode);


    vector<Node *> getVertices();
    void printGraph();

private:
    void push_back(Node *head, string article);
    Node* getEdges(string article);

    string relative_path_of_vertices;
    string relative_path_of_edges;

    vector<Node *> vertices;

    int getIndex(Node* node);

    // void dfs(Node* start, vector<bool>& visited);
    // void fillOrder();
    // Graph transpose();
};