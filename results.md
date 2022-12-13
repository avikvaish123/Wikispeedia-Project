# CS 225 Project Results

## Goals and Leading Question - BFS

When beginning this project, we set our goal to be to create a program that would allow a user to select a "start" and "finish" article from the wikispeedia dataset, and return the shortest path from start to finish using links on the page as the possible paths. We used Breadth-First-Search (BFS) to answer this question, with our algorithm outputting a vector that contains all the articles needed to traverse from start to finish, in order. So that the user only has to interact with the terminal, we have printed this vector out. For example, if you requested the shortest path between `Pakistan` and `Nikola_Tesla`, the program will print:

`Pakistan -> Age_of_Enlightenment -> Physics -> Nikola_Tesla`

In order to verify that our algorithm worked correctly, we created smaller, known graphs and then performed a BFS on each node. We verified the algorithm's performance through various test cases, and have confirmed that it outputs the correct shortest path.

A major difficulty we faced with the BFS algorithm is that we are unable to directly verify performance on the full dataset due to the large number of nodes and edges (4604 and 119882 respectively), but for very simple cases (0 or 1 articles in between start and finish) we manually verified the algorithm returns a path with minimum length. Since the articles have many links, there may be multiple paths with the same length, but these are all considered "shortest paths".

## Brandes's Algorithm

We used Brandes's Algorithm to calculate the betweenness centrality of different nodes in our dataset. "Betweenness centrality" is calculated by performing an all-pairs shortest path (BFS from each node to each other node) and then summing the number of paths that cross through a node. Our implementation creates a map with strings as keys and ints as values. The key is the article title, and the value is the centrality score. In the UI we give to the user, we have them request the centrality score for a single node, and then return the value associated with that key. For example, if the user requested the centrality score of `Africa` on our modified dataset, the program will print:

`Centrality score: 9372`

In order to verify this algorithm, we created smaller known graphs and manually computed the centrality score for each node in the graph. We then compared the algorithm's values with our manually computed values to ensure they were identical. We also tested to make sure that empty graphs and graphs with no edges would work.

The main challenge we faced with Brandes's algorithm is the runtime due to our large dataset. The runtime of Brandes's on a directed, unweighted graph is O(VE), and since we have 4604 nodes and 119882 edges, the runtime became a huge problem. We solved this by simplifying our dataset down to 361 nodes and 923 edges. On this simplified dataset, computing the centrality score of a node takes 1-2 minutes, instead of hours.

## Kosaraju's Algorithm

We used Kosaraju's Algorithm to find the strongly connected components of our dataset. A strongly connected component means that every node in the component is accessible from every other node in the component. This is useful for us because if nodes are not accessible from each other, we cannot generate a BFS path. Our implementation of Kosaraju's ... For example, if the user requested the strongly connected component that contains `Argentina` on our modified dataset, the program will print:

`Andes, Armadillo, Argentina`