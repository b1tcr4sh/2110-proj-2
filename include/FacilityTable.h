// author: Rylee Ford
// purpose: Class that defines the top level Hash Table as well as Facility management functions

#ifndef _FACILITYTABLE_H_
#define _FACILITYTABLE_H_

#include <vector>
#include "Facility.h"
#include "FacilityChain.h"

class FacilityTable { // stores all facilities as a hash table
    public:
        FacilityTable(int size);

        void Load(string filename); // load from file
        bool Create(string id, string name, string building, string category); // insert a new element into the table (this function will actually create the facility)
        void Remove(string id); // find the facility and remove it
        Facility FindByID(string id); // find a specific facility; combination of a hashing function and linear search that returns a copy so we don't break the hash table
        int FindByName(string name, vector<Facility> &found); // find a all facilities with a name; has to be a linear search through the entire tabler; populates found with copies so we don't break the hash table; returns number of matches
        int FindByCategory(string category, vector<Facility> &found); // find all facilities in a category; has to be a linear search through the entire table; populates found with copies so we don't break the hash table; returns number of matches
        void ListAll(); // list every entry in the table
        float LoadFactor(); // compute the load factor
    private:
        const int multiplier = 33;
        const int startingValue = 5381;
        int size; // number of buckets in the table

        FacilityChain* hash(string id); // hash function that returns a chain (bucket) to operate on
        vector<FacilityChain*> table; // vector that contains chains; there are as many as size

        int DJB2(string key); // compute the bucket id of the key; general implementation of DJB2
        bool isValid(string key); // determine if a key is formatted correctly
        string normalize(string key); // normalize all keys before they are used
};


#endif