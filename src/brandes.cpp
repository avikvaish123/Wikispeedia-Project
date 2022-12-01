#include "brandes.hpp"

Brandes::Brandes() {

}

string Brandes::calculate(Graph graph) {
    vector<Graph::Node*> vertices = graph.getVertices();

    map<string, int> visited;
    for (size_t i = 0; i < vertices.size(); i++) {
        visited[vertices.at(i)->article_] = 0;
    }

    for (size_t i = 0; i < vertices.size() - 1; i++) {
        for (size_t j = 1; j < vertices.size(); j++) {
            Graph::Node* starting = vertices.at(i);
            Graph::Node* ending = vertices.at(j);
            cout << "Test: " << starting->article_ << " -> " << ending->article_ << endl;
            vector<string> shortest_path = graph.bfs(starting, ending);
            if (shortest_path.size() == 0) {
                continue;
            }
            for (size_t k = 1; k < shortest_path.size() - 1; k++) {
                string current_article = shortest_path.at(k);
                visited[current_article] = visited[current_article] + 1;
                cout << "\t" << current_article << " " << visited[current_article] << endl;
            }
        }
    }
    return "working";
}