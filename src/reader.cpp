#include "reader.hpp"

Reader::Reader(string path) {
    relative_path = path;
}

void Reader::initialize_vertices() {
    ifstream fstream(relative_path);
    string line;
    int lineNumber = 0;
    while (getline(fstream, line)) {\
        lineNumber++;
        if (lineNumber < 13) {
            continue;
        }
        vertices.push_back(line);
    }
    fstream.close();
}

void Reader::initialize_edges_2D() {

}

void Reader::initialize_edges_list() {
    
}

vector<string> Reader::getVertices() {
    return vertices;
}