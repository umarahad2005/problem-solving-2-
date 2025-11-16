#include<iostream>
#include<string>
using namespace std;

class WebPage {
public:
    string url;
    string domain;
    WebPage* next;
    
    WebPage(string u, string d) {
        url = u;
        domain = d;
        next = NULL;
    }
};

class BrowserHistory {
    WebPage* head;
    
public:
    BrowserHistory() {
        head = NULL;
    }
    
    // Add page to history
    void visitPage(string url, string domain) {
        WebPage* newPage = new WebPage(url, domain);
        
        if(head == NULL) {
            head = newPage;
        } else {
            WebPage* temp = head;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newPage;
        }
        cout << "Visited: " << url << endl;
    }
    
    // Navigate backward (display history in reverse)
    void navigateBackward() {
        if(head == NULL) {
            cout << "No history available" << endl;
            return;
        }
        
        // Count nodes
        int count = 0;
        WebPage* temp = head;
        while(temp != NULL) {
            count++;
            temp = temp->next;
        }
        
        // Display in reverse using array
        string* history = new string[count];
        temp = head;
        for(int i = 0; i < count; i++) {
            history[i] = temp->url;
            temp = temp->next;
        }
        
        cout << "\n=== Browsing History (Recent First) ===" << endl;
        for(int i = count - 1; i >= 0; i--) {
            cout << (count - i) << ". " << history[i] << endl;
        }
        delete[] history;
    }
    
    // Remove all entries from specific domain
    void removeByDomain(string domain) {
        if(head == NULL) {
            cout << "History is empty" << endl;
            return;
        }
        
        // Remove from head
        while(head != NULL && head->domain == domain) {
            WebPage* temp = head;
            head = head->next;
            delete temp;
        }
        
        if(head == NULL) {
            cout << "All history from " << domain << " removed" << endl;
            return;
        }
        
        // Remove from rest of list
        WebPage* temp = head;
        while(temp->next != NULL) {
            if(temp->next->domain == domain) {
                WebPage* toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
            } else {
                temp = temp->next;
            }
        }
        
        cout << "Removed all history from " << domain << endl;
    }
    
    // Clear recent N entries
    void clearRecentHistory(int n) {
        if(head == NULL) {
            cout << "History is empty" << endl;
            return;
        }
        
        // Count total entries
        int count = 0;
        WebPage* temp = head;
        while(temp != NULL) {
            count++;
            temp = temp->next;
        }
        
        if(n >= count) {
            // Clear all history
            while(head != NULL) {
                WebPage* toDelete = head;
                head = head->next;
                delete toDelete;
            }
            cout << "All history cleared" << endl;
            return;
        }
        
        // Navigate to node before entries to delete
        temp = head;
        for(int i = 0; i < count - n - 1; i++) {
            temp = temp->next;
        }
        
        // Delete last n nodes
        WebPage* current = temp->next;
        temp->next = NULL;
        
        while(current != NULL) {
            WebPage* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        
        cout << "Cleared last " << n << " entries" << endl;
    }
    
    // Detect circular reference
    bool detectCircular() {
        if(head == NULL) {
            return false;
        }
        
        WebPage* slow = head;
        WebPage* fast = head;
        
        while(fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            
            if(slow == fast) {
                return true;
            }
        }
        
        return false;
    }
    
    // Display history
    void displayHistory() {
        if(head == NULL) {
            cout << "No history available" << endl;
            return;
        }
        
        cout << "\n=== Browser History ===" << endl;
        WebPage* temp = head;
        int count = 1;
        
        while(temp != NULL) {
            cout << count++ << ". " << temp->url << " [" << temp->domain << "]" << endl;
            temp = temp->next;
        }
    }
};

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    
    BrowserHistory browser;
    int choice;
    
    while(true) {
        cout << "\n=== Browser History Manager ===" << endl;
        cout << "1. Visit Page" << endl;
        cout << "2. Navigate Backward (View History)" << endl;
        cout << "3. Remove Domain History" << endl;
        cout << "4. Clear Recent History" << endl;
        cout << "5. Check for Circular Reference" << endl;
        cout << "6. Display All History" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) {
            string url, domain;
            cout << "Enter URL: ";
            getline(cin, url);
            cout << "Enter domain: ";
            getline(cin, domain);
            browser.visitPage(url, domain);
        }
        else if(choice == 2) {
            browser.navigateBackward();
        }
        else if(choice == 3) {
            string domain;
            cout << "Enter domain to remove: ";
            getline(cin, domain);
            browser.removeByDomain(domain);
        }
        else if(choice == 4) {
            int n;
            cout << "Enter number of recent entries to clear: ";
            cin >> n;
            browser.clearRecentHistory(n);
        }
        else if(choice == 5) {
            if(browser.detectCircular()) {
                cout << "Circular reference detected!" << endl;
            } else {
                cout << "No circular reference found" << endl;
            }
        }
        else if(choice == 6) {
            browser.displayHistory();
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
