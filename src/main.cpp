#include <iostream>
#include "../include/CampusGraph.h"
#include "../include/FacilityTable.h"
#include "../include/DepartmentTree.h"
#include "../include/DepartmentTree.h"

using namespace std;

CampusGraph BuildingGraph;
FacilityTable FacilityHashTable(50); // initialize the hash table for storing facility information with a size parameter
DepartmentTree DepartmentTrees;


void graphBFS() {

}

void searchFacilityById() {
    string id;
    cout << endl << "ID > ";
    cin >> id;

    Facility fac = FacilityHashTable.Find(id);

    if (fac.name != "null") {
        cout << endl << fac.name << ": " << fac.id << endl;
            cout << " Located at: " << fac.building << endl;
            cout << " Category: " << fac.category << endl;
    }
}

bool HandleInut(int input) {
    switch (input) {
        case 1: // view all facilities
            FacilityHashTable.ListAll(); 
            return true;
        case 2: // search facility by ID
            searchFacilityById();
            return true;
        case 3: // view campus graph
            BuildingGraph.displayGraph();
            return true;
        case 4: // display graph counts and degrees
            BuildingGraph.displayStatistics();
            return true;
        case 5: // BFS
            graphBFS();
            return true;
        case 6: // add department 
            // DepartmentTrees.addDepartment();
            return true;
        case 7: // search department
            // DepartmentTrees.searchDepartment();
            return true;
        case 8: // display department hierarchy
            // DepartmentTrees.displayDepartmentHierarchy();
            return true;
        case 9: // run preorder traversal
            // DepartmentTrees.preorderTraversal();
            return true;
        case 10: // exit
            return false;
        default: // unhandeled input
            cout << "input not recognized: " << input << endl;
            return true;
    }
}

void PrintMenu() {
    cout << "==== Campus Navigator ====" << endl;
    cout << "1. View all facilities" << endl;
    cout << "2. Search facility by ID" << endl;
    cout << "3. View campus graph" << endl;
    cout << "4. Display graph counts and degrees" << endl;
    cout << "5. Find reachable buildings (BFS)" << endl;
    cout << "6. Add department" << endl;
    cout << "7. Search department" << endl;
    cout << "8. Display department hierarchy" << endl;
    cout << "9. Run preorder traversal" << endl;
    cout << "10. Exit" << endl << endl;
}

int main(int argc, char *argv[]) {
    string dataDirectory = "data";
    if (argc > 1) { // if arguments are provided
        dataDirectory = argv[1]; // use the first one as the directory to look for data files
    }

    BuildingGraph.loadBuildings(dataDirectory + "/buildings.txt");
    BuildingGraph.loadConnections(dataDirectory + "/connections.txt");
    FacilityHashTable.Load(dataDirectory + "/facilities.txt");
    DepartmentTrees.Load(dataDirectory + "/departments.txt");

    int input;
    bool cont = true;
    while (cont) { // loop until program end; makes sure that user gets prompted with a new menu after each operaiton
        cout << endl;
        PrintMenu(); // print the menu
        cin >> input;
        cont = HandleInut(input); // take user input and do things with it
    }

    cout << "bye bye..." << endl;
    return 0;

}