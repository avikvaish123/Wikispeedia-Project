#include "graph.hpp"

#include <vector>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

class Kosaraju {
public:
    
    Kosaraju();

    vector<vector<string>> kosaraju(Graph g);
    void cft(const string& u, const vector<Graph::Node*> vertices, unordered_map<string, bool>& visited, stack<string> stack);
    Graph transpose(Graph g);
    void dfs(const string& u, const vector<Graph::Node*> vertices, unordered_map<string, bool>& visited, vector<string> scc);

private:
};