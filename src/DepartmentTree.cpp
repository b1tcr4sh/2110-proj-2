#include <iostream>
#include "DepartmentTree.h"


using namespace std;

// add department

void DepartmentTree::addDepartment() {
    string departmentName;
    cout << "Enter department name: ";
    cin >> departmentName;
    Department newDepartment;
    newDepartment.name = departmentName;
    root.children.push_back(newDepartment);
}

// search department
void DepartmentTree::searchDepartment() {
    string departmentName;
    cout << "Enter department name to search: ";
    cin >> departmentName;
    
    // Implement search logic here
    bool found = false;
    for (const auto& department : root.children) {
        if (department.name == departmentName) {
            found = true;
            break;
        }
    }
    if (found) {
        cout << "Department found." << endl;
    } else {
        cout << "Department not found." << endl;
    }
}

// display department hierarchy
void DepartmentTree::displayDepartmentHierarchy() {
    // Implement display logic here
    for (const auto& department : root.children) {
        cout << department.name << endl;
    }
}

// preorder traversal
void DepartmentTree::preorderTraversal() {
    // Implement preorder traversal logic here
}
