#include "../include/DepartmentTree.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// adding the department to the main tree

DepartmentNode* DepartmentTree::addDepartment(DepartmentNode* parent, string name, string id) {

    if (root == nullptr) {
        cout << "Parent department not found." << endl;
        return;
    }

    // creating a whole new department
    DepartmentNode* newDepartment = new DepartmentNode(name);

    // setting the parent of the new department to the root
    newDepartment->parent = parent;

    // adding the new department to the root's children list
    parent->children.push_back(newDepartment);
    cout << "Department added successfully." << endl;
}

// searching the tree for each of the departments 

DepartmentNode* DepartmentTree::searchDepartment(string name) { // perform a DFS to find a matching department
    if (root == nullptr) {
        cout << "Department tree is empty." << endl;
        return;
    }

    vector<DepartmentNode*> explored;
    
    DepartmentNode* source = root; // start at the root

    if (source->name == name) {
        return source;
    }

    SearchAncestors(source, name); // recursively search each children
    
}

DepartmentNode* DepartmentTree::SearchAncestors(DepartmentNode* source, string name) {
    if (source->name == name) {
        return source;
    }

    for (unsigned int i = 0; i < source->children.size(); i++) {
        if (source->children.at(i)->name == name) {
            SearchAncestors(source->children.at(i), name);
        }
    }
}

// displaying the hierarchy for the departments
    
void DepartmentTree::displayDepartmentHierarchy() {
    cout << "Department Hierarchy:" << endl;
    for (const auto& department : root->children) {
        cout << "- " << department->name << endl;
    }
    cout << "End of Department Hierarchy." << endl;
    cout << endl;
}

// performing preorder traversal of the department tree with a DFS

void DepartmentTree::preorderTraversal() {
    cout << "Preorder Traversal:" << endl;
    for (const auto& department : root->children) {
        cout << "- " << department->name << endl;
    }
    cout << "End of Preorder Traversal." << endl;
    cout << endl;

}
