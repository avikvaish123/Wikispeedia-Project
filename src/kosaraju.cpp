#include "kosaraju.hpp"

using namespace std;

Kosaraju::Kosaraju() {

}

void Kosaraju::cft(const string& u, const vector<Graph::Node*> vertices, unordered_map<string, bool>& visited, stack<string> stack) {
    visited[u] = true;
    for (size_t i = 0; i < vertices.size(); i++) {
        if (vertices.at(i)->article_ == u && !visited[vertices.at(i)->next_->article_]) {
            cft(vertices.at(i)->next_->article_, vertices, visited, stack);
        }
    }
    stack.push(u);
}

Graph Kosaraju::transpose(Graph g) {
    //traverse through all the vertices
    Graph ret("","");
    vector<Graph::Node*> vertices = g.getVertices();
    for (size_t i = 0; i < vertices.size(); i++) {
        Graph::Node* temp = new Graph::Node();
        string name = vertices.at(i)->article_;
        temp->article_ = name;
        for (size_t j = 0; j < vertices.size(); j++) {
            if (i == j) { continue; }
            Graph::Node* current = vertices.at(j)->next_;
            while (current != NULL) {
                if (current->article_ == name) {
                    ret.push_back(temp, vertices.at(j)->article_);
                }
            }
        }
        ret.getVertices().push_back(temp);
    }
    return ret;
}

void Kosaraju::dfs(const string& u, const vector<Graph::Node*> vertices, unordered_map<string, bool>& visited, vector<string> scc) {
    visited[u] = true;
    scc.push_back(u);
    for (size_t i = 0; i < vertices.size(); i++) {
        if (vertices.at(i)->article_ == u && !visited[vertices.at(i)->next_->article_]) {
            dfs(vertices.at(i)->next_->article_, vertices, visited, scc);
        }
    }
}

vector<vector<string>> Kosaraju::kosaraju(Graph g) {
    stack<string> stack;
    unordered_map<string, bool> visited;
    cout << "REACHED " << __LINE__ << endl;
    vector<Graph::Node*> vertices = g.getVertices();
    for (size_t i = 0; i < vertices.size(); i++) {
        if (!visited[vertices.at(i)->article_]) {
            cft(vertices.at(i)->article_, vertices, visited, stack);
        }
    }
    cout << "REACHED " << __LINE__ << endl;
    Graph reverse = transpose(g);
    cout << "REACHED " << __LINE__ << endl;
    visited.clear();
    vector<vector<string>> sccs;
    cout << "REACHED " << __LINE__ << endl;
    while(!stack.empty()) {
        string i = stack.top();
        stack.pop();
        if (!visited[i]) {
            vector<string> scc;
            dfs(i, reverse.getVertices(), visited, scc);
            sccs.push_back(scc);
            cout << "REACHED " << __LINE__ << endl;
        }
    }
    cout << "REACHED " << __LINE__ << endl;
    return sccs;
}
