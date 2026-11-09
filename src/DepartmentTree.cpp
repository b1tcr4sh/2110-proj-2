#include "../include/DepartmentTree.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// adding the department to the main tree

DepartmentNode* DepartmentTree::addDepartment(DepartmentNode* parent, string name, string id) {

    if (root == nullptr) {
        cout << "Parent department not found." << endl;
        return nullptr;
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
        return nullptr;
    }

    stack<DepartmentNode*> explored;

    DepartmentNode* source = root; // start at the root

    if (source->name == name) {
        return source;
    }

    DepartmentNode* result = SearchAncestors(source, name, explored); // recursively search each children
    if (result == nullptr) {
        cout << "not found" << endl;
    }

    return result;
}

DepartmentNode* DepartmentTree::SearchAncestors(DepartmentNode* source, string name, stack<DepartmentNode*> &explored) {
    if (source->name == name) { // if the source is the correct one, 
        return source; // return it
    }

    if (source->children.size() == 0) { // otherwise, if we have hit a leaf and this still isn't the one we're looking for
        // explored.push(source); // then mark it as explored
        source->explored = true;
        return nullptr;
    }

    bool allChildrenExplored = true;
    for (unsigned int i = 0; i < source->children.size(); i++) {
        if (source->children.at(i)->explored == false) {
            allChildrenExplored = false;
            break;
        }
    }

    if (allChildrenExplored) {
        return nullptr;
    }

    for (unsigned int i = 0; i < source->children.size(); i++) {
        if (source->children.at(i)->explored == false) { // for each unexplored child
            SearchAncestors(source, name, explored); // search it's unexplored ancestors
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
