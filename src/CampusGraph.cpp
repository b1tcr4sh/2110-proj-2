#include "CampusGraph.h"
#include <iostream>
#include <fstream>

using namespace std;

void CampusGraph::addBuilding(const string& buildingID) {

    buildings.push_back(buildingID);

    adjacencyList.push_back(vector<int>());
}

bool CampusGraph::addConnection(const string& building1, const string& building2) {

    int index1 = -1;
    int index2 = -1;

    
    for (int i = 0; i < buildings.size(); i++) {

        if (buildings[i] == building1) {
            index1 = i;
        }

        if (buildings[i] == building2) {
            index2 = i;
        }
    }

   
    if (index1 == -1 || index2 == -1 || index1 == index2) {
        return false;
    }

    
    for (int neighbor : adjacencyList[index1]) {
        if (neighbor == index2) {
            return false;
        }
    }

    
    adjacencyList[index1].push_back(index2);
    adjacencyList[index2].push_back(index1);

    return true;
}

void CampusGraph::displayGraph() const {

    cout << "\n===== CAMPUS GRAPH =====\n";

    for (int i = 0; i < buildings.size(); i++) {

        cout << buildings[i] << " connects to: ";

        for (int neighbor : adjacencyList[i]) {
            cout << buildings[neighbor] << " ";
        }

        cout << endl;
    }
}

void CampusGraph::displayStatistics() const {

    cout << "\n===== GRAPH STATISTICS =====\n";

    
    cout << "Total buildings: " << buildings.size() << endl;

    int totalConnections = 0;

    
    for (int i = 0; i < buildings.size(); i++) {

        int degree = adjacencyList[i].size();

        cout << buildings[i] << " degree: " << degree << endl;

        totalConnections += degree;
    }

    
    totalConnections = totalConnections / 2;

    cout << "Total connections: " << totalConnections << endl;
}

void CampusGraph::breadthFirstSearch(const string& startBuilding) const {

    
    int startIndex = -1;

    for (int i = 0; i < buildings.size(); i++) {
        if (buildings[i] == startBuilding) {
            startIndex = i;
            break;
        }
    }

    
    if (startIndex == -1) {
        cout << "Building not found.\n";
        return;
    }

    
    vector<bool> visited(buildings.size(), false);

    
    vector<int> distance(buildings.size(), -1);

    
    queue<int> q;

    
    visited[startIndex] = true;
    distance[startIndex] = 0;
    q.push(startIndex);

    cout << "\n===== BFS REACHABILITY =====\n";

    while (!q.empty()) {

        int current = q.front();
        q.pop();

        cout << buildings[current]
            << " - Distance: " << distance[current] << endl;

        
        for (int neighbor : adjacencyList[current]) {

            if (!visited[neighbor]) {

                visited[neighbor] = true;
                distance[neighbor] = distance[current] + 1;

                q.push(neighbor);
            }
        }
    }
}

bool CampusGraph::loadBuildings(const string& filename) {

    ifstream inputFile(filename);

    
    if (!inputFile.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return false;
    }

    string line;
    int lineNumber = 0;
    int loaded = 0;
    int rejected = 0;

    while (getline(inputFile, line)) {

        lineNumber++;

        
        size_t start = line.find_first_not_of(" \t\r\n");

        if (start == string::npos) {
            continue;
        }

        size_t end = line.find_last_not_of(" \t\r\n");
        line = line.substr(start, end - start + 1);

        
        if (line[0] == '#') {
            continue;
        }

        
        bool duplicate = false;

        for (const string& building : buildings) {
            if (building == line) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            cout << filename << ", line " << lineNumber
                << ": Duplicate building: " << line << endl;

            rejected++;
            continue;
        }

       
        addBuilding(line);
        loaded++;
    }

    inputFile.close();

    cout << "\n===== BUILDING LOAD SUMMARY =====\n";
    cout << "File: " << filename << endl;
    cout << "Buildings loaded: " << loaded << endl;
    cout << "Buildings rejected: " << rejected << endl;

    return true;
}

bool CampusGraph::loadConnections(const string& filename) {

    ifstream inputFile(filename);

    
    if (!inputFile.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return false;
    }

    string line;
    int lineNumber = 0;
    int loaded = 0;
    int rejected = 0;

    while (getline(inputFile, line)) {

        lineNumber++;

        
        size_t start = line.find_first_not_of(" \t\r\n");

        if (start == string::npos) {
            continue;
        }

        size_t end = line.find_last_not_of(" \t\r\n");
        line = line.substr(start, end - start + 1);

        
        if (line[0] == '#') {
            continue;
        }

        
        size_t separator = line.find('|');

        if (separator == string::npos ||
            line.find('|', separator + 1) != string::npos) {

            cout << filename << ", line " << lineNumber
                << ": Invalid connection format." << endl;

            rejected++;
            continue;
        }

        
        string building1 = line.substr(0, separator);
        string building2 = line.substr(separator + 1);

        
        
        size_t firstStart = building1.find_first_not_of(" \t\r\n");
        size_t firstEnd = building1.find_last_not_of(" \t\r\n");

        size_t secondStart = building2.find_first_not_of(" \t\r\n");
        size_t secondEnd = building2.find_last_not_of(" \t\r\n");

        
        if (firstStart == string::npos || secondStart == string::npos) {

            cout << filename << ", line " << lineNumber
                << ": Missing building name." << endl;

            rejected++;
            continue;
        }

        building1 = building1.substr(firstStart, firstEnd - firstStart + 1);
        building2 = building2.substr(secondStart, secondEnd - secondStart + 1);

        
        if (addConnection(building1, building2)) {
            loaded++;
        }
        else {
            cout << filename << ", line " << lineNumber
                << ": Invalid or duplicate connection: "
                << building1 << " | " << building2 << endl;

            rejected++;
        }
    }

    inputFile.close();

    cout << "\n===== CONNECTION LOAD SUMMARY =====\n";
    cout << "File: " << filename << endl;
    cout << "Connections loaded: " << loaded << endl;
    cout << "Connections rejected: " << rejected << endl;

    return true;
}