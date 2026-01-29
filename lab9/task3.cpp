/*
 * Lab 9 - Task 3: Mathematical Expression Trees
 * Binary tree for expression evaluation and notation conversion
 */

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <cctype>
#include <sstream>
#include <vector>
using namespace std;

struct ExprNode {
    string value;       // Operator or operand
    bool isOperator;
    ExprNode* left;     // Left operand
    ExprNode* right;    // Right operand
    
    ExprNode(string val, bool isOp = false)
        : value(val), isOperator(isOp), left(nullptr), right(nullptr) {}
};

class ExpressionTree {
private:
    ExprNode* root;
    
    // Check if character is operator
    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }
    
    bool isOperator(const string& s) {
        return s.length() == 1 && isOperator(s[0]);
    }
    
    // Get operator precedence
    int precedence(char op) {
        if (op == '^') return 3;
        if (op == '*' || op == '/') return 2;
        if (op == '+' || op == '-') return 1;
        return 0;
    }
    
    // Evaluate operation
    double evaluate(double left, double right, char op) {
        switch (op) {
            case '+': return left + right;
            case '-': return left - right;
            case '*': return left * right;
            case '/': return right != 0 ? left / right : 0;
            case '^': return pow(left, right);
            default: return 0;
        }
    }
    
    // Recursive evaluation
    double evaluateTree(ExprNode* node) {
        if (node == nullptr) return 0;
        
        // Leaf node - operand
        if (!node->isOperator) {
            return stod(node->value);
        }
        
        // Internal node - operator
        double leftVal = evaluateTree(node->left);
        double rightVal = evaluateTree(node->right);
        return evaluate(leftVal, rightVal, node->value[0]);
    }
    
    // In-order traversal for infix notation
    void inOrderInfix(ExprNode* node, stringstream& ss, bool needParens = false) {
        if (node == nullptr) return;
        
        if (node->isOperator && needParens) ss << "(";
        
        inOrderInfix(node->left, ss, node->left && node->left->isOperator);
        ss << node->value;
        inOrderInfix(node->right, ss, node->right && node->right->isOperator);
        
        if (node->isOperator && needParens) ss << ")";
    }
    
    // Post-order traversal for postfix notation
    void postOrderPostfix(ExprNode* node, stringstream& ss) {
        if (node == nullptr) return;
        
        postOrderPostfix(node->left, ss);
        postOrderPostfix(node->right, ss);
        ss << node->value << " ";
    }
    
    // Pre-order traversal for prefix notation
    void preOrderPrefix(ExprNode* node, stringstream& ss) {
        if (node == nullptr) return;
        
        ss << node->value << " ";
        preOrderPrefix(node->left, ss);
        preOrderPrefix(node->right, ss);
    }
    
    // Deep copy of tree
    ExprNode* copyTree(ExprNode* node) {
        if (node == nullptr) return nullptr;
        
        ExprNode* newNode = new ExprNode(node->value, node->isOperator);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }
    
    // Simplify expression tree
    ExprNode* simplify(ExprNode* node) {
        if (node == nullptr) return nullptr;
        
        node->left = simplify(node->left);
        node->right = simplify(node->right);
        
        if (!node->isOperator) return node;
        
        char op = node->value[0];
        
        // x * 0 = 0 or 0 * x = 0
        if (op == '*') {
            if ((node->left && node->left->value == "0") ||
                (node->right && node->right->value == "0")) {
                deleteTree(node->left);
                deleteTree(node->right);
                node->left = node->right = nullptr;
                node->value = "0";
                node->isOperator = false;
                return node;
            }
            // x * 1 = x
            if (node->right && node->right->value == "1") {
                ExprNode* left = node->left;
                delete node->right;
                delete node;
                return left;
            }
            // 1 * x = x
            if (node->left && node->left->value == "1") {
                ExprNode* right = node->right;
                delete node->left;
                delete node;
                return right;
            }
        }
        
        // x + 0 = x or 0 + x = x
        if (op == '+') {
            if (node->right && node->right->value == "0") {
                ExprNode* left = node->left;
                delete node->right;
                delete node;
                return left;
            }
            if (node->left && node->left->value == "0") {
                ExprNode* right = node->right;
                delete node->left;
                delete node;
                return right;
            }
        }
        
        // x - 0 = x
        if (op == '-' && node->right && node->right->value == "0") {
            ExprNode* left = node->left;
            delete node->right;
            delete node;
            return left;
        }
        
        // x ^ 0 = 1
        if (op == '^' && node->right && node->right->value == "0") {
            deleteTree(node->left);
            deleteTree(node->right);
            node->left = node->right = nullptr;
            node->value = "1";
            node->isOperator = false;
            return node;
        }
        
        // x ^ 1 = x
        if (op == '^' && node->right && node->right->value == "1") {
            ExprNode* left = node->left;
            delete node->right;
            delete node;
            return left;
        }
        
        return node;
    }
    
    // Delete tree
    void deleteTree(ExprNode* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    
    // Tokenize expression
    vector<string> tokenize(const string& expr) {
        vector<string> tokens;
        string num;
        
        for (size_t i = 0; i < expr.length(); i++) {
            char c = expr[i];
            
            if (isspace(c)) {
                if (!num.empty()) {
                    tokens.push_back(num);
                    num.clear();
                }
                continue;
            }
            
            if (isdigit(c) || c == '.') {
                num += c;
            } else if (isalpha(c)) {
                if (!num.empty()) {
                    tokens.push_back(num);
                    num.clear();
                }
                tokens.push_back(string(1, c));  // Variable
            } else if (c == '(' || c == ')' || isOperator(c)) {
                if (!num.empty()) {
                    tokens.push_back(num);
                    num.clear();
                }
                tokens.push_back(string(1, c));
            }
        }
        
        if (!num.empty()) {
            tokens.push_back(num);
        }
        
        return tokens;
    }
    
public:
    ExpressionTree() : root(nullptr) {}
    
    ~ExpressionTree() {
        deleteTree(root);
    }
    
    // Build from postfix notation: "3 4 + 5 *"
    void buildFromPostfix(const string& postfix) {
        deleteTree(root);
        root = nullptr;
        
        stack<ExprNode*> nodeStack;
        vector<string> tokens = tokenize(postfix);
        
        for (const string& token : tokens) {
            if (isOperator(token)) {
                ExprNode* node = new ExprNode(token, true);
                node->right = nodeStack.top(); nodeStack.pop();
                node->left = nodeStack.top(); nodeStack.pop();
                nodeStack.push(node);
            } else {
                nodeStack.push(new ExprNode(token, false));
            }
        }
        
        if (!nodeStack.empty()) {
            root = nodeStack.top();
        }
        
        cout << "Tree built from postfix: " << postfix << endl;
    }
    
    // Build from prefix notation: "* + 3 4 5"
    void buildFromPrefix(const string& prefix) {
        deleteTree(root);
        root = nullptr;
        
        stack<ExprNode*> nodeStack;
        vector<string> tokens = tokenize(prefix);
        
        // Process right to left
        for (int i = tokens.size() - 1; i >= 0; i--) {
            const string& token = tokens[i];
            
            if (isOperator(token)) {
                ExprNode* node = new ExprNode(token, true);
                node->left = nodeStack.top(); nodeStack.pop();
                node->right = nodeStack.top(); nodeStack.pop();
                nodeStack.push(node);
            } else {
                nodeStack.push(new ExprNode(token, false));
            }
        }
        
        if (!nodeStack.empty()) {
            root = nodeStack.top();
        }
        
        cout << "Tree built from prefix: " << prefix << endl;
    }
    
    // Build from infix notation: "(3 + 4) * 5"
    void buildFromInfix(const string& infix) {
        // Convert infix to postfix first, then build
        vector<string> tokens = tokenize(infix);
        stack<string> opStack;
        stringstream postfix;
        
        for (const string& token : tokens) {
            if (token == "(") {
                opStack.push(token);
            } else if (token == ")") {
                while (!opStack.empty() && opStack.top() != "(") {
                    postfix << opStack.top() << " ";
                    opStack.pop();
                }
                if (!opStack.empty()) opStack.pop();  // Remove "("
            } else if (isOperator(token)) {
                while (!opStack.empty() && opStack.top() != "(" &&
                       precedence(opStack.top()[0]) >= precedence(token[0])) {
                    postfix << opStack.top() << " ";
                    opStack.pop();
                }
                opStack.push(token);
            } else {
                postfix << token << " ";
            }
        }
        
        while (!opStack.empty()) {
            postfix << opStack.top() << " ";
            opStack.pop();
        }
        
        cout << "Converted infix '" << infix << "' to postfix: " << postfix.str() << endl;
        buildFromPostfix(postfix.str());
    }
    
    // Evaluate expression
    double evaluate() {
        return evaluateTree(root);
    }
    
    // Simplify expression
    void simplifyExpression() {
        root = simplify(root);
        cout << "Expression simplified." << endl;
    }
    
    // Create deep copy
    ExpressionTree* copy() {
        ExpressionTree* newTree = new ExpressionTree();
        newTree->root = copyTree(root);
        return newTree;
    }
    
    // 1. In-order traversal - produce infix notation
    string toInfix() {
        stringstream ss;
        inOrderInfix(root, ss, false);
        return ss.str();
    }
    
    // 2. Post-order traversal - generate postfix notation
    string toPostfix() {
        stringstream ss;
        postOrderPostfix(root, ss);
        return ss.str();
    }
    
    // 3. Pre-order traversal - generate prefix notation
    string toPrefix() {
        stringstream ss;
        preOrderPrefix(root, ss);
        return ss.str();
    }
    
    // 4. Level-order traversal - display by operator precedence levels
    void displayLevelOrder() {
        cout << "\n=== Level-order Traversal (By Tree Levels) ===" << endl;
        if (root == nullptr) return;
        
        queue<pair<ExprNode*, int>> q;
        q.push({root, 0});
        int currentLevel = -1;
        
        while (!q.empty()) {
            ExprNode* node = q.front().first;
            int level = q.front().second;
            q.pop();
            
            if (level != currentLevel) {
                if (currentLevel != -1) cout << endl;
                cout << "Level " << level << ": ";
                currentLevel = level;
            } else {
                cout << " ";
            }
            
            cout << node->value;
            
            if (node->left) q.push({node->left, level + 1});
            if (node->right) q.push({node->right, level + 1});
        }
        cout << endl;
    }
    
    // Display tree structure
    void displayTree(ExprNode* node = nullptr, int indent = 0, bool isRoot = true) {
        if (isRoot) {
            cout << "\n=== Expression Tree Structure ===" << endl;
            node = root;
        }
        
        if (node == nullptr) return;
        
        displayTree(node->right, indent + 4, false);
        
        for (int i = 0; i < indent; i++) cout << " ";
        cout << node->value << endl;
        
        displayTree(node->left, indent + 4, false);
    }
};

// Differentiation helper class
class Differentiator {
public:
    static ExprNode* differentiate(ExprNode* node, const string& var) {
        if (node == nullptr) return nullptr;
        
        // Constant or different variable
        if (!node->isOperator) {
            if (node->value == var) {
                return new ExprNode("1", false);  // d/dx(x) = 1
            }
            return new ExprNode("0", false);  // d/dx(c) = 0
        }
        
        char op = node->value[0];
        
        // d/dx(u + v) = du + dv
        if (op == '+' || op == '-') {
            ExprNode* result = new ExprNode(node->value, true);
            result->left = differentiate(node->left, var);
            result->right = differentiate(node->right, var);
            return result;
        }
        
        // d/dx(u * v) = u*dv + v*du (product rule)
        if (op == '*') {
            ExprNode* result = new ExprNode("+", true);
            
            // u * dv
            ExprNode* left = new ExprNode("*", true);
            left->left = copyNode(node->left);
            left->right = differentiate(node->right, var);
            
            // v * du
            ExprNode* right = new ExprNode("*", true);
            right->left = copyNode(node->right);
            right->right = differentiate(node->left, var);
            
            result->left = left;
            result->right = right;
            return result;
        }
        
        // Simplified handling for other operators
        return new ExprNode("0", false);
    }
    
private:
    static ExprNode* copyNode(ExprNode* node) {
        if (node == nullptr) return nullptr;
        ExprNode* newNode = new ExprNode(node->value, node->isOperator);
        newNode->left = copyNode(node->left);
        newNode->right = copyNode(node->right);
        return newNode;
    }
};

int main() {
    ExpressionTree tree;
    
    // Example 1: (3 + 4) * 5
    cout << "=== Example 1: (3 + 4) * 5 ===" << endl;
    tree.buildFromInfix("(3 + 4) * 5");
    tree.displayTree();
    
    cout << "\nNotations:" << endl;
    cout << "Infix:   " << tree.toInfix() << endl;
    cout << "Postfix: " << tree.toPostfix() << endl;
    cout << "Prefix:  " << tree.toPrefix() << endl;
    cout << "Result:  " << tree.evaluate() << endl;
    
    tree.displayLevelOrder();
    
    // Example 2: Build from postfix
    cout << "\n\n=== Example 2: Build from postfix '3 4 + 5 *' ===" << endl;
    ExpressionTree tree2;
    tree2.buildFromPostfix("3 4 + 5 *");
    tree2.displayTree();
    cout << "Result: " << tree2.evaluate() << endl;
    
    // Example 3: Build from prefix
    cout << "\n\n=== Example 3: Build from prefix '^ 2 + 3 4' ===" << endl;
    ExpressionTree tree3;
    tree3.buildFromPrefix("^ 2 + 3 4");
    tree3.displayTree();
    cout << "Infix: " << tree3.toInfix() << endl;
    cout << "Result: 2^(3+4) = " << tree3.evaluate() << endl;
    
    // Example 4: Simplification
    cout << "\n\n=== Example 4: Simplification ===" << endl;
    ExpressionTree tree4;
    tree4.buildFromInfix("x * 0 + y * 1");
    cout << "Before: " << tree4.toInfix() << endl;
    tree4.simplifyExpression();
    cout << "After:  " << tree4.toInfix() << endl;
    
    // Example 5: More complex expression
    cout << "\n\n=== Example 5: Complex Expression (2 + 3) * (4 - 1) ===" << endl;
    ExpressionTree tree5;
    tree5.buildFromInfix("(2 + 3) * (4 - 1)");
    tree5.displayTree();
    cout << "\nNotations:" << endl;
    cout << "Infix:   " << tree5.toInfix() << endl;
    cout << "Postfix: " << tree5.toPostfix() << endl;
    cout << "Prefix:  " << tree5.toPrefix() << endl;
    cout << "Result:  " << tree5.evaluate() << endl;
    
    tree5.displayLevelOrder();
    
    // Example 6: Copy tree
    cout << "\n\n=== Example 6: Tree Copy ===" << endl;
    ExpressionTree* treeCopy = tree5.copy();
    cout << "Original: " << tree5.toInfix() << " = " << tree5.evaluate() << endl;
    cout << "Copy:     " << treeCopy->toInfix() << " = " << treeCopy->evaluate() << endl;
    delete treeCopy;
    
    return 0;
}
