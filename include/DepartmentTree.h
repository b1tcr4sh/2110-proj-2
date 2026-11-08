#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include <string>
#include <vector>

using namespace std;

// for the department tree, department statistics, pre order traversal, and department hierarchy.

class DepartmentTree {
public:
    void addDepartment();
    void searchDepartment();
    void displayDepartmentHierarchy();
    void preorderTraversal();


private:
    struct Department {
        string name;
        vector<Department> children;
    };

    Department root;
};  

#endif // DEPARTMENTTREE_H