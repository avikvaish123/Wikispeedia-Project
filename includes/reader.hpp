#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Reader {
    public:
        Reader(string path);

        void initialize_vertices();
        void initialize_edges_2D();
        void initialize_edges_list();
        
        vector<string> getVertices();
    private:
        string relative_path;
        vector<string> vertices;
};