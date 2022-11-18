#include <iostream>

#include "graph.hpp"

using namespace std;

int main()
{

  Graph graph("dataset/articles.tsv", "dataset/links.tsv");

  //initalize edges using adjacency list
  graph.initialize_graph();

  vector<Graph::Node*> vertices = graph.getVertices();
  Graph::Node* startingNode;
  Graph::Node* endingNode;

  for (size_t i = 0; i < vertices.size(); i++) {
    //Starting Node
    if (vertices.at(i)->article_ == "14th_century") {
      startingNode = vertices.at(i);
    }
    //Ending Node
    if (vertices.at(i)->article_ == "John_F._Kennedy") {
      endingNode = vertices.at(i);
    }
  }

  vector<string> path = graph.bfs(startingNode, endingNode);
  for (size_t i = 0; i < path.size(); i++) {
    cout << path.at(i) << " -> ";
  }
  cout << endl;

  //graph.printGraph();

  return 0;
}
