/*
 * Lab 9 - Task 2: Company Organizational Hierarchy
 * Binary tree for employee org chart with traversals
 */

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
#include <iomanip>
using namespace std;

struct Employee {
    int employeeId;
    string name;
    string position;
    double salary;
    Employee* leftChild;   // Subordinate
    Employee* rightChild;  // Peer at same level
    
    Employee(int id, string n, string pos, double sal)
        : employeeId(id), name(n), position(pos), salary(sal),
          leftChild(nullptr), rightChild(nullptr) {}
};

class OrganizationTree {
private:
    Employee* root;
    
    // Helper to find employee by ID
    Employee* findEmployee(Employee* node, int id) {
        if (node == nullptr) return nullptr;
        if (node->employeeId == id) return node;
        
        Employee* found = findEmployee(node->leftChild, id);
        if (found) return found;
        return findEmployee(node->rightChild, id);
    }
    
    // Helper to find parent of an employee
    Employee* findParent(Employee* node, int id, Employee* parent = nullptr) {
        if (node == nullptr) return nullptr;
        if (node->employeeId == id) return parent;
        
        Employee* found = findParent(node->leftChild, id, node);
        if (found) return found;
        return findParent(node->rightChild, id, node);
    }
    
    // Calculate total salary in subtree
    double calculateTotalSalary(Employee* node) {
        if (node == nullptr) return 0;
        return node->salary + 
               calculateTotalSalary(node->leftChild) + 
               calculateTotalSalary(node->rightChild);
    }
    
    // Find employee with highest salary
    void findHighestSalary(Employee* node, double& maxSalary, Employee*& maxEmp) {
        if (node == nullptr) return;
        
        if (node->salary > maxSalary) {
            maxSalary = node->salary;
            maxEmp = node;
        }
        
        findHighestSalary(node->leftChild, maxSalary, maxEmp);
        findHighestSalary(node->rightChild, maxSalary, maxEmp);
    }
    
    // Find employee with lowest salary
    void findLowestSalary(Employee* node, double& minSalary, Employee*& minEmp) {
        if (node == nullptr) return;
        
        if (node->salary < minSalary) {
            minSalary = node->salary;
            minEmp = node;
        }
        
        findLowestSalary(node->leftChild, minSalary, minEmp);
        findLowestSalary(node->rightChild, minSalary, minEmp);
    }
    
    // Find path from root to employee
    bool findPath(Employee* node, int id, vector<Employee*>& path) {
        if (node == nullptr) return false;
        
        path.push_back(node);
        
        if (node->employeeId == id) return true;
        
        if (findPath(node->leftChild, id, path) || 
            findPath(node->rightChild, id, path)) {
            return true;
        }
        
        path.pop_back();
        return false;
    }
    
    // Pre-order display with indentation
    void preOrderDisplay(Employee* node, int indent) {
        if (node == nullptr) return;
        
        for (int i = 0; i < indent; i++) cout << "  ";
        cout << "|- " << node->name << " (" << node->position 
             << ", $" << fixed << setprecision(0) << node->salary << ")" << endl;
        
        preOrderDisplay(node->leftChild, indent + 1);
        preOrderDisplay(node->rightChild, indent);  // Peers at same indent
    }
    
    // Post-order to calculate department totals
    double postOrderSalaryCalc(Employee* node, int depth = 0) {
        if (node == nullptr) return 0;
        
        double leftTotal = postOrderSalaryCalc(node->leftChild, depth + 1);
        double rightTotal = postOrderSalaryCalc(node->rightChild, depth);
        double total = node->salary + leftTotal + rightTotal;
        
        for (int i = 0; i < depth; i++) cout << "  ";
        cout << node->name << ": Own=$" << fixed << setprecision(0) << node->salary 
             << ", Department Total=$" << total << endl;
        
        return total;
    }
    
    // In-order collect employees with salary
    void inOrderCollect(Employee* node, vector<pair<double, Employee*>>& employees) {
        if (node == nullptr) return;
        
        inOrderCollect(node->leftChild, employees);
        employees.push_back({node->salary, node});
        inOrderCollect(node->rightChild, employees);
    }
    
    // Collect employees by level for average calculation
    void collectByLevel(Employee* node, int level, vector<vector<double>>& levelSalaries) {
        if (node == nullptr) return;
        
        if (level >= (int)levelSalaries.size()) {
            levelSalaries.resize(level + 1);
        }
        levelSalaries[level].push_back(node->salary);
        
        collectByLevel(node->leftChild, level + 1, levelSalaries);
        collectByLevel(node->rightChild, level, levelSalaries);  // Peer at same level
    }
    
    // Delete subtree
    void deleteSubtree(Employee* node) {
        if (node == nullptr) return;
        deleteSubtree(node->leftChild);
        deleteSubtree(node->rightChild);
        delete node;
    }
    
public:
    OrganizationTree() : root(nullptr) {}
    
    ~OrganizationTree() {
        deleteSubtree(root);
    }
    
    // Add CEO (root)
    void addCEO(int id, const string& name, double salary) {
        if (root == nullptr) {
            root = new Employee(id, name, "CEO", salary);
            cout << "CEO '" << name << "' added to organization." << endl;
        } else {
            cout << "CEO already exists!" << endl;
        }
    }
    
    // Add subordinate (left child)
    bool addSubordinate(int managerId, int newId, const string& name, 
                        const string& position, double salary) {
        Employee* manager = findEmployee(root, managerId);
        if (manager == nullptr) {
            cout << "Manager with ID " << managerId << " not found!" << endl;
            return false;
        }
        
        if (manager->leftChild == nullptr) {
            manager->leftChild = new Employee(newId, name, position, salary);
        } else {
            // Add as peer to existing subordinate
            Employee* current = manager->leftChild;
            while (current->rightChild != nullptr) {
                current = current->rightChild;
            }
            current->rightChild = new Employee(newId, name, position, salary);
        }
        
        cout << name << " (" << position << ") added under " << manager->name << endl;
        return true;
    }
    
    // Calculate total salary budget for department
    double getTotalSalaryBudget(int managerId) {
        Employee* manager = findEmployee(root, managerId);
        if (manager == nullptr) {
            cout << "Employee not found!" << endl;
            return 0;
        }
        return calculateTotalSalary(manager);
    }
    
    // Find highest paid employee
    Employee* getHighestPaid() {
        if (root == nullptr) return nullptr;
        
        double maxSalary = -1;
        Employee* maxEmp = nullptr;
        findHighestSalary(root, maxSalary, maxEmp);
        return maxEmp;
    }
    
    // Find lowest paid employee
    Employee* getLowestPaid() {
        if (root == nullptr) return nullptr;
        
        double minSalary = INT_MAX;
        Employee* minEmp = nullptr;
        findLowestSalary(root, minSalary, minEmp);
        return minEmp;
    }
    
    // Get reporting chain from employee to CEO
    vector<Employee*> getReportingChain(int employeeId) {
        vector<Employee*> path;
        findPath(root, employeeId, path);
        return path;
    }
    
    // Move employee to new manager (restructure)
    bool moveEmployee(int employeeId, int newManagerId) {
        if (employeeId == root->employeeId) {
            cout << "Cannot move CEO!" << endl;
            return false;
        }
        
        Employee* emp = findEmployee(root, employeeId);
        Employee* newManager = findEmployee(root, newManagerId);
        Employee* oldParent = findParent(root, employeeId);
        
        if (!emp || !newManager || !oldParent) {
            cout << "Employee or manager not found!" << endl;
            return false;
        }
        
        // Remove from old position
        if (oldParent->leftChild && oldParent->leftChild->employeeId == employeeId) {
            oldParent->leftChild = emp->rightChild;
        } else {
            Employee* prev = oldParent->leftChild;
            while (prev && prev->rightChild && prev->rightChild->employeeId != employeeId) {
                prev = prev->rightChild;
            }
            if (prev && prev->rightChild) {
                prev->rightChild = emp->rightChild;
            }
        }
        
        // Reset peer pointer
        emp->rightChild = nullptr;
        
        // Add to new manager
        if (newManager->leftChild == nullptr) {
            newManager->leftChild = emp;
        } else {
            Employee* current = newManager->leftChild;
            while (current->rightChild != nullptr) {
                current = current->rightChild;
            }
            current->rightChild = emp;
        }
        
        cout << emp->name << " moved under " << newManager->name << endl;
        return true;
    }
    
    // 1. Pre-order traversal - org chart with indentation
    void displayPreOrder() {
        cout << "\n=== Pre-order Traversal (Organization Chart) ===" << endl;
        preOrderDisplay(root, 0);
    }
    
    // 2. Post-order traversal - salary calculations bottom-up
    void displayPostOrder() {
        cout << "\n=== Post-order Traversal (Salary Calculations) ===" << endl;
        postOrderSalaryCalc(root);
    }
    
    // Average salary per level
    void displayAverageSalaryPerLevel() {
        cout << "\n=== Average Salary Per Level ===" << endl;
        vector<vector<double>> levelSalaries;
        collectByLevel(root, 0, levelSalaries);
        
        for (size_t i = 0; i < levelSalaries.size(); i++) {
            double sum = 0;
            for (double sal : levelSalaries[i]) sum += sal;
            double avg = levelSalaries[i].empty() ? 0 : sum / levelSalaries[i].size();
            cout << "Level " << i << ": $" << fixed << setprecision(0) << avg 
                 << " (avg of " << levelSalaries[i].size() << " employees)" << endl;
        }
    }
    
    // 3. In-order traversal - employees sorted by salary (low to high)
    void displayInOrderLowToHigh() {
        cout << "\n=== In-order Traversal (Salary: Low to High) ===" << endl;
        vector<pair<double, Employee*>> employees;
        inOrderCollect(root, employees);
        
        sort(employees.begin(), employees.end());
        
        for (const auto& emp : employees) {
            cout << emp.second->name << " (" << emp.second->position 
                 << "): $" << fixed << setprecision(0) << emp.first << endl;
        }
    }
    
    // 4. Reverse in-order - employees sorted by salary (high to low)
    void displayReverseInOrder() {
        cout << "\n=== Reverse In-order Traversal (Salary: High to Low) ===" << endl;
        vector<pair<double, Employee*>> employees;
        inOrderCollect(root, employees);
        
        sort(employees.begin(), employees.end(), greater<pair<double, Employee*>>());
        
        for (const auto& emp : employees) {
            cout << emp.second->name << " (" << emp.second->position 
                 << "): $" << fixed << setprecision(0) << emp.first << endl;
        }
    }
    
    // 5. Level-order traversal - by hierarchy level
    void displayLevelOrder() {
        cout << "\n=== Level-order Traversal (By Hierarchy) ===" << endl;
        if (root == nullptr) return;
        
        queue<pair<Employee*, int>> q;
        q.push({root, 0});
        int currentLevel = -1;
        
        while (!q.empty()) {
            Employee* emp = q.front().first;
            int level = q.front().second;
            q.pop();
            
            if (level != currentLevel) {
                if (currentLevel != -1) cout << endl;
                cout << "Level " << level << ": ";
                currentLevel = level;
            } else {
                cout << " | ";
            }
            
            cout << emp->name << "(" << emp->position << ")";
            
            if (emp->leftChild) q.push({emp->leftChild, level + 1});
            if (emp->rightChild) q.push({emp->rightChild, level});
        }
        cout << endl;
    }
};

int main() {
    OrganizationTree org;
    
    // Build organizational hierarchy
    org.addCEO(1, "John Smith", 500000);
    
    // Department Heads (direct reports to CEO)
    org.addSubordinate(1, 2, "Alice Johnson", "VP Engineering", 350000);
    org.addSubordinate(1, 3, "Bob Williams", "VP Sales", 320000);
    org.addSubordinate(1, 4, "Carol Davis", "VP HR", 280000);
    
    // Engineering Department
    org.addSubordinate(2, 5, "David Brown", "Engineering Manager", 180000);
    org.addSubordinate(2, 6, "Eve Wilson", "QA Manager", 160000);
    
    // Under Engineering Manager
    org.addSubordinate(5, 7, "Frank Miller", "Team Lead", 120000);
    org.addSubordinate(5, 8, "Grace Lee", "Senior Developer", 110000);
    
    // Under Team Lead
    org.addSubordinate(7, 9, "Henry Chen", "Developer", 85000);
    org.addSubordinate(7, 10, "Ivy Wang", "Developer", 80000);
    
    // Sales Department
    org.addSubordinate(3, 11, "Jack Taylor", "Sales Manager", 150000);
    org.addSubordinate(11, 12, "Kate Anderson", "Sales Rep", 75000);
    org.addSubordinate(11, 13, "Leo Martinez", "Sales Rep", 72000);
    
    // HR Department
    org.addSubordinate(4, 14, "Mary Thomas", "HR Manager", 130000);
    org.addSubordinate(14, 15, "Nick Jackson", "Recruiter", 65000);
    
    // Display all traversals
    org.displayPreOrder();
    org.displayPostOrder();
    org.displayAverageSalaryPerLevel();
    org.displayInOrderLowToHigh();
    org.displayReverseInOrder();
    org.displayLevelOrder();
    
    // Additional operations
    cout << "\n=== Additional Operations ===" << endl;
    
    cout << "\nTotal salary budget for Engineering (ID 2): $" 
         << fixed << setprecision(0) << org.getTotalSalaryBudget(2) << endl;
    
    Employee* highest = org.getHighestPaid();
    if (highest) {
        cout << "Highest paid: " << highest->name << " ($" << highest->salary << ")" << endl;
    }
    
    Employee* lowest = org.getLowestPaid();
    if (lowest) {
        cout << "Lowest paid: " << lowest->name << " ($" << lowest->salary << ")" << endl;
    }
    
    cout << "\nReporting chain for Ivy Wang (ID 10):" << endl;
    vector<Employee*> chain = org.getReportingChain(10);
    for (size_t i = 0; i < chain.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << chain[i]->name;
    }
    cout << endl;
    
    // Demonstrate restructuring
    cout << "\n=== Restructuring: Moving Grace Lee under QA Manager ===" << endl;
    org.moveEmployee(8, 6);
    org.displayPreOrder();
    
    return 0;
}
