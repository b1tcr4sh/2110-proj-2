# Campus Graph (Rylan Smith - Member B)

The campus graph represents the buildings on campus and each connection between them. Every building is a vertex, and each connection is an edge.

An adjacency list is used to store connections. One vector stores the building names, and another stores the connected buildings using their indexes. Since each connection is undirected, they are added to each other’s adjacency lists.

The graph loads buildings and connections from buildings.txt and connections.txt. Invalid entries, duplicate buildings, and duplicate connections are also checked.

Each building and connection is displayed with the graph. The total number of buildings, total connections, and the degree of each building are also displayed.

A breadth-first search (BFS) is implemented to find which buildings can be reached from a starting building. A queue is used to visit connected buildings and track visited buildings and distances from the starting point.