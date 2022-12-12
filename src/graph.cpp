#include "graph.hpp"
#include <algorithm>

using namespace std;

// Simple constructor that stores the string paths to the fields
Graph::Graph(string path_of_vertices, string path_of_edges) {
    relative_path_of_vertices = path_of_vertices;
    relative_path_of_edges = path_of_edges;
}

// Computes the adjacency list and stores it in a vector "vertices"
void Graph::initialize_graph() {

    // Traverse the edges first (using ifstream for this)
    ifstream fstream(relative_path_of_edges);
    string line;
    string head_article = "";
    int index = 0;

    // While the file has a next line
    while (getline(fstream, line)) {
        // remove any '\r' at the end of the line to eliminate any formating issues in visual studios
        if (line[line.length() - 1] == '\r') {
            line.pop_back();
        }

        // since we are using 'tab seperated values'; find the index of the tab
        size_t vertex_index = line.find('\t');
        // grabs the vertex (article)
        string article = line.substr(0, vertex_index);
        // grabs the edge
        string edge = line.substr(vertex_index + 1);

        // if we are starting a new linked list
        if (head_article.empty()) {
            // create a new Node that holds the vertex
            head_article = article;
            Node *head = new Node();
            head->article_ = article;
            // create a new Node that holds the edge
            Node *first = new Node();
            first->article_ = edge;
            // point the vertex to the edge and the edge to NULL
            head->next_ = first;
            first->next_ = NULL;
            vertices.push_back(head);
            // continue to the next line
            continue;
        }
        
        // if the vertex we are on has a vertex
        if (head_article == article) {
            // call the helper function to add it to end of the link-list
            push_back(vertices.at(index), edge);
        }
        else { // if the new article has changed and doesn't have a vertex
            // create a new Node that holds the vertex
            head_article = article;
            Node *head = new Node();
            head->article_ = article;
            // create a new Node that holds the edge
            Node *first = new Node();
            first->article_ = edge;
            // point the vertex to the edge and the edge to NULL
            head->next_ = first;
            first->next_ = NULL;
            vertices.push_back(head);
            index++;
        }
    }

    // We have to traverse through the vertex tsv file
    // We found that if a vertex has no edges, it would excluded from the edges tsv file
    // This meant that we were 17 nodes short due to this reasoning
    // To account for this we traverse through the vertex file
    // And add it to 'vertices' with no edges
    ifstream fstre(relative_path_of_vertices);
    string line2;
    
    //While the vertex file has a next line
    while (getline(fstre, line2)) {
        // remove any '\r' at the end of the line to eliminate any formating issues in visual studios
        if (line2[line2.length() - 1] == '\r') {
            line2.pop_back();
        }

        // Trys to find the vertex in 'vertices'
        bool found = false;
        for (size_t i = 0; i < vertices.size(); i++) {
            if (line2 == vertices.at(i)->article_) {
                found = true;
                break;
            }
        }

        // If we did not find the vertex, then add it to 'vertices' with no edges
        if (!found) {
            Node *head = new Node();
            head->article_ = line2;
            head->next_ = NULL;
            vertices.push_back(head);
        }
    }

    // close the files at the end
    fstre.close();
    fstream.close();
}

// Computues the transpose of the graph and stores it in "vertices"
// This function is the exact same as the "initalize_graph()"
// The only thing we changed was swap the vertex and edges
void Graph::transpose_graph() {

    ifstream fstream(relative_path_of_edges);
    string line;
    string head_article = "";
    int index = 0;

    while (getline(fstream, line)) {

        if (line[line.length() - 1] == '\r') {
            line.pop_back();
        }

        size_t vertex_index = line.find('\t');
        // The only change we made: swap the vertex with the edge to tranpose the graph
        string edge = line.substr(0, vertex_index);
        string article = line.substr(vertex_index + 1);

        if (head_article.empty()) {
            head_article = article;
            Node *head = new Node();
            head->article_ = article;
            Node *first = new Node();
            first->article_ = edge;
            head->next_ = first;
            first->next_ = NULL;
            vertices.push_back(head);
            continue;
        }

        if (head_article == article) {
            push_back(vertices.at(index), edge);
        } else {
            head_article = article;
            Node *head = new Node();
            head->article_ = article;
            Node *first = new Node();
            first->article_ = edge;
            head->next_ = first;
            first->next_ = NULL;
            vertices.push_back(head);
            index++;
        }
    }

    ifstream fstre(relative_path_of_vertices);
    string line2;
    while (getline(fstre, line2)) {
        if (line2[line2.length() - 1] == '\r') {
            line2.pop_back();
        }

        bool found = false;
        for (size_t i = 0; i < vertices.size(); i++) {
            if (line2 == vertices.at(i)->article_) {
                found = true;
                break;
            }
        }

        if (!found) {
            Node *head = new Node();
            head->article_ = line2;
            head->next_ = NULL;
            vertices.push_back(head);
        }
    }

    fstre.close();
    fstream.close();
}

// Performs a breadth-first search on two nodes
// Returns a vector that stores the path between the Nodes
// E.g. {Node2, Node5, Node3} <- Would be the shortest path between Node2 and Node3
vector<string> Graph::bfs(Node* startingNode, Node* endingNode) {

    // Create a queue that holds all the neighbors
    // Push the starting node to the queue
    queue<Node*> queue;
    queue.push(startingNode);

    // Create a map that stores a string (article) to a boolean to see if it has been visited
    // Assign the starting vertex to have already been visited
    map<string, bool> visited;
    for (size_t i = 0; i < vertices.size(); i++) {
        visited[vertices.at(i)->article_] = false;
    }
    visited.insert_or_assign(startingNode->article_, true);

    // Create a map that stores a vertex to the previous vertex that is was linked to
    // This will be helpful when we construct the path back to the starting vertex
    map<string, string> previous;
    for (size_t i = 0; i < vertices.size(); i++) {
        previous[vertices.at(i)->article_] = "";
    }

    // While the queue is not empty
    while (!queue.empty()) {
        // Graph the Node at the front of the queue and pop it
        Node* current = queue.front();
        queue.pop();

        // All the neighbors start at the next node, not the head (vertex) node
        Node* neighbor = current->next_;

        // Traverse through all the neighbors
        while (neighbor != NULL) { 
            // If the current neighbor has NOT been visited
            if (!visited.at(neighbor->article_)) {
                // Push the current neighbor to the queue
                // You can't just push neighbor on the queue 
                // because that means the next nodes would continue 
                // to be the neighbors of 'curent' and not itself
                queue.push(getEdges(neighbor->article_));
                // Reassign the current neighbor to be visited (true)
                visited.insert_or_assign(neighbor->article_, true);
                // Reassign the current neighbor to hold the article of 'current'
                // Since it came from the 'current' node
                previous.insert_or_assign(neighbor->article_, current->article_);
            }
            // Updated neighbor to the next node
            neighbor = neighbor->next_;
        }
    }

    // Calculated the path and stores it in the vector 'path'
    // start and the endingNode
    vector<string> path;
    string current = endingNode->article_;

    // While the current node holds a vertex
    while (!current.empty()) {
        // Push the vertex onto the path
        path.push_back(current);
        // Update current to point to the previous node in the path
        current = previous.at(current);
    }
    // Since we started at the ending vertex, we have to reverse the vector
    // That way index 0 is the starting vertex
    std::reverse(path.begin(), path.end());

    // If index 0 holds the start vertex, that means there IS a path between the two nodes
    if (path.at(0) == startingNode->article_) {
        return path;
    }
    // If it doesn't, that means there is NO path between the two nodes
    // Clear the vector and return the path
    path.clear();
    return path;
}

// Helper function that gets the edges "neighbors" of a vertex (article)
Graph::Node* Graph::getEdges(string article) {
    // Tranverse through 'vertices' and searches for article
    for (size_t i = 0; i < vertices.size(); i++) {
        if (vertices.at(i)->article_ == article) {
            // if it finds it, return that vertex
            return vertices.at(i);
        }
    }
    // if it doesn't find it, return an empty node
    Node* temp = new Node();
    return temp;
}

// Accessor function that returns the adjacency list
vector<Graph::Node *> Graph::getVertices() {
    return vertices;
}

// Helper function that prints the adjacency list to the terminal
// Used for testing as well as debugging any issues in our algorithms
void Graph::printGraph() {
    // Traverse through all of the vertices and print the graph in a neat format
    for (size_t i = 0; i < vertices.size(); i++) {
        string output = "Head: ";
        output += vertices.at(i)->article_ + " - [";
        Node *temp = vertices.at(i)->next_;
        while (temp != NULL) {
            output += temp->article_ + ",";
            temp = temp->next_;
        }
        // checks if the node has edges
        if (output[output.length() - 1] != '[') {
            output.pop_back();
        }
        output += "]";
        cout << output << endl;
    }
}

// Helper function that adds an article to the end of the linked list
void Graph::push_back(Node *head, string article)
{
    // creates a temp node to add to the end of the list
    Node *temp = new Node();
    temp->article_ = article;
    temp->next_ = NULL;

    // traverse the all of the edges
    Node *current = head;
    while (current->next_ != NULL) {
        current = current->next_;
    }
    // adds the node to the end of the link-list
    current->next_ = temp;
}


