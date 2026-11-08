// author: Rylee Ford
// purpose: implements the top level Hash Table as well as Facility management functions

#include <fstream>
#include <iostream>
#include <vector>
#include "../include/FacilityTable.h"
#include "../include/Files.h"

FacilityTable::FacilityTable(int size) { // basic constructor that defines the number of buckets the table will have
    this->size = size;

    for (int i = 0; i < size; i++) { // fill table with empty chains
        table.push_back(new FacilityChain);
    }
}

void FacilityTable::Load(string filename) { // load the facilities.txt file, process, and store it's input
    ifstream file(filename);

    if (file.bad() || file.fail() || !file.is_open()) {
        cout << "Warning: File \"" << filename << "\" failed to open." << endl;
        return; // exit early
    }

    string line;
    int lineNumber = 0; // count lines for error handling
    int loaded = 0; // count the amount of loaded entries
    int rejected = 0; // count the amount of rejected entries
    
    
    while (getline(file, line)) { // read each line from file
        vector<string> tokens = Files::processFileLine(line, "|", lineNumber); // prcocess the line into tokens

        if (tokens.size() == 0) { // if line is either empty or is a comment
            continue; // skip it
        }

        if (tokens.size() != 4) { // if there are not 4 tokens, the formatting is incorrect
            cout << "Malformed Line: " << filename << " line " << lineNumber << ": incorrect number or format of tokens." << endl;
            rejected++; // iterate rejected
            continue; // skip it
        }

        string id = tokens.at(0); // the first token (it will get normalized)
        string name = Files::trim(tokens.at(1)); // the trimmed second token
        string building = Files::trim(tokens.at(2)); // the trimmed third token
        string category = Files::trim(tokens.at(3)); // the  trimmed forth token

        if (name == "") {
            cout << "Warning: Facility name is empty: line " << lineNumber << endl;
            rejected++;
            continue;
        }

        if (Create(id, name, building, category)) loaded++; // if it is succesfully created and added to the table, then incremend the number of loaded records
        else rejected++; // otherwise, increment the number of rejected records
    }

    cout << endl << "===== FACILITY LOAD SUMMARY =====" << endl;
    cout << "File: " << filename << endl;
    cout << "Facilities loaded: " << loaded << endl;
    cout << "Facilities rejected: " << rejected << endl;
    
    int collisions = 0;
    int total = 0;
    for (unsigned int i = 0; i < table.size(); i++) {
        FacilityChain* chain = table.at(i);
        collisions += chain->NumCollisions(); // add the number of collisions 
        total += chain->Size(); // add the size of the chain
    }
    cout << "Facility Collisions: " << collisions << endl;
    cout << "Number of Chains: " << size << endl;
    cout << "Number of Facilities Stored: " << total << endl;
    cout << "Facilities Load Factor: " << LoadFactor() << endl;
}

Facility FacilityTable::Find(string id) { // search for a key in a bucket by hashing it, then searching the bucket to find the entry
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

bool FacilityTable::Create(string id, string name, string building, string category) { // create a facility entry and insert it into the chain
    id = normalize(id); // normalize the key

    if (!isValid(id)) { // if the format of the id is invalid,
        return false; // then exit early and state rejection
    }

    Facility* newFac = new Facility(id, name, building, category);

    FacilityChain* bucket = hash(newFac->id); // hash the key and get the bucket to append into
    
    if (bucket->LinearSearch(id) != NULL) { // if this bucket already contains this id
        cout << "Duplicate facility id: " << id << endl; // then print an error 
        return false; // and return early and state rejection
    }
    
    bucket->appendToList(newFac); // append to bucket
    return true;
}

void FacilityTable::Remove(string id) { // remove an entry from the table
    id = normalize(id); // normalize the key
    FacilityChain* bucket = hash(id); // find the bucket that the key belongs in

    Facility* fac = bucket->LinearSearch(id); // find the correct element in the bucket
    bucket->removeFromList(fac); // and remove it
}

FacilityChain* FacilityTable::hash(string id) { // hashing wrapper function that gets the index of the hashed key and returns a reference to the appropriate chain
    int hash = DJB2(id);
    // cout << hash << endl;
    
    return table.at(hash); // return the pointer to the corresponding bucket (the hash is the array index)
}

int FacilityTable::DJB2(string key) { // implements the DJB2 hashing algorithm
    int running = startingValue; // start with the constant starting value
    // cout << "hashing..." << endl;

    for (unsigned int i = 0; i < key.size(); i++) { // for each character in the key,
        running *= multiplier; // multiply by the constant multiplier
        running += key.at(i); // add the ASCII value of the current char
    }

    return running % size; // mod with the size of the table and return the key
}

void FacilityTable::ListAll() { // iterate through each chain in the table and print out their contents
    cout << endl << "===== Facilities List =====" << endl;

    for (unsigned int i = 0; i < table.size(); i++) { // go through each bucket
        FacilityChain* chain = table.at(i);
        if (chain == NULL) {
            cout << "chain uninitialized.." << endl;
            return;
        }
        chain->ListAll(); // and list it
    }
}

bool FacilityTable::isValid(string id) { // helper function to determine if a key is "valid" (is formatted correctly)
    if (id.at(0) != 'F' || id.size() != 4) { // if the first character is not an f or is not of length 4
        cout << "Invalid format: an ID is F followed by exactly three digits" << endl; // then print an error
        return false; // and exit early
    }
    return true; // if nothing is caught, the key is fine as is
}

string FacilityTable::normalize(string key) { // helper function to normalize a key before doing anything with it
    // normalize to uppercase and trim whitespace
    key = Files::to_upper(key);
    key = Files::trim(key);
    return key;
}

float FacilityTable::LoadFactor() { // computes and returns the current load factor of the table
    int sum = 0;
    for (unsigned int i = 0; i < table.size(); i++) {
        FacilityChain* chain = table.at(i);

        sum += chain->Size();
    }

    return (float) sum / (float) size; 
}