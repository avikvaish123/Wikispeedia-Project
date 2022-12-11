#include <iostream>
#include <fstream>
#include <vector>

#include "graph.hpp"
#include "brandes.hpp"

using namespace std;

bool sortByVal(const pair<string, int> &a, 
               const pair<string, int> &b) 
{ 
    return (a.second > b.second); 
} 

int main()
{

  Graph graph("../dataset/articles.tsv", "../dataset/links.tsv");

  //initalize edges using adjacency list
  graph.initialize_graph();

  vector<Graph::Node*> vertices = graph.getVertices();

  // Brandes brandes;
  // map<string, int> mymap = brandes.calculate(graph);

  // map<string, int> mymap = {
	// 	{"coconut", 10}, {"apple", 5}, {"peach", 30}, {"mango", 8}
	// };

	// vector<pair<string, int>> vec;
  // map<string, int> :: iterator it2;
  // for (it2=mymap.begin(); it2!=mymap.end(); it2++) 
  // {
  //   vec.push_back(make_pair(it2->first, it2->second));
  // }

  // // sort(vec.begin(), vec.end(), sortByVal);

  // std::ofstream outfile;

  // outfile.open("BrandesAlgorithm.txt", std::ios_base::app); // append instead of overwrite
  // for (size_t i = 0; i < vec.size(); i++)
	// {
	// 	outfile << vec[i].first << ": " << vec[i].second << endl;
	// }

  Graph::Node* startingNode;
  Graph::Node* endingNode;
  for (size_t i = 0; i < vertices.size(); i++) {
    //Starting Node
    if (vertices.at(i)->article_ == "Achilles_tendon") {
      startingNode = vertices.at(i);
    }
    //Ending Node
    if (vertices.at(i)->article_ == "Donald_Duck") {
      endingNode = vertices.at(i);
    }
  }

  vector<string> path = graph.bfs(startingNode, endingNode);
  for (size_t i = 0; i < path.size(); i++) {
    cout << path.at(i);
    if (i < path.size() - 1) {
      cout << " -> ";
    }
  }
  cout << endl;
  cout << vertices.size() << endl;

  // graph.printGraph();

  return 0;
}
