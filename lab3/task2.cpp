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

void insertAtHead(node* &head, int val) {
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
    head = n;
}

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
    
    cout << "\nEnter the value to insert at the beginning: ";
    cin >> value;
    insertAtHead(head, value);
    
    cout << "\nUpdated Circular Linked List: ";
    display(head);
    
    return 0;
}
