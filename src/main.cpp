// author: Rylee Ford
// purpose: handles loading the files and is an intermediate between user input and the various systems in the program

#include <cctype>
#include <iostream>
#include "../include/CampusGraph.h"
#include "../include/FacilityTable.h"

using namespace std;

CampusGraph BuildingGraph;
FacilityTable FacilityHashTable(50); // initialize the hash table for storing facility information with a size parameter

bool FieldInputValidString(unsigned int length, string input) { // helper function to standardize and handle errors for numeric input fields
    if (input.size() > length || input.size() < 1) { // if the string is empty or too long
        cout << "malformed input: " << input << ": input should be more than 0 characters and less than " << length << " characters." << endl; // print an error
        return false; // and exit early
    }

    for (char c : input) { // for every character
        if (!isalnum(c) || c == ' ') { // if it's not alphanumeric or a space
            cout << "malformed input: " << input << ": input should be a number." << endl; // print an error
            return false; // and exit early
        }
    }

    return true;
}

int ParseFieldInputInt(unsigned int length, string input) { // helper function to standardize and handle errors for numeric input fields
    if (input.size() > length || input.size() < 1) { // if the string is empty or too long
        cout << "Malformed Input: " << input << ": input should be more than 0 characters and less than " << length << " characters." << endl; // print an error
        return -1; // and exit early
    }

    for (char c : input) { // for every character
        if (!isdigit(c)) { // if it's not a digit
            cout << "Malformed Input: " << input << ": input should be a number." << endl; // print an error
            return -1; // and exit early
        }
    }

    return stoi(input); // convert to an int and return
}

void graphBFS() {
    string startBuilding;

    cout << "\nEnter starting building: ";

    cin >> ws;
    getline(cin, startBuilding);

    BuildingGraph.breadthFirstSearch(startBuilding);
}


void searchFacilityById() { // take input and provde that to the hash table's find function
    string id;
    cout << endl << "ID > ";
    cin >> id;
    if (!FieldInputValidString(4, id)) { // if the parsing errored out
        return; // then return
    }

    Facility fac = FacilityHashTable.Find(id); // otherwise, find the facility

    if (fac.name != "null") { // if it can be found
        cout << endl << fac.name << ": " << fac.id << endl; // then print it's info
        cout << " Located at: " << fac.building << endl;
        cout << " Category: " << fac.category << endl;
    }
}

bool HandleInut(string inputStr) { // take in raw input, process it, and handle it
    int input = ParseFieldInputInt(2, inputStr); // parse the input


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
            cout << "input not recognized: " << input << endl;
            return true;
    }
}

void PrintMenu() { // what it says
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

    string input;
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