#include <fstream>
#include <sstream>
#include <iostream>
#include "../include/FacilityTable.h"

void FacilityTable::Load() {
    ifstream file("data/facilities.txt");

    if (file.bad() || file.fail()) {
        cout << "Warning: File \"data/facilities.txt\" failed to open." << endl;
        return; // exit early
    }
    int lineNumber = 1; // count lines for error handling
    
    
    while (!file.eof()) {
        string line;
        getline(file, line); // read 1 line from file

        if (line.find("#") || line == "") {
            continue; // this line is either a comment or an empty line, so we can disregard it
        }

        //split line into tokens
        stringstream stream(line);

        string id;
        getline(stream, id, '|');

        string name;
        getline(stream, name, '|');

        string building;
        getline(stream, building, '|');

        string category;
        getline(stream, category, '|');

        if (!line.empty()) {
            cout << "Warning: File \"data/facilities.txt\" contained incorrect formatting. Too many fields were provided." << endl;
            continue;
        }

        lineNumber++;
    }
}