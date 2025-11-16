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

void insertAtEnd(Node* &head, int val){
    Node* n = new Node(val);
    if (head==NULL){
        head = n;
        return;
    }

    Node* temp = head;
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = n;
}

void display(Node* head){
    Node* temp = head;
    while (temp != NULL){
        cout<<temp->data<<"->";
        temp = temp->next;
    }
    cout<<"NULL"<<endl;
}
void updateNode(Node* head, int oldVal, int newVal){
    Node* temp = head;
    while(temp != NULL){
        if(temp->data == oldVal){
            temp->data = newVal;
            cout << "Node updated successfully!" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Value " << oldVal << " not found in the list!" << endl;
}

int main(){
    cout << "Welcome in the world of problem solving 2 with Umar Ahad Usmani SAP: 60199"<<endl;
    cout << "=========================================="<<endl;
    
    Node* head = NULL;
    int n, value;
    
    cout << "Enter the number of nodes: ";
    cin >> n;
    
    cout << "Enter the values for the linked list:"<<endl;
    for(int i = 0; i < n; i++){
        cout << "Value " << (i+1) << ": ";
        cin >> value;
        insertAtEnd(head, value);
    }
    
    cout << "\nLinked List: ";
    display(head);
    cout<<"kindly enter the element that you want to update from the linked list : ";
    int oldVal, newVal;
    cout<<"kindly enter old element:";
    cin>>oldVal;
    cout<<"\nkindly enter new element:";
    cin>>newVal;
    updateNode(head, oldVal, newVal);
   
    cout << "Linked List after update : ";
    display(head);

    
    return 0;
}