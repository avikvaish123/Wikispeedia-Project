#include "graph.hpp"

#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include <list>

using namespace std;

class Kosaraju {
public:
    //constructor
    Kosaraju();

    //main kosaraju's function that performs a dfs, reverse the graph, and then performs another dfs to return the strongly connected components
    //Input: Graph object and tronspose of the graph object
    //Output: Vector of the strongly connected components
    vector<vector<string>> kosaraju(Graph graph, Graph tranposed);

private:
    //converts our graph structure into a map of vectors so it's easier to traverse through for kosaraju's algorithm
    unordered_map<string, vector<string>> convert(Graph g);
    //Computes the finishing order for nodes that are traverse using dfs
    //puts the nodes on a stack in terms of which dfs finishes first
    void cft(const string& u, unordered_map<string, vector<string>> graph, unordered_map<string, bool>& visited, stack<string>& stack);
    //runs dfs on the nodes in the stack and adds the traversed nodes to the strongly connected components
    void dfs(const string& u, const unordered_map<string, vector<string>> graph, unordered_map<string, bool>& visited, vector<string>& scc);
};