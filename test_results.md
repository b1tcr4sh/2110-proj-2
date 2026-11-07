# Test Results – Rylan Smith - Member B

### Compilation

* Compiled the program using Visual Studio C++.
* Program compiled successfully with no errors.
* **Result: Passed**

### Loading Buildings

* Loaded buildings from `data/buildings.txt`.
* 7 buildings loaded and 0 rejected.
* **Result: Passed**

### Loading Connections

* Loaded connections from `data/connections.txt`.
* 6 connections loaded and 0 rejected.
* **Result: Passed**

### Graph Display

* Checked that all buildings displayed their connections correctly.
* Verified that Observatory displayed "(no connections)" because it has no connections.
* **Result: Passed**

### Graph Statistics

* Checked the total number of buildings and connections.
* Verified the degree of each building.
* Program displayed 7 buildings and 6 connections.
* All building degrees matched the expected results.
* **Result: Passed**

### BFS

* Ran BFS starting at Library.
* Checked that buildings displayed in the correct order and had the correct distances.
* Program showed 6 out of 7 buildings were reachable.
* **Result: Passed**

### Case-Insensitive Search

* Tested BFS using "library" instead of "Library".
* Program still found the correct building and displayed the same results.
* **Result: Passed**

### Invalid Connections

* Tested self-connections, connections to buildings that don't exist, missing building names, and duplicate connections.
* Program rejected the invalid connections and displayed error messages with the line numbers.
* **Result: Passed**
