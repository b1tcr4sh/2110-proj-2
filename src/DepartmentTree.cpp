#include "DepartmentTree.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// adding the department to the main tree

void DepartmentTree::addDepartment() {
    string departmentName;

    cout << "Enter the department name: ";
    cin >> departmentName;

    Department* parent = root;

    if (root == nullptr) {
        cout << "Parent department not found." << endl;
        return;
    }

    // creating a whole new department
    Department* newDepartment = new Department(departmentName);

    // setting the parent of the new department to the root
    newDepartment->parent = parent;

    // adding the new department to the root's children list
    parent->children.push_back(newDepartment);
    cout << "Department added successfully." << endl;
}

// searching the tree for each of the departments 

void DepartmentTree::searchDepartment() {
    string departmentName;
    cout << "Enter the department name to search: ";
    cin >> departmentName;

    if (root == nullptr) {
        cout << "Department tree is empty." << endl;
        return;
    }
    if (root->children.empty()) {
        cout << "No departments found." << endl;
        return;
    }
    for (const auto& department : root->children) {
        if (department->name == departmentName) {
            cout << "Department found: " << department->name << endl;
            return;
        }
    }
    cout << "Department not found." << endl;    
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
