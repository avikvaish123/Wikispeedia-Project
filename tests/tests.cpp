#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <time.h>
#include <utility>
#include <cmath>

#include "graph.hpp"

using namespace std;

TEST_CASE("Load Graph", "[weight=1][part=1]") {
    Graph graph("tests/testNodes.tsv", "tests/testLinks.tsv");

    graph.initialize_graph();

    REQUIRE(graph.getVertices().size() == 6);
}

TEST_CASE("Test Graph for Edges", "[weight=1][part=1]") {
    Graph graph("tests/testNodes.tsv", "tests/testLinks.tsv");

    graph.initialize_graph();

    Graph::Node* testNode = graph.getVertices().at(0);

    while(testNode->article_ != "NodeC" && testNode->next_ != NULL) {
        testNode = testNode->next_;
    }

    REQUIRE(testNode->article_ == "NodeC");
}

TEST_CASE("Empty Graph BFS", "[weight=1][part=1]") {
    Graph graph("tests/empty.tsv", "tests/empty.tsv");

    graph.initialize_graph();
}

TEST_CASE("Simple BFS", "[weight=1][part=1]") {
    Graph graph("tests/testNodes.tsv", "tests/testLinks.tsv");

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