#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include <string>
#include <vector>
#include "DepartmentNode.h"

// functions for the department tree, department statistics, pre order traversal, and department hierarchy.

using namespace std;

class DepartmentTree{
  public:

  DepartmentNode* addDepartment(DepartmentNode* parent, string name, string id);
  DepartmentNode* searchDepartment(string name); // take in name to search for, return the found record
  void displayDepartmentHierarchy();
  void preorderTraversal();

  private:
    DepartmentNode* root;

    DepartmentNode* SearchAncestors(DepartmentNode* source, string name);
};

#endif
