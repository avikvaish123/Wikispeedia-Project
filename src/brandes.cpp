#include "brandes.hpp"

//constructor
Brandes::Brandes() {

}

//function to calculate the centrality scores of all the nodes
map<string, int> Brandes::calculate(Graph graph) {
    vector<Graph::Node*> vertices = graph.getVertices(); //vertices

    map<string, int> visited;
    if (vertices.size() == 0) {
        return visited;
    }
    
    for (size_t i = 0; i < vertices.size(); i++) {
        visited[vertices.at(i)->article_] = 0; //set the visited map to 0 to start counting
    }

    //traverse through the vertices
    for (size_t i = 0; i < vertices.size() - 1; i++) {
        //traverse through the vertices after the current node
        for (size_t j = 1 + i; j < vertices.size(); j++) {
            Graph::Node* starting = vertices.at(i); //set the starting node and ending node from i to j
            Graph::Node* ending = vertices.at(j);
            vector<string> shortest_path = graph.bfs(starting, ending); //find the shortest path from i to j using bfs
            //if there isn't a path, move onto the next node
            if (shortest_path.size() == 0) {
                continue;
            }

            //traverse through the middle nodes of the shortest path
            for (size_t k = 1; k < shortest_path.size() - 1; k++) {
                string current_article = shortest_path.at(k);
                //increase the count for each node that is on the shortest path
                visited[current_article] = visited[current_article] + 1;
            }
        }
    }
    //return the map
    return visited;
}