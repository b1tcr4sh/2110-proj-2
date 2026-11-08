// author: Rylee Ford
// purpose: Class that defines the chain for the Facilities hash table. Performs pointer operations on and stores individual Facility objects


#ifndef _FACILITYCHAIN_H_
#define _FACILITYCHAIN_H_

#include "Facility.h"

class FacilityChain { // wrapper for linked list
    public:
        void appendToList(Facility* fac); // append to the list
        Facility* LinearSearch(string id); // finds based on key (for chained elements)
        void removeFromList(Facility* fac); // helper function to remove from the list
        void ListAll(); // list all elements in the chain
        int Size(); // get the size
        int NumCollisions(); // get the number of collisions in this chain
    private:
        int size = 0;
        int collisions = 0;
        Facility* head = NULL;
        Facility* tail = NULL;
};

#endif