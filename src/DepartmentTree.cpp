#include "../include/DepartmentTree.h"
#include "../include/Files.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void DepartmentTree::Load(string filename) {
    ifstream file(filename);

    if (file.bad() || file.fail() || !file.is_open()) {
        cout << "Warning: File \"" << filename << "\" failed to open." << endl;
        return; // exit early
    }

    string line;
    int lineNumber = 0; // count lines for error handling
    int loaded = 0; // count the amount of loaded entries
    int rejected = 0; // count the amount of rejected entries
    
    
    while (getline(file, line)) { // read each line from file
        vector<string> tokens = Files::processFileLine(line, "|", lineNumber); // prcocess the line into tokens

        if (tokens.size() == 0) { // if line is either empty or is a comment
            continue; // skip it
        }

        if (tokens.size() != 2) { // if there are not 4 tokens, the formatting is incorrect
            cout << "Malformed Line: " << filename << " line " << lineNumber << ": incorrect number or format of tokens." << endl;
            continue; // skip it
        }

        string name = Files::trim(tokens.at(0)); // the first token 
        string parent = Files::trim(tokens.at(1)); // the trimmed second token

        if (name == "") {
            cout << "Warning: Department name is empty: line " << lineNumber << endl;
            rejected++;
            continue;
        }

        if (parent == "NONE") {
            // creating a whole new department
            DepartmentNode* newDepartment = new DepartmentNode(name);

            root = newDepartment;
        
            loaded++;
        } else {
            DepartmentNode* parentNode = searchDepartment(parent);
            if (parentNode == nullptr) {
                cout << "Warning: Department " << parent << " not found. line: " << lineNumber << endl;
                rejected++; // increment the number of rejected records
                continue;
            }

            DepartmentNode* node = addDepartment(parentNode, name);
            if (node == nullptr) {
                cout << "Warning: Department " << name << " could not be added. line: " << lineNumber << endl;
                rejected++; // increment the number of rejected records
                continue;
            }

            loaded++;
        }
    }

    cout << endl << "===== DEPARTMENT LOAD SUMMARY =====" << endl;
    cout << "File: " << filename << endl;
    cout << "Departments loaded: " << loaded << endl;
    cout << "Departments rejected: " << rejected << endl;
}

// adding the department to the main tree

DepartmentNode* DepartmentTree::addDepartment(DepartmentNode* parent, string name) {

    if (root == nullptr) {
        cout << "Root not initialized." << endl;
        return nullptr;
    }

    // creating a whole new department
    DepartmentNode* newDepartment = new DepartmentNode(name);

    // setting the parent of the new department to the root
    newDepartment->parent = parent;

    // adding the new department to the root's children list
    parent->children.push_back(newDepartment);
    cout << "Department added successfully." << endl;
    
    return newDepartment;
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
        source->explored = true;
        return SearchAncestors(source->parent, name, explored);
    }

    bool allChildrenExplored = true;
    for (unsigned int i = 0; i < source->children.size(); i++) {
        if (source->children.at(i)->explored == false) {
            allChildrenExplored = false;
            break;
        }
    }

    if (allChildrenExplored) {
        source->explored = true;
        return SearchAncestors(source->parent, name, explored);
    }

    for (unsigned int i = 0; i < source->children.size(); i++) {
        if (source->children.at(i)->explored == false) { // for each unexplored child
            return SearchAncestors(source->children.at(i), name, explored); // search it's unexplored ancestors
        }
    }

    return nullptr;
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
