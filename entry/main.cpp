#include <iostream>

#include "graph.hpp"

using namespace std;

int main()
{

  Graph graph("dataset/articles.tsv", "dataset/links.tsv");

  //initalize edges using adjacency list
  graph.initialize_graph();

  graph.printGraph();
  cout << graph.getVertices().size() << endl;

  return 0;
}
