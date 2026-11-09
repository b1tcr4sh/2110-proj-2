#ifndef DEPARTMENTNODE_H
#define DEPARTMENTNODE_H

#include <string>
#include <vector>

using namespace std;

// used to define the parent root, leaf nodes, child nodes for the department

class DepartmentNode {
public:
    string name;
    bool explored = false;

    DepartmentNode* parent = nullptr;
    vector<DepartmentNode*> children;
    DepartmentNode(const string& n) : name(n) {}
    DepartmentNode() : name("") {}

    void addChild(DepartmentNode* child) {
        if (child == nullptr) {
            return;
        }
        child->parent = this;
        children.push_back(child);
    }    
};


#endif