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

  // Graph graph("../dataset/articles.tsv", "../dataset/links.tsv");

  // //initalize edges using adjacency list
  // graph.initialize_graph();
  // // graph.printGraph();

  // vector<Graph::Node*> vertices = graph.getVertices();

  // cout << vertices.size() << endl;

  // // Brandes brandes;
  // // map<string, int> mymap = brandes.calculate(graph);

  // map<string, int> mymap = {
	// 	{"coconut", 10}, {"apple", 5}, {"peach", 350}, {"mango", 8}
	// };

	// vector<pair<string, int>> vec;
  // map<string, int> :: iterator it2;
  // for (it2=mymap.begin(); it2!=mymap.end(); it2++) 
  // {
  //   vec.push_back(make_pair(it2->first, it2->second));
  // }

  // sort(vec.begin(), vec.end(), sortByVal);

  // std::ofstream outfile;

  // outfile.open("../tests/BrandesAlgorithm.txt", std::ios_base::app); // append instead of overwrite
  // for (size_t i = 0; i < vec.size(); i++)
	// {
	// 	outfile << vec[i].first << ": " << vec[i].second << endl;
	// }

  // Graph testGraph("../tests/kosa_vert.tsv", "../tests/kosa_edges.tsv");
  // Graph testGraphTrans("../tests/kosa_vert.tsv", "../tests/kosa_edges.tsv");

  Graph testGraph("../dataset/articles.tsv", "../dataset/links.tsv");
  Graph testGraphTrans("../dataset/articles.tsv", "../dataset/links.tsv");

  testGraph.initialize_graph();
  testGraphTrans.transpose_graph();


  Kosaraju k;
  vector<vector<string>> sccs = k.kosaraju(testGraph, testGraphTrans);


  for (size_t i = 0; i < sccs.size(); i++) {
    cout << "SCCS: {";
    for (size_t j = 0; j < sccs.at(i).size(); j++) {
      cout << sccs.at(i).at(j) << + ", ";
    }
    cout << "}" << endl;
  }

  return 0;
}
