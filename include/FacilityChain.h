#ifndef _FACILITYCHAIN_H_
#define _FACILITYCHAIN_H_

#include "Facility.h"

class FacilityChain { // wrapper for linked list
    public:
        string bucket; // hashed value that will refer to this bucket (multiple ids will hash to this value)

        void appendToList(Facility* fac); // append to the list
        Facility* LinearSearch(string id); // finds based on key (for chained elements)
        void removeFromList(Facility* fac); // helper function to remove from the list
    private:
        Facility* head;
        Facility* tail;
};

#endif