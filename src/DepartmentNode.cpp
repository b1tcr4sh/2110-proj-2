#include "../include/DepartmentNode.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// creating the department node ("parent")
DepartmentNode* createDepartment(string name) {
    return new DepartmentNode(name);
}

// constructor for the department node
DepartmentNode::DepartmentNode(const string& n) : name(n), parent(nullptr) {
}

// adding a child department to the parent department

void DepartmentNode::addChild(DepartmentNode* child) {
    if (child == nullptr) {
        return;
    }
    child->parent = this;
    children.push_back(child);
}
