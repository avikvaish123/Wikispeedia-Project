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
    int line_number = 0;
    string head_article = "";
    int index = 0;
    while (getline(fstream, line)) {
        line_number++;
        if (line_number < 13) {
            continue;
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
    line_number = 0;
    while (getline(fstre, line2)) {
        line_number++;
        if (line_number < 13) {
            continue;
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

Graph Graph::transpose() {
    Graph ret;
    for (size_t i = 0; i < this->vertices.size(); i++) {
        //create a temp node with the vertex name
        Node *temp = new Node();
        temp->article_ = this->vertices.at(i)->article_;
        //traverse through the rest of the vertices
        for (size_t j = 0; j < this->vertices.size(); j++) {
            if (i == j) {
                continue;
            }
            //traverse through the neighbors of the other vertices
            Node* current = this->vertices.at(j)->next_;
            while (current != NULL) {
                //if the temp node is a neighbor of one of the vertices
                //add the vertex to the neighbors of the temp node
                if (current->article_ == temp->article_) {
                    push_back(temp, current->article_);
                    break;
                }
            }
        }
        //after adding all the neighbors, repeat for every vertex in the graph
        ret.vertices.push_back(temp);
    }
    return ret;
}

void Graph::dfs(Node* start, vector<bool>& visited) {
    visited[]
}

