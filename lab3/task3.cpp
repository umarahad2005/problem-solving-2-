#include<iostream>
using namespace std;

class node {
public:
    int data;
    node* next;

    node(int val) {
        data = val;
        next = NULL;
    }
};

void insertAtTail(node* &head, int val) {
    node* n = new node(val);
    if(head == NULL) {
        n->next = n;
        head = n;
        return;
    }

    node* temp = head;
    while(temp->next != head) {
        temp = temp->next;
    }
    temp->next = n;
    n->next = head;
}

void deleteByValue(node* &head, int val) {
    if(head == NULL) {
        cout << "List is empty" << endl;
        return;
    }
    
    // If head node contains the value
    if(head->data == val) {
        // If only one node
        if(head->next == head) {
            delete head;
            head = NULL;
            return;
        }
        
        // Find last node
        node* temp = head;
        while(temp->next != head) {
            temp = temp->next;
        }
        
        node* todelete = head;
        temp->next = head->next;
        head = head->next;
        delete todelete;
        return;
    }
    
    // Search for node to delete
    node* temp = head;
    while(temp->next != head && temp->next->data != val) {
        temp = temp->next;
    }
    
    if(temp->next == head) {
        cout << "Value " << val << " not found in the list" << endl;
        return;
    }
    
    node* todelete = temp->next;
    temp->next = temp->next->next;
    delete todelete;
    cout << "Value " << val << " deleted successfully" << endl;
}

void display(node* head) {
    if(head == NULL) {
        cout << "List is empty" << endl;
        return;
    }
    
    node* temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while(temp != head);
    cout << endl;
}

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    
    node* head = NULL;
    int n, value;
    
    cout << "Enter the number of nodes: ";
    cin >> n;
    
    cout << "Enter " << n << " values for the nodes:" << endl;
    for(int i = 0; i < n; i++) {
        cout << "Node " << (i + 1) << ": ";
        cin >> value;
        insertAtTail(head, value);
    }
    
    cout << "\nOriginal Circular Linked List: ";
    display(head);
    
    cout << "\nEnter the value to delete: ";
    cin >> value;
    deleteByValue(head, value);
    
    cout << "\nCircular Linked List after deletion: ";
    display(head);
    
    return 0;
}
