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

  Graph testGraph("../tests/medium_vert.tsv", "../tests/medium_links.tsv");
  Graph testGraphTrans("../tests/medium_vert.tsv", "../tests/medium_links.tsv");

  testGraph.initialize_graph();
  testGraphTrans.transpose_graph();

  Kosaraju k;
  vector<vector<string>> sccs = k.kosaraju(testGraph, testGraphTrans);

  std::ofstream outfile;

  outfile.open("../tests/Kosaraju.txt", std::ios_base::app); // append instead of overwrite

  for (size_t i = 0; i < sccs.size(); i++) {
    string line = "{";
    for (size_t j = 0; j < sccs.at(i).size(); j++) {
      line += sccs.at(i).at(j) + ", ";
    }
    if (line[line.length() - 1] != '{') {
      line.pop_back();
      line.pop_back();
    }
    line += "}";
    outfile << line << endl;
  }

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
