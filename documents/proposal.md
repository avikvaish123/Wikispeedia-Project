## Leading Question 
Our project goal is to create a program that allows a user to select "start" and "finish" articles on Wikipedia, and then returns the shortest path from the start to finish, using linkes on each page as the possible paths. We will accomplish this with the "wikispeedia" dataset from the Stanford Large Network Dataset Collection. To find the shortest path, we will create a graph where the starting page is the root node, and the directed edges are the links between pages. The shortest path will be found via Djikstra's Algorithm. We will also be able to do some basic math on the dataset: most distant pages (longest shortest path) as well as provide "best next moves" to players playing the game.
## Dataset Acquisition
## Data Format
Our input dataset is the "wikispeedia" dataset from Stanford. We will be using the "links" text document, which is in the format of a list of parent-child pairs. Each parent is listed in alphabetical order, so we should be able to load the nodes into the dataset in alphabetical order. Each node will have all of its connected nodes loaded, with directed edges. We plan to use the entire dataset, which is 4,604 nodes and 119,882 directed edges.
## Data Correction
We must verify that the graph has only 1 connected component, otherwise not all pages are linkable. If not, we may have to add our own data to form bidirectional paths between disconnected components. We can also perform string checks to make sure that there are no typos or duplicated pages in the dataset.
## Data Storage
We plan to store our data in a directed graph, with each Wikipedia page as a node and each link as a directed edge. Since our input dataset has size N, this would be O(N) storage.
## Algorithm
To answer the leading question, which is what is the shortest path between a start wikipedia page and an end wikipedia page is, we will be using Djikstra's algorithm. The input of this algorithm will be the start and end node in the graph. For that, there is no conversion, as the function will take in Nodes and these nodes will have all the information that is required to traverse. All of our nodes will be stored in a vector or similar data structure that we will convert upon reading the data. The output of this function will be the path of nodes in the form of a string of the different webpages, as well as the length or number of clicks in the form of an integer. The run time of this is O($V^2$).

We will also need to implement BFS and DFS ot traverse the graph. For BFS, we will just be looking at neighbors, so the function will take a single Node as the input and return a vector of the neighbors of the directed graph, so only webpages that you can access from the input node. The run time of this function O{degree V}.For DFS, we would take in one Node for the input and a number of clicks, and the output will be a vector of all the different webpages n clicks away from the input node. The run time for this function is O(V+E).

The other data algorithm we will implement is Eulerian Path/Cycle Indentification, which will help us find cycles in the wikispeedia game. The input of this algorithm will be 1 input Node, and the output will be a vector where the size of the vector is the number of cycles, and the data value at each index in the vector is the number of nodes in that corresponding cycle. The runtime for this function is O($E^2$).


## Timeline
With a due date of December 8th, there is a lot that needs to get done in roughly under a month.

- Starting with Data Collection and Processing, being able to have good clean data that we can understand and work with is important. Having our data set ready to work with and in our github repository should be done by $\textbf{Nov 10}$. 

- Getting all the graphing algorithms done will take a while. For our traversal algorithm, we want to use both BFS and DFS since our project can make use of both. The good thing about these algorithms are that we learned them in class so they shouldn't take us that long. Ideally, these algorithms should be coded up by $\textbf{Nov 11}$. We can start building these algorithms immediately and then adjust them according to our data.

- The other two more complex algorithms will take some time to develop, but since there is a lot of documentation online, we should be in good hands. These algorithms should be developed by $\textbf{Nov 15}$.

- The next step is developing test cases for each of our algorithms. As soon as we finish an algorithm, we should be testing it, but developing good test plans and cases does take some time, so we will allow a week after each algorithm is done. Ideally, the BFS and DFS test cases should be written out by $\textbf{Nov 18}$ and also tested by then. The other test cases should be finished by $\textbf{Nov 22}$.

- While this next goal might be ambitious, the all of the algorithms should be tested and tuned and fully functioning by the end of Fall Break, which is $\textbf{Nov 28}$. If we can get all of the meat of the code done by this time, we will be set up well for the rest of the project. 

- After the algorithms are written, we need to write UI and other peripheral functions, as well as a proper make file to make compiling easy. These added features should be done and perfected by $\textbf{Dec 4}$. A final run through of the code should be done by $\textbf{Dec 5}$ which is when all coding should stop. At this point, all of the technical work for the project should be done.

- The rest of the project, which includes the written report and the presentation, will be completed in the next couple of days and be done by the final submission day of $\textbf{Dec 8}$
