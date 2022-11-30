#include "catch.hpp"
#include "catchmain.cpp"
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <time.h>
#include <utility>
#include <cmath>

#include "../src/graph.cpp"

using namespace std;

TEST_CASE("Simple BFS", "[weight=1][part=1]") {
    Graph graph("tests/testNodes.tsv", "tests/testLinks.tsv");

    //initalize edges using adjacency list
    graph.initialize_graph();

    vector<Graph::Node*> vertices = graph.getVertices();
    Graph::Node* startingNode;
    Graph::Node* endingNode;

    for (size_t i = 0; i < vertices.size(); i++) {
        //Starting Node
        if (vertices.at(i)->article_ == "NodeA") {
        startingNode = vertices.at(i);
        }
        //Ending Node
        if (vertices.at(i)->article_ == "NodeF") {
        endingNode = vertices.at(i);
        }
    }

    vector<string> path = graph.bfs(startingNode, endingNode);
    vector<string> correctPath{"NodeA", "NodeC", "NodeF"};

    for (size_t j = 0; j < path.size(); j++) {
        REQUIRE(path[j] == correctPath[j]);
    }
}