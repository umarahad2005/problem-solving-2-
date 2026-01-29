#include<iostream>
#include<string>
using namespace std;

// Operation types
enum OperationType { DRAW, ERASE, RESIZE, COLOR_CHANGE, GROUP };

// Single operation
struct Operation {
    OperationType type;
    string description;
    string details;      // Additional info like color, size, etc.
    bool isGrouped;      // Part of a group
    int groupId;         // Group identifier
    
    Operation() : type(DRAW), description(""), details(""), isGrouped(false), groupId(0) {}
    Operation(OperationType t, string desc, string det) 
        : type(t), description(desc), details(det), isGrouped(false), groupId(0) {}
};

// Operation Stack for undo/redo
class OperationStack {
    Operation stack[100];
    int top;
    
public:
    OperationStack() : top(-1) {}
    
    bool isEmpty() { return top == -1; }
    bool isFull() { return top == 99; }
    int size() { return top + 1; }
    
    void push(Operation op) {
        if(!isFull()) stack[++top] = op;
    }
    
    Operation pop() {
        if(!isEmpty()) return stack[top--];
        return Operation();
    }
    
    Operation peek() {
        if(!isEmpty()) return stack[top];
        return Operation();
    }
    
    void clear() { top = -1; }
    
    // Pop all operations with same group ID
    void popGroup(int groupId) {
        while(!isEmpty() && stack[top].groupId == groupId) {
            top--;
        }
    }
    
    // Get the group ID of top operation
    int getTopGroupId() {
        if(!isEmpty()) return stack[top].groupId;
        return -1;
    }
};

// Graphic Design Undo/Redo System
class UndoRedoSystem {
    OperationStack undoStack;     // Operations that can be undone
    OperationStack redoStack;     // Operations that can be redone
    int operationCounter;
    int groupCounter;
    bool isGrouping;              // Currently creating a group
    int currentGroupId;
    
    string typeToString(OperationType t) {
        switch(t) {
            case DRAW: return "Draw";
            case ERASE: return "Erase";
            case RESIZE: return "Resize";
            case COLOR_CHANGE: return "Color Change";
            case GROUP: return "Group";
            default: return "Unknown";
        }
    }
    
public:
    UndoRedoSystem() : operationCounter(0), groupCounter(0), isGrouping(false), currentGroupId(0) {}
    
    // Perform a new operation
    void performOperation(OperationType type, string description, string details) {
        Operation op(type, description, details);
        operationCounter++;
        
        if(isGrouping) {
            op.isGrouped = true;
            op.groupId = currentGroupId;
        }
        
        undoStack.push(op);
        redoStack.clear();  // Clear redo stack on new operation
        
        cout << "Performed: " << typeToString(type) << " - " << description;
        if(!details.empty()) cout << " (" << details << ")";
        if(isGrouping) cout << " [Group " << currentGroupId << "]";
        cout << endl;
    }
    
    // Start grouping operations
    void startGroup() {
        if(isGrouping) {
            cout << "Already in a group! End current group first." << endl;
            return;
        }
        isGrouping = true;
        currentGroupId = ++groupCounter;
        cout << "Started operation group " << currentGroupId << endl;
    }
    
    // End grouping operations
    void endGroup() {
        if(!isGrouping) {
            cout << "Not currently grouping!" << endl;
            return;
        }
        isGrouping = false;
        cout << "Ended operation group " << currentGroupId << endl;
    }
    
    // Undo last operation (or group)
    void undo() {
        if(undoStack.isEmpty()) {
            cout << "Nothing to undo!" << endl;
            return;
        }
        
        Operation top = undoStack.peek();
        
        if(top.isGrouped) {
            // Undo entire group
            int groupId = top.groupId;
            cout << "Undoing group " << groupId << ":" << endl;
            
            while(!undoStack.isEmpty() && undoStack.peek().groupId == groupId) {
                Operation op = undoStack.pop();
                redoStack.push(op);
                cout << "  - " << typeToString(op.type) << ": " << op.description << endl;
            }
        } else {
            // Undo single operation
            Operation op = undoStack.pop();
            redoStack.push(op);
            cout << "Undone: " << typeToString(op.type) << " - " << op.description << endl;
        }
    }
    
    // Redo last undone operation (or group)
    void redo() {
        if(redoStack.isEmpty()) {
            cout << "Nothing to redo!" << endl;
            return;
        }
        
        Operation top = redoStack.peek();
        
        if(top.isGrouped) {
            // Redo entire group
            int groupId = top.groupId;
            cout << "Redoing group " << groupId << ":" << endl;
            
            while(!redoStack.isEmpty() && redoStack.peek().groupId == groupId) {
                Operation op = redoStack.pop();
                undoStack.push(op);
                cout << "  + " << typeToString(op.type) << ": " << op.description << endl;
            }
        } else {
            // Redo single operation
            Operation op = redoStack.pop();
            undoStack.push(op);
            cout << "Redone: " << typeToString(op.type) << " - " << op.description << endl;
        }
    }
    
    // Multiple undos
    void multipleUndo(int count) {
        cout << "Performing " << count << " undos:" << endl;
        for(int i = 0; i < count && !undoStack.isEmpty(); i++) {
            undo();
        }
    }
    
    // Clear entire history
    void clearHistory() {
        undoStack.clear();
        redoStack.clear();
        operationCounter = 0;
        groupCounter = 0;
        isGrouping = false;
        cout << "History cleared!" << endl;
    }
    
    // Display history
    void displayHistory() {
        cout << "\n=== OPERATION HISTORY ===" << endl;
        cout << "Undo stack: " << undoStack.size() << " operations" << endl;
        cout << "Redo stack: " << redoStack.size() << " operations" << endl;
        
        if(isGrouping) {
            cout << "[Currently grouping - Group " << currentGroupId << "]" << endl;
        }
    }
    
    // Demo function - common operations
    void drawShape(string shape) {
        performOperation(DRAW, "Draw " + shape, "");
    }
    
    void eraseArea(string area) {
        performOperation(ERASE, "Erase " + area, "");
    }
    
    void resizeElement(string element, string newSize) {
        performOperation(RESIZE, "Resize " + element, newSize);
    }
    
    void changeColor(string element, string color) {
        performOperation(COLOR_CHANGE, "Change color of " + element, color);
    }
};

int main() {
    cout << "welcome to world of programming with umar usmani sap : 60199" << endl;
    cout << "Assignment 2 Task 4: Graphic Design Undo/Redo System" << endl;
    cout << "=====================================================" << endl;
    
    UndoRedoSystem editor;
    int choice;
    
    while(true) {
        cout << "\n=== GRAPHIC EDITOR ===" << endl;
        cout << "1. Draw Shape" << endl;
        cout << "2. Erase Area" << endl;
        cout << "3. Resize Element" << endl;
        cout << "4. Change Color" << endl;
        cout << "5. Start Group" << endl;
        cout << "6. End Group" << endl;
        cout << "7. Undo" << endl;
        cout << "8. Multiple Undo" << endl;
        cout << "9. Redo" << endl;
        cout << "10. Display History" << endl;
        cout << "11. Clear History" << endl;
        cout << "12. Demo (Auto-add operations)" << endl;
        cout << "13. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) {
            string shape;
            cout << "Shape name (circle/rectangle/line/etc): ";
            getline(cin, shape);
            editor.drawShape(shape);
        }
        else if(choice == 2) {
            string area;
            cout << "Area to erase: ";
            getline(cin, area);
            editor.eraseArea(area);
        }
        else if(choice == 3) {
            string element, size;
            cout << "Element to resize: ";
            getline(cin, element);
            cout << "New size (e.g., 200x200): ";
            getline(cin, size);
            editor.resizeElement(element, size);
        }
        else if(choice == 4) {
            string element, color;
            cout << "Element to recolor: ";
            getline(cin, element);
            cout << "New color: ";
            getline(cin, color);
            editor.changeColor(element, color);
        }
        else if(choice == 5) {
            editor.startGroup();
        }
        else if(choice == 6) {
            editor.endGroup();
        }
        else if(choice == 7) {
            editor.undo();
        }
        else if(choice == 8) {
            int count;
            cout << "How many undos: ";
            cin >> count;
            editor.multipleUndo(count);
        }
        else if(choice == 9) {
            editor.redo();
        }
        else if(choice == 10) {
            editor.displayHistory();
        }
        else if(choice == 11) {
            editor.clearHistory();
        }
        else if(choice == 12) {
            cout << "\n--- Running Demo ---" << endl;
            editor.drawShape("circle");
            editor.changeColor("circle", "blue");
            
            editor.startGroup();
            editor.drawShape("rectangle");
            editor.changeColor("rectangle", "red");
            editor.resizeElement("rectangle", "100x50");
            editor.endGroup();
            
            editor.drawShape("line");
            
            cout << "\n--- Demo Complete ---" << endl;
            cout << "Try undoing - the grouped operations will undo together!" << endl;
        }
        else if(choice == 13) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
