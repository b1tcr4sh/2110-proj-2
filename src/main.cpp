#include <iostream>
#include "../include/CampusGraph.h"
#include "../include/FacilityTable.h"

using namespace std;

bool HandleInut(int input) {
    switch (input) {
        case 1: // view all facilities
            return true;
        case 2: // search facility by ID
            return true;
        case 3: // view campus graph
            return true;
        case 4: // display graph counts and degrees
            return true;
        case 5: // BFS
            return true;
        case 6: // add department
            return true;
        case 7: // search department
            return true;
        case 8: // display department hierarchy
            return true;
        case 9: // run preorder traversal
            return true;
        case 10: // exit
            return false;
        default: // unhandeled input
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

int main() {
    CampusGraph graph;
    FacilityTable table(10); // initialize the hash table for storing facility information with a size parameter

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