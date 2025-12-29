#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val)
     {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};
Node *insert(Node* root , int val)
{
    if (root == nullptr){
        return new Node(val);

    }
    if (val < root->data){
        root->left = insert(root->left , val);
    }
    else{
        root->right = insert(root->right , val);
    }
    return root;
}
void postorderTraversal(Node* root){
    if(root == nullptr){
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->data << " ";

}
int main (){
    cout << "welcome to the world of problem solving 2 with umar ahad usmani sap : 60199\n";
    cout <<"this is the lab 8 task 1 in which we jsut create a binary search tree \n";
    Node* root = nullptr;
    cout << "Enter the number of elements to insert: ";
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cout << "Enter element " << i+1 << ": ";
        int val;
        cin >> val;
        root = insert(root , val);
    }
    cout << "Binary Search Tree created with " << n << " elements." << endl;
    cout << "Postorder Traversal of the BST: ";
    postorderTraversal(root);
    return 0;
}