# Campus Graph (Rylan Smith - Member B)

The campus graph represents the buildings on campus and each connection between them. Every building is a vertex, and each connection is an edge.

An adjacency list is used to store connections. One vector stores the building names, and another stores the connected buildings using their indexes. Since each connection is undirected, they are added to each other’s adjacency lists.

The graph loads buildings and connections from buildings.txt and connections.txt. Invalid entries, duplicate buildings, and duplicate connections are also checked.

Each building and connection is displayed with the graph. The total number of buildings, total connections, and the degree of each building are also displayed.

A breadth-first search (BFS) is implemented to find which buildings can be reached from a starting building. A queue is used to visit connected buildings and track visited buildings and distances from the starting point.

# Facility Hash Table

The facilities and hash table are implemented in 3 separate classes, each representing an individual level of the hierarchy of functionality: FacilityTable, FacilityChain, and Facility.

## FacilityTable

This is the parent class that is itself the actual has table. The chains are stored in a vector so the size can be dynamic and resizing could be supported if need be. The functionality of loading the Facilities file, creating, storing, deleting, hashing, finding, and managing the table is all implemented here. The choice to abstract the other stages means that the inner workings of the buckets is arbitrary and the table is not manipulating the individual faciltiies itself. This is very useful for expanding the functionality and compartmentalizing errors. 

I'm choosing an initialization size of 50 because I want to anticipate large test sizes and keep speed high. The linked lists are very efficient to store, especially when empty, so I'm not that worried about taking up space.

## FacilityChain

This is the class that represents the individual buckets. I decided to implement these using Separate Chaining and so FacilityChain is implemented as a linked list. This is a strategic choice because it keeps table operations very quick as long as a large enough bucket value is chose relative to the number of facilities stored, but it will never completely fill up. This is useful, because the number of facilities will always be known at runtime (they are loaded from a static file, rather than input during the program's operation), so the number of chains can be tuned to get optimal performance.

### Collisions

I'm defining a **collision** to mean anytime a linked list is appended to when it already has 1 or more elements. This is logically the same as anytime multiple facilities are hashed to the same value. Because I'm using separate chaining, the collision resolution strategy is just to append to the chain when inserting into the list and linear search through the chain to retrieve from a bucket with collisions. This does mean that, as chains grow, both insertion and retrieval operations become polynomial time. When inserting, we have to check for duplicates in the bucket, and when retrieving, we have to search the bucket. 

## Facility 

This is the baseline unit that represents the actual Facility records being stored and contains the information about the Facilities. However, it is also a Linked List node and so contains a *next*.