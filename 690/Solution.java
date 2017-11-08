import java.util.ArrayList;
import java.util.List;
import java.util.LinkedList;
import java.util.Queue;

public class Solution {
    private int MAX = 2000;
    public int getImportance(List<Employee> employees, int id) {
        Employee[] eList = new Employee[MAX + 1];
        for (Employee e : employees) {
            eList[e.id] = e;
        }
        int importance = 0;
        Queue<Employee> unvisited = new LinkedList<Employee>();
        unvisited.add(eList[id]);
        while (!unvisited.isEmpty()) {
            Employee e = unvisited.poll();
            importance += e.importance;
            if (e.subordinates != null) {
                for (Integer eId : e.subordinates) {
                    unvisited.add(eList[eId]);
                }
            }
        }
        System.out.println(importance);
        return importance;
    }

    public static void main(String[] args) {
        Employee e1 = new Employee();
        e1.id = 1;
        e1.importance = 5;
        e1.subordinates = new ArrayList<Integer>();
        e1.subordinates.add(2);
        e1.subordinates.add(3);
        Employee e2 = new Employee();
        e2.id = 2;
        e2.importance = 3;
        e2.subordinates = new ArrayList<Integer>();
        Employee e3 = new Employee();
        e3.id = 3;
        e3.importance = 3;
        e3.subordinates = new ArrayList<Integer>();
        List<Employee> employees = new ArrayList<Employee>();
        employees.add(e1);
        employees.add(e2);
        employees.add(e3);
        new Solution().getImportance(employees, 1);
    }
}

/**
 * Employee info
 */
class Employee {
    /**
     * It's the unique id of each node;
     * unique id of this employee
     */
    public int id;
    /**
     * the importance value of this employee
     */
    public int importance;
    /**
     * the id of direct subordinates
     */
    public List<Integer> subordinates;
};
