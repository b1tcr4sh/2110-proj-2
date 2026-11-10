#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include <string>
#include <vector>
#include <stack>
#include "DepartmentNode.h"

// functions for the department tree, department statistics, pre order traversal, and department hierarchy.

using namespace std;

class DepartmentTree{
  public:
  void Load(string filename); 
  DepartmentNode* addDepartment(DepartmentNode* parent, string name);
  DepartmentNode* searchDepartment(string name); // take in name to search for, return the found record
  void displayDepartmentHierarchy();
  void preorderTraversal();

  private:
      DepartmentNode* root = nullptr;

    DepartmentNode* SearchAncestors(DepartmentNode* source, string name, stack<DepartmentNode*> &explored);
};

#endif
