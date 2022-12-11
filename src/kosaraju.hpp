#include "graph.hpp"

#include <vector>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;
using namespace Graph;

class Kosaraju {
public:
    
    Kosaraju();

    vector<vector<string>> kosaraju(Graph g);
    void compute_finishing_times(const string& u, const vector<Graph::Node*> vertices, unordered_map<string, bool>& visited, stack<Graph::Node*> stack);
    Graph transpose(Graph g);
    void dfs(const string& u, const vector<Graph::Node*> vertices, unordered_map<string, bool>& visited, vector<string> scc);

private:
};