#include<iostream>
using namespace std;

class Node {
    public:
    int data;
    Node* next;

    Node(int val){
        data = val;
        next = NULL;
    }
};

void insertAtHead(Node* &head, int val){
   Node* n = new Node(val);
   n->next = head;
   head=n;
}

void display(Node* head){
    Node* temp = head;
    while (temp != NULL){
        cout<<temp->data<<"->";
        temp = temp->next;
    }
    cout<<"NULL"<<endl;
}

int main(){
    cout << "Welcome in the world of problem solving 2 with Umar Ahad Usmani SAP: 60199"<<endl;
    cout << "=========================================="<<endl;
    
    Node* head = NULL;
    int n, value;
    
    cout << "Enter the number of nodes: ";
    cin >> n;
    
    cout << "Enter the values for the linked list That Insert At Head :"<<endl;
    for(int i = 0; i < n; i++){
        cout << "Value " << (i+1) << ": ";
        cin >> value;
        insertAtHead(head, value);
    }
    
    cout << "\nLinked List: ";
    display(head);
    
    return 0;
}