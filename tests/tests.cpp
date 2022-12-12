#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <time.h>
#include <utility>
#include <cmath>
#include <map>

#include "graph.hpp"
#include "brandes.hpp"
#include "kosaraju.hpp"

using namespace std;

//Test data loading and vertex loading
TEST_CASE("Load Graph", "[weight=1][part=1]") {
    Graph testGraph("../tests/testNodes.tsv", "../tests/testLinks.tsv");

    testGraph.initialize_graph();

    REQUIRE(testGraph.getVertices().size() == 6);
}

//Test to make sure that edges are properly loaded
TEST_CASE("Test Graph for Edges", "[weight=1][part=1]") {
    Graph graph("../tests/testNodes.tsv", "../tests/testLinks.tsv");

    graph.initialize_graph();

    Graph::Node* testNode = graph.getVertices().at(0);

    while(testNode->article_ != "NodeC" && testNode->next_ != NULL) {
        testNode = testNode->next_;
    }

    REQUIRE(testNode->article_ == "NodeC");
}

//Initializing an empty graph
TEST_CASE("Empty Graph Loading", "[weight=1][part=1]") {
    Graph graph("../tests/empty.tsv", "../tests/empty.tsv");

    graph.initialize_graph();

    REQUIRE(graph.getVertices().size() == 0);
}

//Performing a simple BFS on a known graph
TEST_CASE("Simple BFS", "[weight=1][part=1]") {
    Graph graph("../tests/testNodes.tsv", "../tests/testLinks.tsv");

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

//BFS to itself
TEST_CASE("Simple BFS 2", "[weight=1][part=1]") {
    Graph graph("../tests/testNodes.tsv", "../tests/testLinks.tsv");

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

//Performing Brandes algorithm on a simple graph
TEST_CASE("Simple Brandes", "[weight=1][part=1]") {
    Graph testGraph("../tests/brandes_vert.tsv", "../tests/brandes_edges.tsv");

    testGraph.initialize_graph();

    Brandes b;
    map<string, int> map = b.calculate(testGraph);

    REQUIRE(map["Node1"] == 0);
    REQUIRE(map["Node2"] == 0);
    REQUIRE(map["Node3"] == 6);
    REQUIRE(map["Node4"] == 6);
    REQUIRE(map["Node5"] == 0);
    REQUIRE(map["Node6"] == 0);
}