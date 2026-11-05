#ifndef _FACILITYTABLE_H_
#define _FACILITYTABLE_H_

#include "FacilityChain.h"

class FacilityTable { // stores all facilities as a hash table
    public:
        void Load(); // load from file
        void Create(string id, string name, string building, string category); // insert a new element into the table (this function will actually create the facility)
        void Remove(string id);
        Facility Find(string id); // wrapper for search function that returns a copy so we don't break the hash table
    private:
        Facility* Search(string id);
        FacilityChain* Hash(string id); // hash function that returns a chain (bucket) to operate on
        FacilityChain* table; // pointer to the first chain in the table. This is an array. I could do this as a Facility* and have it be a pointer to the first element in an array of Facilities that is also itself the head of the first chain, but the implementation of this sounds like a nightmare 
};


#endif