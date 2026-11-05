#ifndef _FACILITY_H_
#define _FACILITY_H_

#include <string>

using namespace std;

class Facility { // represents and individual facility record
    public:
        Facility(string id, string name, string building, string category);

        string id;
        string name;
        string building; // may need to be a class
        string category; // may need to be an enum

        Facility* next = NULL; // for linked list in separate chaining
    private:
};

#endif