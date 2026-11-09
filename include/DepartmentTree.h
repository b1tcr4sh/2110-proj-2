#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include <string>
#include <vector>

// functions for the department tree, department statistics, pre order traversal, and department hierarchy.

using namespace std;

class DepartmentTree{
  public:

  void addDepartment();
  void searchDepartment();
  void displayDepartmentHierarchy();
  void preorderTraversal();

  private:
    Department* root;
};

class Department {
  public:
    string name;
    vector<Department*> children;
    Department* parent;
    Department(const string& n) : name(n), parent(nullptr) {}

    private:
    void addChild(Department* child) {
        children.push_back(child);
        child->parent = this;
    }
};

#endif
