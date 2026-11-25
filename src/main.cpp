// author: Rylee Ford
// purpose: handles loading the files and is an intermediate between user input and the various systems in the program

#include <cctype>
#include <cstdio>
#include <iostream>
#include <vector>
#include "../include/CampusGraph.h"
#include "../include/FacilityTable.h"
#include "../include/DepartmentTree.h"
#include "../include/Files.h"

using namespace std;

CampusGraph BuildingGraph;
FacilityTable FacilityHashTable(50); // initialize the hash table for storing facility information with a size parameter
DepartmentTree DepartmentTrees;


bool FieldInputValidString(int length, string input) { // helper function to standardize and handle errors for numeric input fields
    if (length != -1) {
        if ((int) input.size() > length || input.size() < 1) { // if the string is empty or too long
            cout << "malformed input: " << input << ": input should be more than 0 characters and less than " << length << " characters." << endl; // print an error
            return false; // and exit early
        }
    } else {
        if ((int) input.size() < 1) { // if the string is empty
            cout << "malformed input: " << input << ": input should be more than 0 characters." << endl; // print an error
            return false; // and exit early
        }
    }
    

    for (char c : input) { // for every character
        if (!isalnum(c) && c != ' ') { // if it's not alphanumeric and not a space
            cout << "malformed input: " << input << ": input contains invalid characters." << endl; // print an error
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

// Gets the starting and destination buildings for shortest path
void graphShortestPath() {
    string startBuilding;
    string destinationBuilding;

    cout << "\nEnter starting building: ";
    cin >> ws;
    getline(cin, startBuilding);

    cout << "Enter destination building: ";
    getline(cin, destinationBuilding);

    BuildingGraph.findShortestPath(startBuilding, destinationBuilding);
}
// Displays the graph connectivity report
void graphConnectivityReport() {
    BuildingGraph.displayConnectivityReport();
}


void searchFacilityById() { // take input and provde that to the hash table's find function
    string id;
    cout << endl << "ID > ";
    cin >> id;
    if (!FieldInputValidString(4, id)) { // if the parsing errored out
        return; // then return
    }

    Facility fac = FacilityHashTable.FindByID(id); // otherwise, find the facility

    if (fac.name != "null") { // if it can be found
        cout << endl << fac.name << ": " << fac.id << endl; // then print it's info
        cout << " Located at: " << fac.building << endl;
        cout << " Category: " << fac.category << endl;
    } else {
        cout << "Not found: no facility with ID " << id << endl;
    }
}

void searchFacilityByName() {
    string name;

    cout << endl << "enter name :" << endl;
    cin >> ws;

    getline(cin, name);
    Files::trim(name);

    if (!FieldInputValidString(-1, name)) { // if the string is invalid
        return; // then return
    }

    vector<Facility> matches;
    int numMatches = FacilityHashTable.FindByName(name, matches);

    if (numMatches < 1) { // if no matches were found
        cout << endl << "Not found: no facility with name " << name << endl; // print an error
        return; // and escape early
    }

    cout << endl << "===== " << numMatches << " Facilities With Name \"" << name << "\" =====" << endl;
    for (int i = 0; i < numMatches; i++) { // otherwise, loop through all the matches
        cout << endl << matches.at(i).name << ": " << matches.at(i).id << endl; // and print their info
        cout << " Located at: " << matches.at(i).building << endl;
        cout << " Category: " << matches.at(i).category << endl;
    }
}

void searchFacilityByCategory() {
    string category;

    cout << endl << "enter category :" << endl;
    cin >> ws;    

    getline(cin, category);
    Files::trim(category);

    if (!FieldInputValidString(-1, category)) { // if the string is invalid
        return; // then return
    }

    vector<Facility> matches;
    int numMatches = FacilityHashTable.FindByCategory(category, matches);

    if (numMatches < 1) { // if no matches were found
        cout << endl << "Not found: no facility in category " << category << endl; // print an error
        return; // and escape early
    }

    cout << endl << "===== " << numMatches << " Facilities in Category \"" << category << "\" =====" << endl;
    for (int i = 0; i < numMatches; i++) { // otherwise, loop through all the matches
        cout << endl << matches.at(i).name << ": " << matches.at(i).id << endl; // and print their info
        cout << " Located at: " << matches.at(i).building << endl;
        cout << " Category: " << matches.at(i).category << endl;
    }
}

void categoryReport() {
    cout << endl << "===== FACILITY CATEGORY REPORT =====" << endl;

    cout << FacilityHashTable.categories.size() << " categories: " << endl << endl;

    if (FacilityHashTable.categories.size() == 0) { // if there are 0 categories
        return; // then escape
    }

    for (int i = 0; i < (int) FacilityHashTable.categories.size(); i++) { // for each category we have seen
        int num = FacilityHashTable.FindByCategory(FacilityHashTable.categories.at(i)); // get the number of matches for this category
    
        float percent = ( (float) 100 / FacilityHashTable.getTotal() ) * num; // calculate percentage

        printf("%s: contains %d facilities: %.1f%% of all facilities\n", FacilityHashTable.categories.at(i).c_str(), num, percent);
    }
}

void CreateDepartment() {
    string name;
    string parent;

    cout << endl << "Department name > ";
    cin >> ws;
    getline(cin, name);

    cout << "Parent department > ";
    cin >> ws;
    getline(cin, parent);

    DepartmentNode* parentNode = DepartmentTrees.searchDepartment(parent);

    if (parentNode != nullptr) {
        DepartmentNode* newDepartment = DepartmentTrees.addDepartment(parentNode, name);

        if (newDepartment != nullptr) {
            cout << "Department created successfully!" << endl;
        }
    }
    else {
        cout << "Parent department not found." << endl;
    }
}

void SearchForDepartment() {
    string name;

    cout << endl << "Department name > ";
    cin >> ws;
    getline(cin, name);

    DepartmentNode* Founddepartment = DepartmentTrees.searchDepartment(name);
    if (Founddepartment != nullptr) {
        cout << "Department found: " << Founddepartment->name << endl;
    } else {
        cout << "Department not found." << endl;
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
        case 3: // search facility by name
            searchFacilityByName();
            return true;
        case 4: // search facility by category
            searchFacilityByCategory();
            return true;
        case 5: // view campus graph
            BuildingGraph.displayGraph();
            return true;
        case 6: // display graph counts and degrees
            BuildingGraph.displayStatistics();
            return true;
        case 7: // Find reachable buildings (BFS)
            graphBFS();
            return true;
        case 8: // Find shortest path (BFS)
            graphShortestPath();
            return true;
        case 9: // add department 
            CreateDepartment();
            return true;
        case 10: // search department
            SearchForDepartment();
            return true;
        case 11: // display department hierarchy
            DepartmentTrees.displayDepartmentHierarchy();
            return true;
        case 12: // run preorder traversal
            DepartmentTrees.preorderTraversal();
            return true;
        case 13: // run postorder traversal
            return true;
        case 14: // run level-order traversal
            return true;
        case 15: // department statistics
            return true;
        case 16: // Facility category report
            categoryReport();
            return true;
        case 17: // display graph connectivity report
            graphConnectivityReport();
            return true;
        case 18: // exit
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
    cout << "3. Search facility by name" << endl;
    cout << "4. Search facility by category" << endl;
    cout << "5. View campus graph" << endl;
    cout << "6. Display graph counts and degrees" << endl;
    cout << "7. Find reachable buildings (BFS)" << endl;
    cout << "8. Find shortest path (BFS)" << endl;
    cout << "9. Add department" << endl;
    cout << "10. Search department" << endl;
    cout << "11. Display department hierarchy" << endl;
    cout << "12. Run preorder traversal" << endl;
    cout << "13. Run postorder traversal" << endl;
    cout << "14. Run level-order traversal" << endl;
    cout << "15. Department statistics" << endl;
    cout << "16. Facility category report" << endl;
    cout << "17. Display graph connectivity report" << endl;
    cout << "18. Exit" << endl << endl;
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

    string input;
    bool cont = true;
    while (cont) { // loop until program end; makes sure that user gets prompted with a new menu after each operaiton
        cout << endl;
        PrintMenu(); // print the menu
        cout << " > ";
        cin >> input;
        
        cont = HandleInut(input); // take user input and do things with it
    }

    cout << "bye bye..." << endl;
    return 0;

}