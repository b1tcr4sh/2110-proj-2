#include "../include/DepartmentTree.h"
#include "../include/Files.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;
string departmentToLowerCase(string text) {
    transform(text.begin(), text.end(), text.begin(),
        [](unsigned char c) {
            return static_cast<char>(tolower(c));
        });

    return text;
}

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

    if (parent == nullptr) {
        cout << "Invalid parent department." << endl;
        return nullptr;
    }

    // Check whether department already exists
    if (searchDepartment(name) != nullptr) {
        cout << "Department already exists." << endl;
        return nullptr;
    }

    // Create the new department
    DepartmentNode* newDepartment = new DepartmentNode(name);

    newDepartment->parent = parent;

    parent->children.push_back(newDepartment);

    return newDepartment;
}

// searching the tree for each of the departments 

DepartmentNode* DepartmentTree::searchDepartment(string name) {
    if (root == nullptr) {
        cout << "Department tree is empty." << endl;
        return nullptr;
    }

    string searchName = departmentToLowerCase(name);

    stack<DepartmentNode*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
        DepartmentNode* current = nodes.top();
        nodes.pop();

        if (departmentToLowerCase(current->name) == searchName) {
            return current;
        }

        for (int i = current->children.size() - 1; i >= 0; i--) {
            nodes.push(current->children[i]);
        }
    }

    return nullptr;
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
    if (root == nullptr) {
        cout << "Department tree is empty." << endl;
        return;
    }

    cout << "Department Hierarchy:" << endl;

    stack<pair<DepartmentNode*, int>> nodes;
    nodes.push({ root, 0 });

    while (!nodes.empty()) {
        auto current = nodes.top();
        nodes.pop();

        DepartmentNode* department = current.first;
        int level = current.second;

        for (int i = 0; i < level; i++) {
            cout << "    ";
        }

        cout << "- " << department->name << endl;

        for (int i = department->children.size() - 1; i >= 0; i--) {
            nodes.push({ department->children[i], level + 1 });
        }
    }

    cout << "End of Department Hierarchy." << endl << endl;
}
// performing preorder traversal of the department tree with a DFS

void DepartmentTree::preorderTraversal() {
    if (root == nullptr) {
        cout << "Department tree is empty." << endl;
        return;
    }

    cout << "Preorder Traversal:" << endl;

    stack<DepartmentNode*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
        DepartmentNode* current = nodes.top();
        nodes.pop();

        cout << "- " << current->name << endl;

        for (int i = current->children.size() - 1; i >= 0; i--) {
            nodes.push(current->children[i]);
        }
    }

    cout << "End of Preorder Traversal." << endl << endl;
}
