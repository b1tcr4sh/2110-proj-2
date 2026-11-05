#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "../include/FacilityTable.h"

FacilityTable::FacilityTable(int size) {
    this->size = size;

    for (int i = 0; i < size; i++) { // fill table with empty chains
        table.push_back(new FacilityChain);
    }
}

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

Facility FacilityTable::Find(string id) {
    FacilityChain* bucket = hash(id); // hash the id to find the bucket

    return *(bucket->LinearSearch(id)); // search the bucket to find the element we are looking for and return a copy of it
}

void FacilityTable::Create(string id, string name, string building, string category) {
    Facility* newFac = new Facility(id, name, building, category);

    FacilityChain* bucket = hash(newFac->id); // hash the key and get the bucket to append into
    bucket->appendToList(newFac); // append to bucket
}

void FacilityTable::Remove(string id) {
    FacilityChain* bucket = hash(id); // find the bucket that the key belongs in

    Facility* fac = bucket->LinearSearch(id); // find the correct element in the bucket
    bucket->removeFromList(fac); // and remove it
}

FacilityChain* FacilityTable::hash(string id) {
    int hash = DJB2(id);

    
    return table.at(hash); // return the pointer to the corresponding bucket (the hash is the array index)
}

int FacilityTable::DJB2(string key) {
    int running = startingValue; // start with the constant starting value

    for (int i = 0; i < key.size(); i++) { // for each character in the key,
        running *= multiplier; // multiply by the constant multiplier
        running += key.at(i); // add the ASCII value of the current char
    }

    return running % size; // mod with the size of the table and return the key
}