#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "graph.hpp"
#include "brandes.hpp"
#include "kosaraju.hpp"

using namespace std;

bool sortByVal(const pair<string, int> &a, 
               const pair<string, int> &b) 
{ 
    return (a.second > b.second); 
} 

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

  // ifstream fstream("../dataset/links.tsv");
  // ifstream fstream2("../dataset/articles.tsv");
  // ofstream outlinks;
  // ofstream outvert;
  // outlinks.open("../tests/medium_links.tsv", std::ios_base::app); // append instead of overwrite
  // outvert.open("../tests/medium_vert.tsv", std::ios_base::app);

  // string line;
  // string head_article = "";
  // int index = 0;
  // int count = 0;
  // while (getline(fstream, line)) {

  //   size_t vertex_index = line.find('\t');
  //   string article = line.substr(0, vertex_index);
  //   string edge = line.substr(vertex_index + 1);

  //   if (article[0] == 'A' && edge[0] == 'A') {
  //     count++;
  //     outlinks << line << endl;
  //   }
  // }

  // while (getline(fstream2, line)) {
  //   if (line[0] == 'A') {
  //     outvert << line << endl;
  //   }
  // }



  //Graph graph("../tests/medium_vert.tsv", "../tests/medium_links.tsv");
  //graph.initialize_graph();
  //vector<Graph::Node*> vertices = graph.getVertices();

  // Graph testGraph("../tests/medium_vert.tsv", "../tests/medium_links.tsv");
  // Graph testGraphTrans("../tests/medium_vert.tsv", "../tests/medium_links.tsv");

  // testGraph.initialize_graph();
  // testGraphTrans.transpose_graph();

  // Kosaraju k;
  // vector<vector<string>> sccs = k.kosaraju(testGraph, testGraphTrans);

  // std::ofstream outfile;

  // outfile.open("../tests/Kosaraju.txt", std::ios_base::app); // append instead of overwrite

  // for (size_t i = 0; i < sccs.size(); i++) {
  //   string line = "{";
  //   for (size_t j = 0; j < sccs.at(i).size(); j++) {
  //     line += sccs.at(i).at(j) + ", ";
  //   }
  //   if (line[line.length() - 1] != '{') {
  //     line.pop_back();
  //     line.pop_back();
  //   }
  //   line += "}";
  //   outfile << line << endl;
  // }

  // Brandes brandes;
  // map<string, int> mymap = brandes.calculate(graph);

  // cout << "finish calculating brandes" << endl;

  // vector<pair<string, int>> vec;
  // map<string, int> :: iterator it2;
  // for (it2=mymap.begin(); it2!=mymap.end(); it2++) 
  // {
  //   vec.push_back(make_pair(it2->first, it2->second));
  // }

  // sort(vec.begin(), vec.end(), sortByVal);

  // cout << "finish sorting" << endl;

  // std::ofstream outfile;

  // outfile.open("../tests/BrandesAlgorithm.txt", std::ios_base::app); // append instead of overwrite
  // for (size_t i = 0; i < vec.size(); i++)
  // {
  //   outfile << vec[i].first << ": " << vec[i].second << endl;
  // }

  // cout << vertices.size() << endl;
  // graph.printGraph();
  

  return 0;
}
