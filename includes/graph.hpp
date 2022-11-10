#include <vector>
#include <string>
#include <iostream>
#include <fstream>

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

    void push_back(Node *head, string article);

    vector<Node *> getVertices();
    void printGraph();

private:
    string relative_path_of_vertices;
    string relative_path_of_edges;

    vector<Node *> vertices;
};