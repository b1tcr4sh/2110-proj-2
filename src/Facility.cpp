// author: Rylee Ford
// purpose: implement the individual facility records. Contains info about the facility and a reference to the next in a linked list (once stored in a chain)

#include "../include/Facility.h"

Facility::Facility(string id, string name, string building, string category) { // basic constructor for initializing the values of the Facility
    this->id = id;
    this->name = name;
    this-> building = building;
    this->category = category;
}