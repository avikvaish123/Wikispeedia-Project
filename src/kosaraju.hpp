#include "graph.hpp"

#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include <list>

using namespace std;

class Kosaraju {
public:

    Kosaraju();

    unordered_map<string, vector<string>> convert(Graph g);
    vector<vector<string>> kosaraju(Graph graph, Graph tranposed);
    void cft(const string& u, unordered_map<string, vector<string>> graph, unordered_map<string, bool>& visited, stack<string>& stack);
    void dfs(const string& u, const unordered_map<string, vector<string>> graph, unordered_map<string, bool>& visited, vector<string>& scc);

private:
};