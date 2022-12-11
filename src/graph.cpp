#include "graph.hpp"
#include <algorithm>

using namespace std;

Graph::Graph(string path_of_vertices, string path_of_edges) {
    relative_path_of_vertices = path_of_vertices;
    relative_path_of_edges = path_of_edges;
}

void Graph::initialize_graph() {
    ifstream fstream(relative_path_of_edges);
    string line;
    string head_article = "";
    int index = 0;
    while (getline(fstream, line)) {
        if (line[line.length() - 1] == '\r') {
            line.pop_back();
        }
        size_t vertex_index = line.find('\t');

        string article = line.substr(0, vertex_index);
        string edge = line.substr(vertex_index + 1);

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
        }
        else {
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
        }
        else {
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

vector<string> Graph::bfs(Node* startingNode, Node* endingNode) {
    queue<Node*> queue;
    queue.push(startingNode);

    map<string, bool> visited;
    for (size_t i = 0; i < vertices.size(); i++) {
        visited[vertices.at(i)->article_] = false;
    }
    visited.insert_or_assign(startingNode->article_, true);

    map<string, string> previous;
    for (size_t i = 0; i < vertices.size(); i++) {
        previous[vertices.at(i)->article_] = "";
    }

    while (!queue.empty()) {
        Node* current = queue.front();
        queue.pop();
        Node* neighbor = current->next_;

        while (neighbor != NULL) {

            if (!visited.at(neighbor->article_)) {
                queue.push(getEdges(neighbor->article_));
                visited.insert_or_assign(neighbor->article_, true);
                previous.insert_or_assign(neighbor->article_, current->article_);
            }
            neighbor = neighbor->next_;
        }
    }

    vector<string> path;
    string current = endingNode->article_;
    while (!current.empty()) {
        path.push_back(current);
        current = previous.at(current);
    }
    std::reverse(path.begin(), path.end());
    if (path.at(0) == startingNode->article_) {
        return path;
    }
    path.clear();
    return path;
}

Graph::Node* Graph::getEdges(string article) {
    for (size_t i = 0; i < vertices.size(); i++) {
        if (vertices.at(i)->article_ == article) {
            return vertices.at(i);
        }
    }
    Node* temp = new Node();
    return temp;
}

vector<Graph::Node *> Graph::getVertices()
{
    return vertices;
}

void Graph::printGraph() {
    for (size_t i = 0; i < vertices.size(); i++) {
        string output = "Head: ";
        output += vertices.at(i)->article_ + " - [";
        Node *temp = vertices.at(i)->next_;
        while (temp != NULL) {
            output += temp->article_ + ",";
            temp = temp->next_;
        }
        if (output[output.length() - 1] != '[') {
            output.pop_back();
        }
        output += "]";
        cout << output << endl;
    }
}

void Graph::push_back(Node *head, string article)
{
    Node *temp = new Node();
    temp->article_ = article;
    temp->next_ = NULL;

    Node *current = head;
    while (current->next_ != NULL) {
        current = current->next_;
    }
    current->next_ = temp;
}


