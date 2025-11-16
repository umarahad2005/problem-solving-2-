#include<iostream>
#include<string>
using namespace std;

class DocumentState {
public:
    string content;
    DocumentState* prev;
    DocumentState* next;
    
    DocumentState(string c) {
        content = c;
        prev = NULL;
        next = NULL;
    }
};

class TextEditor {
    DocumentState* current;
    DocumentState* head;
    int maxHistorySize;
    int currentSize;
    
public:
    TextEditor(int maxSize = 10) {
        current = NULL;
        head = NULL;
        maxHistorySize = maxSize;
        currentSize = 0;
    }
    
    // Save document state
    void saveState(string content) {
        DocumentState* newState = new DocumentState(content);
        
        if(head == NULL) {
            head = newState;
            current = newState;
            currentSize = 1;
            cout << "Initial state saved" << endl;
            return;
        }
        
        // Clear redo stack (everything after current)
        if(current->next != NULL) {
            DocumentState* temp = current->next;
            while(temp != NULL) {
                DocumentState* toDelete = temp;
                temp = temp->next;
                delete toDelete;
                currentSize--;
            }
            current->next = NULL;
        }
        
        // Add new state
        current->next = newState;
        newState->prev = current;
        current = newState;
        currentSize++;
        
        // Check if exceeded max size
        if(currentSize > maxHistorySize) {
            DocumentState* toDelete = head;
            head = head->next;
            head->prev = NULL;
            delete toDelete;
            currentSize--;
        }
        
        cout << "State saved (History: " << currentSize << "/" << maxHistorySize << ")" << endl;
    }
    
    // Undo operation
    void undo() {
        if(current == NULL) {
            cout << "Nothing to undo" << endl;
            return;
        }
        
        if(current->prev == NULL) {
            cout << "Already at oldest state" << endl;
            return;
        }
        
        current = current->prev;
        cout << "Undo successful" << endl;
        cout << "Current content: " << current->content << endl;
    }
    
    // Redo operation
    void redo() {
        if(current == NULL) {
            cout << "Nothing to redo" << endl;
            return;
        }
        
        if(current->next == NULL) {
            cout << "Already at newest state" << endl;
            return;
        }
        
        current = current->next;
        cout << "Redo successful" << endl;
        cout << "Current content: " << current->content << endl;
    }
    
    // Get current content
    string getCurrentContent() {
        if(current == NULL) {
            return "";
        }
        return current->content;
    }
    
    // Display history
    void displayHistory() {
        if(head == NULL) {
            cout << "No history available" << endl;
            return;
        }
        
        cout << "\n=== Document History ===" << endl;
        DocumentState* temp = head;
        int count = 1;
        
        while(temp != NULL) {
            if(temp == current) {
                cout << count++ << ". " << temp->content << " <- CURRENT" << endl;
            } else {
                cout << count++ << ". " << temp->content << endl;
            }
            temp = temp->next;
        }
    }
    
    // Clear all history
    void clearHistory() {
        while(head != NULL) {
            DocumentState* toDelete = head;
            head = head->next;
            delete toDelete;
        }
        current = NULL;
        currentSize = 0;
        cout << "History cleared" << endl;
    }
};

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    
    TextEditor editor(5); // Max 5 states in history
    int choice;
    
    while(true) {
        cout << "\n=== Text Editor (Undo/Redo) ===" << endl;
        cout << "1. Type/Edit Text" << endl;
        cout << "2. Undo" << endl;
        cout << "3. Redo" << endl;
        cout << "4. Show Current Content" << endl;
        cout << "5. Show History" << endl;
        cout << "6. Clear History" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) {
            string content;
            cout << "Enter text: ";
            getline(cin, content);
            editor.saveState(content);
        }
        else if(choice == 2) {
            editor.undo();
        }
        else if(choice == 3) {
            editor.redo();
        }
        else if(choice == 4) {
            string current = editor.getCurrentContent();
            if(current.empty()) {
                cout << "Document is empty" << endl;
            } else {
                cout << "Current content: " << current << endl;
            }
        }
        else if(choice == 5) {
            editor.displayHistory();
        }
        else if(choice == 6) {
            editor.clearHistory();
        }
        else if(choice == 7) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
