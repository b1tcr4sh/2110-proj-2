#ifndef DEPARTMENTNODE_H
#define DEPARTMENTNODE_H

#include <string>
#include <vector>

using namespace std;

// used to define the parent root, leaf nodes, child nodes for the department

class DepartmentNode {
public:
    string name;
    vector<DepartmentNode> children;
    DepartmentNode(const string& n) : name(n) {}
    DepartmentNode() : name("") {}

    void addChild(const DepartmentNode& child) {
        children.push_back(child);
    }
};


#endif // DEPARTMENTNODE_H