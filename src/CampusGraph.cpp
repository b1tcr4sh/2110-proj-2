#include "../include/CampusGraph.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>

// Converts string to lowercase so capitalization doesn't matter when comparing names
using namespace std;
string toLowerCase(string text) {
    transform(text.begin(), text.end(), text.begin(),
        [](unsigned char c) { return tolower(c); });
    return text;
}

// Adds building to graph and makes empty list of connections
void CampusGraph::addBuilding(const string& buildingID) {

    buildings.push_back(buildingID);

    adjacencyList.push_back(vector<int>());
}

// If connection is valid, adds connection between two buildings
bool CampusGraph::addConnection(const string& building1, const string& building2) {

    int index1 = -1;
    int index2 = -1;

    // Find where each building is stored in the vector
    for (unsigned int i = 0; i < buildings.size(); i++) {

        if (toLowerCase(buildings[i]) == toLowerCase(building1)) {
            index1 = i;
        }

        if (toLowerCase(buildings[i]) == toLowerCase(building2)) {
            index2 = i;
        }
    }

   // If names are the same or building doesn't exsit, dont add connection
    if (index1 == -1 || index2 == -1 || index1 == index2) {
        return false;
    }

    // Makes sure connection hasn't already been added
    for (int neighbor : adjacencyList[index1]) {
        if (neighbor == index2) {
            return false;
        }
    }

    // Adds both sides of the connection
    adjacencyList[index1].push_back(index2);
    adjacencyList[index2].push_back(index1);

    return true;
}

// Prints each building and the buildings connected
void CampusGraph::displayGraph() const {

    cout << "\n===== CAMPUS GRAPH =====\n";

    for (unsigned int i = 0; i < buildings.size(); i++) {

        cout << buildings[i] << " connects to: ";

        if (adjacencyList[i].empty()) {
            cout << "(no connections)";
        }
        else {
            for (int neighbor : adjacencyList[i]) {
                cout << buildings[neighbor] << " ";
            }
        }

        cout << endl;
    }
}

// Prints total buildings, total connections, and each buildings degree
void CampusGraph::displayStatistics() const {

    cout << "\n===== GRAPH STATISTICS =====\n";

    
    cout << "Total buildings: " << buildings.size() << endl;

    int totalConnections = 0;

    
    for (unsigned int i = 0; i < buildings.size(); i++) {

        int degree = adjacencyList[i].size();

        cout << buildings[i] << " degree: " << degree << endl;

        totalConnections += degree;
    }

    // Every connection gets counted twice, so divide by two
    totalConnections = totalConnections / 2;

    cout << "Total connections: " << totalConnections << endl;
}

// Uses BFS to find which buildings can be reached from the starting building
void CampusGraph::breadthFirstSearch(const string& startBuilding) const {

    int startIndex = -1;

    // Disregard capitalization when finding the starting building
    for (unsigned int i = 0; i < buildings.size(); i++) {
        if (toLowerCase(buildings[i]) == toLowerCase(startBuilding)) {
            startIndex = i;
            break;
        }
    }

    // Stop if building was not found
    if (startIndex == -1) {
        cout << "Building not found.\n";
        return;
    }

    vector<bool> visited(buildings.size(), false);
    vector<int> distance(buildings.size(), -1);

    queue<int> q;

    // Start BFS at selected building
    visited[startIndex] = true;
    distance[startIndex] = 0;
    q.push(startIndex);

    int reachableCount = 0;

    cout << "\n===== BFS REACHABILITY =====\n";

    // Continue until there are no buildings in queue
    while (!q.empty()) {

        int current = q.front();
        q.pop();

        cout << buildings[current]
            << " - Distance: " << distance[current] << endl;

        reachableCount++;

        // Check connected buildings and add the ones that haven't been visited
        for (int neighbor : adjacencyList[current]) {

            if (!visited[neighbor]) {

                visited[neighbor] = true;
                distance[neighbor] = distance[current] + 1;

                q.push(neighbor);
            }
        }
    }

    cout << "Reachable buildings: " << reachableCount
        << " out of " << buildings.size() << endl;
}

// Reads building names from file, checks for duplicates or invalid entries
bool CampusGraph::loadBuildings(const string& filename) {
    
    ifstream inputFile(filename);

    // Make sure file is opened successfully
    if (!inputFile.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return false;
    }

    string line;
    int lineNumber = 0;
    int loaded = 0;
    int rejected = 0;

    // Go through file one line at a time
    while (getline(inputFile, line)) {

        lineNumber++;

        // Find the first character that isnt whitespace
        size_t start = line.find_first_not_of(" \t\r\n");

        if (start == string::npos) {
            continue;
        }

        // Remove extra spaces from beginning and end of line
        size_t end = line.find_last_not_of(" \t\r\n");
        line = line.substr(start, end - start + 1);

       
        if (line[0] == '#') {
            continue;
        }

        // Check if building is already in graph 
        bool duplicate = false;

        for (const string& building : buildings) {
            if (toLowerCase(building) == toLowerCase(line)) {
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

       // Add building if it isnt a duplicate
        addBuilding(line);
        loaded++;
    }

    inputFile.close();

    // Show how many buildings were added and how many were rejected
    cout << "\n===== BUILDING LOAD SUMMARY =====\n";
    cout << "File: " << filename << endl;
    cout << "Buildings loaded: " << loaded << endl;
    cout << "Buildings rejected: " << rejected << endl;

    return true;
}

// Reads the connections from file and checks if valid
bool CampusGraph::loadConnections(const string& filename) {

    ifstream inputFile(filename);

    // Make sure file is open successfully
    if (!inputFile.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return false;
    }

    string line;
    int lineNumber = 0;
    int loaded = 0;
    int rejected = 0;

    // Go through file one line at a time
    while (getline(inputFile, line)) {

        lineNumber++;

        // Find first character that isn't whitespace
        size_t start = line.find_first_not_of(" \t\r\n");

        if (start == string::npos) {
            continue;
        }
        // Removes extra spaces from beginning and end of line
        size_t end = line.find_last_not_of(" \t\r\n");
        line = line.substr(start, end - start + 1);

        
        if (line[0] == '#') {
            continue;
        }

        // Find | that separates building names
        size_t separator = line.find('|');

        // Make sure only one | in the line
        if (separator == string::npos ||
            line.find('|', separator + 1) != string::npos) {

            cout << filename << ", line " << lineNumber
                << ": Invalid connection format." << endl;

            rejected++;
            continue;
        }

        // Split line into two building names
        string building1 = line.substr(0, separator);
        string building2 = line.substr(separator + 1);

        
        // Find extra spaces around each building name
        size_t firstStart = building1.find_first_not_of(" \t\r\n");
        size_t firstEnd = building1.find_last_not_of(" \t\r\n");

        size_t secondStart = building2.find_first_not_of(" \t\r\n");
        size_t secondEnd = building2.find_last_not_of(" \t\r\n");

        // Reject connection if either name is empty
        if (firstStart == string::npos || secondStart == string::npos) {

            cout << filename << ", line " << lineNumber
                << ": Missing building name." << endl;

            rejected++;
            continue;
        }
        // Remove extra spaces around building names
        building1 = building1.substr(firstStart, firstEnd - firstStart + 1);
        building2 = building2.substr(secondStart, secondEnd - secondStart + 1);

        // Try adding connection and count whether it worked or was rejected
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

    // Show how many connections were added and rejected
    cout << "\n===== CONNECTION LOAD SUMMARY =====\n";
    cout << "File: " << filename << endl;
    cout << "Connections loaded: " << loaded << endl;
    cout << "Connections rejected: " << rejected << endl;

    return true;
}