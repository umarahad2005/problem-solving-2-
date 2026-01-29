#include<iostream>
#include<string>
using namespace std;

// Page structure for history
struct Page {
    string url;
    string title;
    
    Page() : url(""), title("") {}
    Page(string u, string t) : url(u), title(t) {}
};

// Stack implementation
class PageStack {
    Page stack[100];
    int top;
    
public:
    PageStack() : top(-1) {}
    
    bool isEmpty() { return top == -1; }
    bool isFull() { return top == 99; }
    int size() { return top + 1; }
    
    void push(Page p) {
        if(!isFull()) stack[++top] = p;
    }
    
    Page pop() {
        if(!isEmpty()) return stack[top--];
        return Page();
    }
    
    Page peek() {
        if(!isEmpty()) return stack[top];
        return Page();
    }
    
    void clear() { top = -1; }
};

// Closed Tabs Queue (circular for last 10)
class ClosedTabsQueue {
    Page queue[10];
    int front, rear, count;
    
public:
    ClosedTabsQueue() : front(0), rear(-1), count(0) {}
    
    bool isEmpty() { return count == 0; }
    
    void addClosedTab(Page p) {
        rear = (rear + 1) % 10;
        queue[rear] = p;
        if(count < 10) count++;
        else front = (front + 1) % 10;
    }
    
    Page reopenLastClosed() {
        if(isEmpty()) return Page();
        Page p = queue[rear];
        rear = (rear - 1 + 10) % 10;
        count--;
        return p;
    }
    
    void display() {
        if(isEmpty()) {
            cout << "No recently closed tabs." << endl;
            return;
        }
        cout << "Recently Closed Tabs (newest first):" << endl;
        int idx = rear;
        for(int i = 0; i < count; i++) {
            cout << (i+1) << ". " << queue[idx].title << " - " << queue[idx].url << endl;
            idx = (idx - 1 + 10) % 10;
        }
    }
    
    int getCount() { return count; }
};

// Tab structure
struct Tab {
    int tabId;
    string title;
    Page currentPage;
    PageStack backHistory;
    PageStack forwardHistory;
    int accessCount;
    int lastAccess;
    
    Tab() : tabId(0), title(""), accessCount(0), lastAccess(0) {}
};

// Browser Tab Manager
class BrowserTabManager {
    Tab tabs[50];
    int tabCount;
    int activeTab;
    int tabIdCounter;
    int accessCounter;
    ClosedTabsQueue closedTabs;
    
public:
    BrowserTabManager() : tabCount(0), activeTab(-1), tabIdCounter(0), accessCounter(0) {}
    
    void openNewTab(string url, string title) {
        if(tabCount >= 50) {
            cout << "Maximum tabs reached!" << endl;
            return;
        }
        
        tabs[tabCount].tabId = ++tabIdCounter;
        tabs[tabCount].title = title;
        tabs[tabCount].currentPage = Page(url, title);
        tabs[tabCount].accessCount = 1;
        tabs[tabCount].lastAccess = ++accessCounter;
        
        activeTab = tabCount;
        tabCount++;
        
        cout << "Opened new tab #" << tabIdCounter << ": " << title << endl;
    }
    
    void closeTab(int index) {
        if(index < 0 || index >= tabCount) {
            cout << "Invalid tab index!" << endl;
            return;
        }
        
        // Add to closed tabs
        closedTabs.addClosedTab(tabs[index].currentPage);
        cout << "Closed tab: " << tabs[index].title << endl;
        
        // Remove tab by shifting
        for(int i = index; i < tabCount - 1; i++) {
            tabs[i] = tabs[i + 1];
        }
        tabCount--;
        
        // Adjust active tab
        if(tabCount == 0) activeTab = -1;
        else if(activeTab >= tabCount) activeTab = tabCount - 1;
        else if(activeTab > index) activeTab--;
    }
    
    void closeActiveTab() {
        if(activeTab >= 0) closeTab(activeTab);
        else cout << "No active tab!" << endl;
    }
    
    void switchToTab(int index) {
        if(index < 0 || index >= tabCount) {
            cout << "Invalid tab index!" << endl;
            return;
        }
        
        activeTab = index;
        tabs[activeTab].accessCount++;
        tabs[activeTab].lastAccess = ++accessCounter;
        cout << "Switched to: " << tabs[activeTab].title << endl;
    }
    
    void navigateTo(string url, string title) {
        if(activeTab < 0) {
            cout << "No active tab! Open a new tab first." << endl;
            return;
        }
        
        // Push current page to back history
        tabs[activeTab].backHistory.push(tabs[activeTab].currentPage);
        // Clear forward history
        tabs[activeTab].forwardHistory.clear();
        // Set new page
        tabs[activeTab].currentPage = Page(url, title);
        tabs[activeTab].title = title;
        tabs[activeTab].accessCount++;
        tabs[activeTab].lastAccess = ++accessCounter;
        
        cout << "Navigated to: " << title << " (" << url << ")" << endl;
    }
    
    void goBack() {
        if(activeTab < 0 || tabs[activeTab].backHistory.isEmpty()) {
            cout << "Cannot go back!" << endl;
            return;
        }
        
        // Push current to forward
        tabs[activeTab].forwardHistory.push(tabs[activeTab].currentPage);
        // Pop from back
        tabs[activeTab].currentPage = tabs[activeTab].backHistory.pop();
        tabs[activeTab].title = tabs[activeTab].currentPage.title;
        
        cout << "Went back to: " << tabs[activeTab].title << endl;
    }
    
    void goForward() {
        if(activeTab < 0 || tabs[activeTab].forwardHistory.isEmpty()) {
            cout << "Cannot go forward!" << endl;
            return;
        }
        
        // Push current to back
        tabs[activeTab].backHistory.push(tabs[activeTab].currentPage);
        // Pop from forward
        tabs[activeTab].currentPage = tabs[activeTab].forwardHistory.pop();
        tabs[activeTab].title = tabs[activeTab].currentPage.title;
        
        cout << "Went forward to: " << tabs[activeTab].title << endl;
    }
    
    void reopenClosedTab() {
        if(closedTabs.isEmpty()) {
            cout << "No closed tabs to reopen!" << endl;
            return;
        }
        
        Page p = closedTabs.reopenLastClosed();
        openNewTab(p.url, p.title);
        cout << "Reopened: " << p.title << endl;
    }
    
    void displayTabs() {
        cout << "\n=== OPEN TABS (" << tabCount << ") ===" << endl;
        
        if(tabCount == 0) {
            cout << "No tabs open." << endl;
            return;
        }
        
        for(int i = 0; i < tabCount; i++) {
            cout << (i == activeTab ? "[*] " : "[ ] ");
            cout << (i+1) << ". " << tabs[i].title;
            cout << " (Back: " << tabs[i].backHistory.size();
            cout << ", Fwd: " << tabs[i].forwardHistory.size() << ")" << endl;
        }
    }
    
    void displayRecentTabs() {
        cout << "\n=== RECENTLY USED TABS ===" << endl;
        
        // Sort by last access (most recent first)
        int indices[50];
        for(int i = 0; i < tabCount; i++) indices[i] = i;
        
        for(int i = 0; i < tabCount - 1; i++) {
            for(int j = i + 1; j < tabCount; j++) {
                if(tabs[indices[j]].lastAccess > tabs[indices[i]].lastAccess) {
                    swap(indices[i], indices[j]);
                }
            }
        }
        
        int count = min(5, tabCount);
        for(int i = 0; i < count; i++) {
            int idx = indices[i];
            cout << (i+1) << ". " << tabs[idx].title << " (accessed " << tabs[idx].accessCount << " times)" << endl;
        }
    }
    
    void displayClosedTabs() {
        closedTabs.display();
    }
    
    void showCurrentPage() {
        if(activeTab < 0) {
            cout << "No active tab!" << endl;
            return;
        }
        cout << "\n=== CURRENT PAGE ===" << endl;
        cout << "Tab: " << tabs[activeTab].title << endl;
        cout << "URL: " << tabs[activeTab].currentPage.url << endl;
        cout << "Back history: " << tabs[activeTab].backHistory.size() << " pages" << endl;
        cout << "Forward history: " << tabs[activeTab].forwardHistory.size() << " pages" << endl;
    }
};

int main() {
    cout << "welcome to world of programming with umar usmani sap : 60199" << endl;
    cout << "Assignment 2 Task 2: Web Browser Tab Manager" << endl;
    cout << "=============================================" << endl;
    
    BrowserTabManager browser;
    int choice;
    
    // Open initial tab
    browser.openNewTab("https://google.com", "Google");
    
    while(true) {
        cout << "\n1. Open New Tab" << endl;
        cout << "2. Close Active Tab" << endl;
        cout << "3. Navigate to URL" << endl;
        cout << "4. Go Back" << endl;
        cout << "5. Go Forward" << endl;
        cout << "6. Switch Tab" << endl;
        cout << "7. Reopen Closed Tab" << endl;
        cout << "8. Display All Tabs" << endl;
        cout << "9. Display Recent Tabs" << endl;
        cout << "10. Display Closed Tabs" << endl;
        cout << "11. Show Current Page" << endl;
        cout << "12. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) {
            string url, title;
            cout << "Enter URL: ";
            getline(cin, url);
            cout << "Enter title: ";
            getline(cin, title);
            browser.openNewTab(url, title);
        }
        else if(choice == 2) {
            browser.closeActiveTab();
        }
        else if(choice == 3) {
            string url, title;
            cout << "Enter URL: ";
            getline(cin, url);
            cout << "Enter title: ";
            getline(cin, title);
            browser.navigateTo(url, title);
        }
        else if(choice == 4) {
            browser.goBack();
        }
        else if(choice == 5) {
            browser.goForward();
        }
        else if(choice == 6) {
            browser.displayTabs();
            int idx;
            cout << "Enter tab number: ";
            cin >> idx;
            browser.switchToTab(idx - 1);
        }
        else if(choice == 7) {
            browser.reopenClosedTab();
        }
        else if(choice == 8) {
            browser.displayTabs();
        }
        else if(choice == 9) {
            browser.displayRecentTabs();
        }
        else if(choice == 10) {
            browser.displayClosedTabs();
        }
        else if(choice == 11) {
            browser.showCurrentPage();
        }
        else if(choice == 12) {
            cout << "Exiting browser..." << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
