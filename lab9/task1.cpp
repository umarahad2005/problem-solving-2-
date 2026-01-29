/*
 * Lab 9 - Task 1: Online Store Category Hierarchy
 * Binary tree for product categories with traversals
 */

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct CategoryNode {
    string categoryName;
    int productCount;
    CategoryNode* leftChild;   // More specific subcategory
    CategoryNode* rightChild;  // Alternative/parallel category at same level
    
    CategoryNode(string name, int count = 0) 
        : categoryName(name), productCount(count), leftChild(nullptr), rightChild(nullptr) {}
};

class ProductCategoryTree {
private:
    CategoryNode* root;
    
    // Helper to find a category by name
    CategoryNode* findCategory(CategoryNode* node, const string& name) {
        if (node == nullptr) return nullptr;
        if (node->categoryName == name) return node;
        
        CategoryNode* found = findCategory(node->leftChild, name);
        if (found) return found;
        return findCategory(node->rightChild, name);
    }
    
    // Helper to calculate total products in subtree
    int calculateTotalProducts(CategoryNode* node) {
        if (node == nullptr) return 0;
        return node->productCount + 
               calculateTotalProducts(node->leftChild) + 
               calculateTotalProducts(node->rightChild);
    }
    
    // Helper to find deepest category
    void findDeepest(CategoryNode* node, int depth, int& maxDepth, string& deepestName) {
        if (node == nullptr) return;
        
        if (depth > maxDepth) {
            maxDepth = depth;
            deepestName = node->categoryName;
        }
        
        findDeepest(node->leftChild, depth + 1, maxDepth, deepestName);
        findDeepest(node->rightChild, depth + 1, maxDepth, deepestName);
    }
    
    // Helper to get leaf categories
    void getLeafCategories(CategoryNode* node, vector<string>& leaves) {
        if (node == nullptr) return;
        
        if (node->leftChild == nullptr && node->rightChild == nullptr) {
            leaves.push_back(node->categoryName);
            return;
        }
        
        getLeafCategories(node->leftChild, leaves);
        getLeafCategories(node->rightChild, leaves);
    }
    
    // Pre-order traversal with indentation
    void preOrderDisplay(CategoryNode* node, int indent) {
        if (node == nullptr) return;
        
        for (int i = 0; i < indent; i++) cout << "  ";
        cout << "|- " << node->categoryName << " (" << node->productCount << " products)" << endl;
        
        preOrderDisplay(node->leftChild, indent + 1);
        preOrderDisplay(node->rightChild, indent + 1);
    }
    
    // In-order traversal to collect categories
    void inOrderCollect(CategoryNode* node, vector<pair<string, int>>& categories) {
        if (node == nullptr) return;
        
        inOrderCollect(node->leftChild, categories);
        categories.push_back({node->categoryName, node->productCount});
        inOrderCollect(node->rightChild, categories);
    }
    
    // Post-order traversal to calculate totals (bottom-up)
    int postOrderCalculate(CategoryNode* node) {
        if (node == nullptr) return 0;
        
        int leftTotal = postOrderCalculate(node->leftChild);
        int rightTotal = postOrderCalculate(node->rightChild);
        int total = node->productCount + leftTotal + rightTotal;
        
        cout << node->categoryName << ": Own=" << node->productCount 
             << ", Subtree Total=" << total << endl;
        
        return total;
    }
    
    // Helper to delete tree
    void deleteTree(CategoryNode* node) {
        if (node == nullptr) return;
        deleteTree(node->leftChild);
        deleteTree(node->rightChild);
        delete node;
    }
    
public:
    ProductCategoryTree() : root(nullptr) {}
    
    ~ProductCategoryTree() {
        deleteTree(root);
    }
    
    // Add root category
    void addRoot(const string& name, int productCount = 0) {
        if (root == nullptr) {
            root = new CategoryNode(name, productCount);
            cout << "Root category '" << name << "' added." << endl;
        } else {
            cout << "Root already exists!" << endl;
        }
    }
    
    // Add subcategory (left child - more specific)
    bool addSubcategory(const string& parentName, const string& newName, int productCount = 0) {
        CategoryNode* parent = findCategory(root, parentName);
        if (parent == nullptr) {
            cout << "Parent category '" << parentName << "' not found!" << endl;
            return false;
        }
        
        if (parent->leftChild == nullptr) {
            parent->leftChild = new CategoryNode(newName, productCount);
            cout << "Subcategory '" << newName << "' added under '" << parentName << "'." << endl;
            return true;
        } else {
            // Add as parallel category to existing left child
            CategoryNode* current = parent->leftChild;
            while (current->rightChild != nullptr) {
                current = current->rightChild;
            }
            current->rightChild = new CategoryNode(newName, productCount);
            cout << "Parallel category '" << newName << "' added alongside siblings under '" << parentName << "'." << endl;
            return true;
        }
    }
    
    // Calculate total products in category and subcategories
    int getTotalProducts(const string& categoryName) {
        CategoryNode* node = findCategory(root, categoryName);
        if (node == nullptr) {
            cout << "Category not found!" << endl;
            return 0;
        }
        return calculateTotalProducts(node);
    }
    
    // Find deepest category
    string findDeepestCategory() {
        if (root == nullptr) return "";
        
        int maxDepth = -1;
        string deepestName;
        findDeepest(root, 0, maxDepth, deepestName);
        return deepestName;
    }
    
    // Get all leaf categories
    vector<string> getLeafCategories() {
        vector<string> leaves;
        getLeafCategories(root, leaves);
        return leaves;
    }
    
    // 1. Pre-order traversal - display category structure with indentation
    void displayPreOrder() {
        cout << "\n=== Pre-order Traversal (Category Structure) ===" << endl;
        preOrderDisplay(root, 0);
    }
    
    // 2. In-order traversal - list categories alphabetically with product counts
    void displayInOrder() {
        cout << "\n=== In-order Traversal (Alphabetically Sorted) ===" << endl;
        vector<pair<string, int>> categories;
        inOrderCollect(root, categories);
        
        // Sort alphabetically
        sort(categories.begin(), categories.end());
        
        for (const auto& cat : categories) {
            cout << cat.first << ": " << cat.second << " products" << endl;
        }
    }
    
    // 3. Post-order traversal - calculate total products bottom-up
    void displayPostOrder() {
        cout << "\n=== Post-order Traversal (Bottom-up Product Calculation) ===" << endl;
        postOrderCalculate(root);
    }
    
    // 4. Level-order traversal - display categories by depth/level
    void displayLevelOrder() {
        cout << "\n=== Level-order Traversal (By Depth) ===" << endl;
        if (root == nullptr) return;
        
        queue<pair<CategoryNode*, int>> q;
        q.push({root, 0});
        int currentLevel = -1;
        
        while (!q.empty()) {
            CategoryNode* node = q.front().first;
            int level = q.front().second;
            q.pop();
            
            if (level != currentLevel) {
                if (currentLevel != -1) cout << endl;
                cout << "Level " << level << ": ";
                currentLevel = level;
            } else {
                cout << ", ";
            }
            
            cout << node->categoryName << "(" << node->productCount << ")";
            
            if (node->leftChild) q.push({node->leftChild, level + 1});
            if (node->rightChild) q.push({node->rightChild, level + 1});
        }
        cout << endl;
    }
};

int main() {
    ProductCategoryTree store;
    
    // Build the category hierarchy as specified
    store.addRoot("Electronics", 0);
    
    // First level subcategories
    store.addSubcategory("Electronics", "Mobile Phones", 0);
    store.addSubcategory("Electronics", "Computers", 0);
    store.addSubcategory("Electronics", "Home Appliances", 0);
    
    // Mobile Phones subcategories
    store.addSubcategory("Mobile Phones", "Smartphones", 150);
    store.addSubcategory("Mobile Phones", "Feature Phones", 50);
    
    // Computers subcategories
    store.addSubcategory("Computers", "Laptops", 200);
    store.addSubcategory("Computers", "Desktops", 100);
    
    // Desktops subcategories
    store.addSubcategory("Desktops", "Gaming PCs", 75);
    store.addSubcategory("Desktops", "Workstations", 25);
    
    // Home Appliances subcategories
    store.addSubcategory("Home Appliances", "Refrigerators", 80);
    store.addSubcategory("Home Appliances", "Washing Machines", 60);
    
    // Demonstrate all traversals
    store.displayPreOrder();
    store.displayInOrder();
    store.displayPostOrder();
    store.displayLevelOrder();
    
    // Additional operations
    cout << "\n=== Additional Operations ===" << endl;
    
    cout << "\nTotal products in 'Computers': " 
         << store.getTotalProducts("Computers") << endl;
    
    cout << "Total products in 'Electronics': " 
         << store.getTotalProducts("Electronics") << endl;
    
    cout << "\nDeepest category: " << store.findDeepestCategory() << endl;
    
    cout << "\nLeaf categories (no subcategories):" << endl;
    vector<string> leaves = store.getLeafCategories();
    for (const string& leaf : leaves) {
        cout << "  - " << leaf << endl;
    }
    
    return 0;
}
