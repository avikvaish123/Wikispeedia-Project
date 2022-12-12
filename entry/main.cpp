#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "graph.hpp"
#include "brandes.hpp"
#include "kosaraju.hpp"

using namespace std;

int main()
{
  string inputEdges;
  string inputVertices;

  cout << "Welcome to the wikispeedia pathfinder." << endl;
  cout << "Please enter the filepath to the input edges dataset: ";
  cin >> inputEdges;
  cout << "Please enter the filepath to the input vertices dataset: ";
  cin >> inputVertices;

  Graph graph(inputVertices, inputEdges);
  graph.initialize_graph();
  vector<Graph::Node*> vertices = graph.getVertices();

  int chooseMode;

  cout << "Which function do you want to perform? Select number (1) Shortest path between 2 nodes, (2) Centrality score of a node, (3) Strongly connected subgraph containing the given node" << endl;
  cin >> chooseMode;

  string startNode;
  string endNode;

  if (chooseMode == 1) {
    cout << "Starting node: ";
    cin >> startNode;
    cout << "Ending node: ";
    cin >> endNode;
    
    Graph::Node* startingNode;
    Graph::Node* endingNode;

    for (size_t i = 0; i < vertices.size(); i++) {
        //Starting Node
        if (vertices.at(i)->article_ == startNode) {
        startingNode = vertices.at(i);
        }
        //Ending Node
        if (vertices.at(i)->article_ == endNode) {
        endingNode = vertices.at(i);
        }
    }

    vector<string> path = graph.bfs(startingNode, endingNode);

    cout << "Shortest path between start and end nodes: " << endl;
    for (size_t i = 0; i < path.size(); i++) {
      cout << path[i];
      if (i < path.size() - 1) {
        cout << " -> ";
      }
    }
    cout << endl;
  } else if (chooseMode == 2) {
    string centerNode;
    cout << "Node: ";
    cin >> centerNode;

    Brandes b;
    Graph brandes_graph(inputVertices, inputEdges);
    brandes_graph.initialize_graph();
    map<string, int> brandes_out = b.calculate(brandes_graph);
    cout << "Centrality score: " << brandes_out[centerNode];

    cout << endl;
    
  } else if (chooseMode == 3) {
    string node;
    cout << "Node: ";
    cin >> node;

    Kosaraju k;
    Graph kosa_graph(inputVertices, inputEdges);
    Graph kosa_transpose(inputVertices, inputEdges);
    kosa_graph.initialize_graph();
    kosa_transpose.transpose_graph();
    vector<vector<string>> kosa_out = k.kosaraju(kosa_graph, kosa_transpose);

    vector<string> output;
    for (size_t i = 0; i < kosa_out.size(); i++) {
      for (size_t j = 0; j < kosa_out[i].size(); j++) {
        if (kosa_out[i][j] == node) {
          output = kosa_out[i];
          break;
        }
      }
    }

    cout << "Strongly connected component containing the node: " << endl;
    for (size_t i = 0; i < output.size(); i++) {
      cout << output[i];
      if (i < output.size() - 1) {
        cout << " , ";
      }
    }
    cout << endl;
  } else {
    cout << "That is not a supported function." << endl;
  }

  return 0;
}
