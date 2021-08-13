# CS225 Data Structures

## Final Project Project Proposal 

1. **Leading question** What is the optimal flight path between two coordinates? What's the most popular airport in the world?

Where is the closest airport to the start/end position, and what is the shortest path between two airports? With our final project, we hope to solve the problem of finding the nearest airport to a current airport, using the airport database. A successful project for us would be able to find an ideal path between two airports according to the least distance. 

2. **Dataset Acquisition and Processing** We will be using the datasets airports.dat and routes.dat from OpenFlights for our project. We will read the .dat/.csv file and use line parsing to get our data to store out data in vectors, before inserting the data into our graphs. Our data is comma-separated, so we will create a stream of strings that we will filter through to get the data we need, iterating through each line. If our dataset is broken/missing lines, we will simply iterate over them.

3. **Graph Algorithms**  

Directed Graph: Contains all airports and connections for routes. Will use BFS (traversal) to find airports within graph. Use Dijkstra's Algorithm and A* Search to get optimal path between origin and destination airports, and have the distance as the route weights.

Runtime analysis: 
  BFS traversal will take O(n) time, considering it is a standard traversal and will need to visit each node in the tree.
  
  Dijkstra's algorithm takes O(|E| + |V|log(|V|)) time, where V is the set of all vertices in a graph.
  
  For A* Search the runtime would be roughly O(|E| + |V|log(|V|)) time, where V is the set of all vertices in a graph, which is the same as Dijkstra's algorithm. 

4. **Timeline**

  April 14 - Finish Design on Project

  April 20 - Latest Date for Parsing and Loading of Data to be completed 

  April 27 - Betweenness Centrality and Directed Graph algorithms completed and written, includes the 2 graph data structures as well as the traversal
  
  April 30 - Integrate all functions/algos into a module that takes user input
  
  May 5 - Begin making test cases
  
  May 10 - Finish Slides, Record Video
