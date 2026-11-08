// author: Rylee Ford
// purpose: Class that defines the individual facility records. Contains info about the facility and a reference to the next in a linked list (once stored in a chain)


#ifndef _FACILITY_H_
#define _FACILITY_H_

#include <string>

using namespace std;

class Facility { 
    public:
        Facility(string id, string name, string building, string category); // basic constructor

        string id;
        string name;
        string building; // may need to be a class
        string category; // may need to be an enum

        Facility* next = NULL; // for linked list in separate chaining
    private:
};

#endif