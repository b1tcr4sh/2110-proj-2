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
    id = normalize(id); // normalize the key

    if (!isValid(id)) { // if the key is formatted incorrectly,
        return Facility("null", "null", "null", "null"); // then exit
    }

    FacilityChain* bucket = hash(id); // hash the id to find the bucket

    Facility* fac = bucket->LinearSearch(id); // search the bucket to find the element

    if (fac == NULL) { // if it wasn't found in bucket
        cout << "Not found: no facility with ID " << id << endl;
        return Facility("null", "null", "null", "null"); // then exit
    }

    return *fac; // otherwise, return a copy of it
}

void FacilityTable::Create(string id, string name, string building, string category) {
    id = normalize(id); // normalize the key
    Facility* newFac = new Facility(id, name, building, category);

    FacilityChain* bucket = hash(newFac->id); // hash the key and get the bucket to append into
    bucket->appendToList(newFac); // append to bucket
}

void FacilityTable::Remove(string id) {
    id = normalize(id); // normalize the key
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

    for (unsigned int i = 0; i < key.size(); i++) { // for each character in the key,
        running *= multiplier; // multiply by the constant multiplier
        running += key.at(i); // add the ASCII value of the current char
    }

    return running % size; // mod with the size of the table and return the key
}

void FacilityTable::ListAll() {
    for (unsigned int i = 0; i < size; i++) { // go through each bucket
        FacilityChain* chain = table.at(i);
        chain->ListAll(); // and list it
    }
}

bool FacilityTable::isValid(string id) {
    if (id.at(0) != 'F' || id.size() != 4) { // if the first character is not an f or is not of length 4
        cout << "Invalid format: an ID is F followed by exactly three digits" << endl; // then print an error
        return false; // and exit early
    }
    return true; // if nothing is caught, the key is fine as is
}

string FacilityTable::normalize(string key) {
    // normalize to uppercase and trim whitespace
    return key;
}
