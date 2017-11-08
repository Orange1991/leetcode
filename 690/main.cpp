#include "iostream"
#include "vector"

using namespace std;

class Employee {
public:
    // It's the unique ID of each node.
    // unique id of this employee
    int id;
    // the importance value of this employee
    int importance;
    // the id of direct subordinates
    vector<int> subordinates;
};

class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        int MAX = 2000;
        vector<int> importances(MAX + 1);
        for (Employee* e : employees) {
            importances[e->id] = e->importance;
            cout << e->importance << endl;
        }
    }
};

int main() {
    Employee e1;
    // e1->id = 1;
    // e1->importance = 5;
    // e1->subordinates = new vector<int>();
    // e1->subordinates.push_back(2);
    // e1->subordinates.push_back(3);
    // Employee* e2 = new Employee();
    // e2->id = 2;
    // e2->importance = 3;
    // e2->subordinates = new vector<int>();
    // Employee* e3 = new Employee();
    // e3->id = 3;
    // e3->importance = 3;
    // e3->subordinates = new vector<int>();
    vector<Employee*> employees;
    employees.push_back(&e1);
    // employees.push_back(e2);
    // employees.push_back(e3);
    Solution s;
    s.getImportance(employees, 1);
}