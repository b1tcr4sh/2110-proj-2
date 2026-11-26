#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <string>
#include <vector>
#include <queue>

using namespace std;

class CampusGraph {
private:
	vector<string> buildings;
	vector<vector<int>> adjacencyList;

public:
	bool buildingExists(string name);

	void addBuilding(const string& buildingID);
	bool loadBuildings(const string& filename);
	bool loadConnections(const string& filename);
	bool addConnection(const string& building1, const string& building2);
	void displayGraph() const;
	void displayStatistics() const;
	void breadthFirstSearch(const string& startBuilding) const;
	void findShortestPath(const string& startBuilding, const string& destinationBuilding) const;
	void displayConnectivityReport() const;
};

#endif
