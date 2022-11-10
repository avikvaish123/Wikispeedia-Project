#include <iostream>

#include "reader.hpp"

using namespace std;

int main() {

  //initalize the reader class using the relative path
  Reader reader("dataset/articles.tsv");

  //initalize the verticles
  reader.initialize_vertices();

  //initalize edges using a adjacency matrix
  reader.initialize_edges_2D();

  //initalize edges using adjacency list
  reader.initialize_edges_list();


  //testing purposes: you can see the size and the vertices
  vector<string> nodes = reader.getVertices();
  // for (string s : nodes) {
  //   cout << s << endl;
  // }
  cout << nodes.size() << endl;

  return 0; 
}
