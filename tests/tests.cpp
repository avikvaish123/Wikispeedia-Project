#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <time.h>
#include <utility>
#include <cmath>
#include <map>
#include <algorithm>

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

//Test data loading and vertex loading with the full dataset
TEST_CASE("Load Graph Complex", "[weight=1][part=1]") {
    Graph graph("../dataset/articles.tsv", "../dataset/links.tsv");

    graph.initialize_graph();

    REQUIRE(graph.getVertices().size() == 4604);
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
TEST_CASE("Simple BFS onto itself", "[weight=1][part=1]") {
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
        if (vertices.at(i)->article_ == "NodeA") {
        endingNode = vertices.at(i);
        }
    }

    vector<string> path = graph.bfs(startingNode, endingNode);
    vector<string> correctPath{"NodeA", "NodeC", "NodeF", "NodeA"};

    for (size_t j = 0; j < path.size(); j++) {
        REQUIRE(path[j] == correctPath[j]);
    }
}

//Performing a complex BFS on a known section of the dataset
TEST_CASE("Complex BFS", "[weight=1][part=1]") {
    Graph graph("../tests/medium_vert.tsv", "../tests/medium_links.tsv");

    graph.initialize_graph();

    vector<Graph::Node*> vertices = graph.getVertices();
    Graph::Node* startingNode;
    Graph::Node* endingNode;

    for (size_t i = 0; i < vertices.size(); i++) {
        //Starting Node
        if (vertices.at(i)->article_ == "Africa") {
        startingNode = vertices.at(i);
        }
        //Ending Node
        if (vertices.at(i)->article_ == "Argentina") {
        endingNode = vertices.at(i);
        }
    }

    vector<string> path = graph.bfs(startingNode, endingNode);
    vector<string> correctPath{"Africa", "Atlantic_Ocean", "Argentina"};

    for (size_t j = 0; j < path.size(); j++) {
        REQUIRE(path[j] == correctPath[j]);
    }
}

//BFS between 2 nodes that are not connected
TEST_CASE("No path exists BFS", "[weight=1][part=1]") {
    Graph graph("../tests/medium_vert.tsv", "../tests/medium_links.tsv");

    graph.initialize_graph();

    vector<Graph::Node*> vertices = graph.getVertices();
    Graph::Node* startingNode;
    Graph::Node* endingNode;

    for (size_t i = 0; i < vertices.size(); i++) {
        //Starting Node
        if (vertices.at(i)->article_ == "Australian_rules_football") {
        startingNode = vertices.at(i);
        }
        //Ending Node
        if (vertices.at(i)->article_ == "Avatar__The_Last_Airbender") {
        endingNode = vertices.at(i);
        }
    }

    vector<string> path = graph.bfs(startingNode, endingNode);
    REQUIRE(path.size() == 0);
}

//Testing Brandes algorithm on an empty graph
TEST_CASE("Empty Brandes", "[weight=1][part=1]") {
    Brandes b;
    Graph brandes_graph("../tests/empty.tsv", "../tests/empty.tsv");
    brandes_graph.initialize_graph();
    map<string, int> brandes_out = b.calculate(brandes_graph);
    REQUIRE(brandes_out.size() == 0);
}

//Testing Brandes algorithm with no edges
TEST_CASE("No Edges Brandes", "[weight=1][part=1]") {
    Brandes b;
    Graph graph("../tests/testNodes.tsv", "../tests/empty.tsv");
    graph.initialize_graph();
    map<string, int> brandes_out = b.calculate(graph);
    REQUIRE(brandes_out["NodeA"] == 0);
    REQUIRE(brandes_out["NodeB"] == 0);
    REQUIRE(brandes_out["NodeC"] == 0);
    REQUIRE(brandes_out["NodeD"] == 0);
    REQUIRE(brandes_out["NodeE"] == 0);
    REQUIRE(brandes_out["NodeF"] == 0);
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

//Testing Kosaraju's algorithm on an empty graph
TEST_CASE("Empty Kosaraju", "[weight=1][part=1]") {
    Kosaraju k;
    Graph graph("../tests/empty.tsv", "../tests/empty.tsv");
    Graph graphTrans("../tests/empty.tsv", "../tests/empty.tsv");
    graph.initialize_graph();
    graphTrans.transpose_graph();
    vector<vector<string>> output = k.kosaraju(graph, graphTrans);

    REQUIRE(output.size() == 0);
}

//Testing Kosaraju's algorithm with no edges
TEST_CASE("No Edges Kosaraju", "[weight=1][part=1]") {
    Kosaraju k;
    Graph graph("../tests/testNodes.tsv", "../tests/empty.tsv");
    graph.initialize_graph();
    vector<vector<string>> output = k.kosaraju(graph, graph);

    vector<string> vecA{"NodeA"};
    vector<string> vecB{"NodeB"};
    vector<string> vecC{"NodeC"};
    vector<string> vecD{"NodeD"};
    vector<string> vecE{"NodeE"};
    vector<string> vecF{"NodeF"};

    REQUIRE(count(output.begin(), output.end(), vecA) != 0);
    REQUIRE(count(output.begin(), output.end(), vecB) != 0);
    REQUIRE(count(output.begin(), output.end(), vecC) != 0);
    REQUIRE(count(output.begin(), output.end(), vecD) != 0);
    REQUIRE(count(output.begin(), output.end(), vecE) != 0);
    REQUIRE(count(output.begin(), output.end(), vecF) != 0);
}

//Testing Kosaraju's algorithm on a simple graph
TEST_CASE("Simple Kosaraju", "[weight=1][part=1]") {
    Kosaraju k;
    Graph graph("../tests/kosa_vert.tsv", "../tests/kosa_edges.tsv");
    Graph graphTrans("../tests/kosa_vert.tsv", "../tests/kosa_edges.tsv");
    graph.initialize_graph();
    graphTrans.transpose_graph();
    vector<vector<string>> output = k.kosaraju(graph, graphTrans);

    REQUIRE(count(output[0].begin(), output[0].end(), "Node0") != 0);
    REQUIRE(count(output[0].begin(), output[0].end(), "Node1") != 0);
    REQUIRE(count(output[0].begin(), output[0].end(), "Node2") != 0);
    REQUIRE(count(output[1].begin(), output[1].end(), "Node3") != 0);
    REQUIRE(count(output[2].begin(), output[2].end(), "Node4") != 0);
    
}