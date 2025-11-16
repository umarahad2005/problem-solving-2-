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

int search(node* head, int val) {
    if(head == NULL) {
        return -1;
    }
    
    node* temp = head;
    int position = 0;
    
    do {
        if(temp->data == val) {
            return position;
        }
        temp = temp->next;
        position++;
    } while(temp != head);
    
    return -1;
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
    
    cout << "\nCircular Linked List: ";
    display(head);
    
    cout << "\nEnter the value to search: ";
    cin >> value;
    
    int position = search(head, value);
    
    if(position != -1) {
        cout << "Value " << value << " found at position " << position << endl;
    } else {
        cout << "Value " << value << " not found in the list" << endl;
    }
    
    return 0;
}
