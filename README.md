# CS225FinalProject

## Original Data Source

Wikispeedia from Stanford: http://snap.stanford.edu/data/wikispeedia.html

## To run the code in VSCode:

1. Go to the parent directory
2. Type "mkdir build"
3. Type "cd build"
4. Type "cmake .."
5. Type "make"
6. Type "./main"
7. To run tests, type "./test"
  
## After running:

1. You will be prompted to enter the file names for edges and vertices
    - We are assuming that the datasets and files you enter are correct and in tsv form
2. Next, you will be prompted on which function you want to run
    - BFS to find the shortest path between two nodes
    - Brandes's to find the centrality score of a node
    - Kosaraju's to find which other nodes are a part of the same strongly connected component
3. Once you enter the function and the necessary inputs, you will receive your result

One thing that you need to keep in mind is for Brandes's and Kosaraju's algorithm, the dataset has to be relatively small.
On graphs with over 500 nodes, the algorithm will take too long and the program will stall, so we recommend that if you want
to run those algorithms, do it on small graphs. BFS will work on large graphs because of the faster run time.

### Organization
- dataset - this folder includes all of the data from the Stanford website
- entry - holds main.cpp for testing and to run ./main
- src - contains our graph and all algorithms that we implemented (graph, brandes, kosaraju)
- tests - all of our test cases as well as our smaller tsv files used for the small/medium cases

### Full Dataset
- Edges: `../dataset/links.tsv`
- Vertices: `../dataset/articles.tsv`

### Small Dataset
- Edges: `../tests/medium_links.tsv`
- Vertices: `../tests/medium_vert.tsv`