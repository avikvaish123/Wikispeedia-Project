#include "kosaraju.hpp"

using namespace std;

Kosaraju::Kosaraju() {

}

//converts our graph to a map of strings, which makes it easier for kosaraju's algorithm implementation
unordered_map<string, vector<string>> Kosaraju::convert(Graph g) {
    unordered_map<string, vector<string>> map;
    //traverse through all the vertices in the graph
    for (size_t i = 0; i < g.getVertices().size(); i++) {
        vector<string> temp_neighbors;
        string temp_name = g.getVertices().at(i)->article_;
        Graph::Node* current = g.getVertices().at(i)->next_;
        //traverse throught the linked list of neighbors, adding the names to the temp vector
        while (current != NULL) {
            temp_neighbors.push_back(current->article_);
            current = current->next_;
        }
        //insert the vector with the key of the head node article name
        map.insert_or_assign(temp_name, temp_neighbors);
    }
    //return map
    return map;
}

//computes which nodes finish first in a dfs and stores them on the stack
void Kosaraju::cft(const string& u, unordered_map<string, vector<string>> graph, unordered_map<string, bool>& visited, stack<string>& stack) {
    //mark the current node as visited
    visited[u] = true;
    //iterate through the neighbors fo the current node
    for (auto it = graph.at(u).begin(); it != graph.at(u).end(); ++it) {
        //if the neighbor hasn't been visited, recurse through it's adjacent vertices
        if (!visited[*it]) {
            cft(*it, graph, visited, stack);
        }
    }
    //push the original node to the stack once it's been processed
    stack.push(u);
}


void Kosaraju::dfs(const string& u, const unordered_map<string, vector<string>> graph, unordered_map<string, bool>& visited, vector<string>& scc) {
    visited[u] = true;
    scc.push_back(u);
    
    for (auto it = graph.at(u).begin(); it != graph.at(u).end(); ++it) {
        if (!visited[*it]) {
            dfs(*it, graph, visited, scc);
        }
    }
}

vector<vector<string>> Kosaraju::kosaraju(Graph graph, Graph transposed) {
    stack<string> stack;
    unordered_map<string, bool> visited;
    unordered_map<string, vector<string>> map = convert(graph);
    unordered_map<string, vector<string>> transposed_map = convert(transposed);

    cout << "Conversion Done" << endl;

    for (auto it = map.begin(); it != map.end(); ++it) {
        if(!visited[it->first]) {
            cft(it->first, map, visited, stack);
        }
        cout << "Finished CFT for: " << it->first << endl;
    }

    visited.clear();

    vector<vector<string>> sccs;

    while(!stack.empty()) {
        string temp = stack.top();
        stack.pop();
        if (!visited[temp]) {
            vector<string> scc;
            dfs(temp, transposed_map, visited, scc);
            sccs.push_back(scc);
            cout << "Finished DFS for: " << temp << endl;
        }
    }
    
    return sccs;
}
