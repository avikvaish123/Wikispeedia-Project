#include "graph.hpp"

#include <vector>
#include <string>

using namespace std;

class Brandes {
public:
    
    //constructor
    Brandes();

    //calculates the centrality score of all the nodes in the graph and stores it in the map
    map<string, int> calculate(Graph graph);

private:
};