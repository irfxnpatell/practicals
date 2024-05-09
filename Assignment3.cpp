#include<iostream>
using namespace std;

class node{
public:
    int data;
    node* left;
    node* right;
    bool leftThread;
    bool rightThread;

    node(int d){
        this->data = d;
        this->left = NULL;
        this->right = NULL;
        this->leftThread = false;
        this->rightThread = false;
    }
};

// Function to find a node with given key in the threaded binary tree
node* search(node* root, int key) {
    while (root != NULL) {
        if (key == root->data)
            return root;
        else if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

// Function to delete a node from the threaded binary tree
node* deleteNode(node* root, int key) {
    // Find the node to be deleted
    node* target = search(root, key);
    if (target == NULL) {
        cout << "Node with key " << key << " not found in the tree." << endl;
        return root;
    }

    // Case 2: Node to be deleted has two children
    if (!target->leftThread && !target->rightThread) {
        node* inorderSuccessor = target->right;
        while (!inorderSuccessor->leftThread) {
            inorderSuccessor = inorderSuccessor->left;
        }
        target->data = inorderSuccessor->data;
        return deleteNode(root, inorderSuccessor->data);
    }

    return root;
}

// Function to perform threaded inorder traversal recursively
void threadedInorderUtil(node* root){
    if(root == NULL)
        return;
    node* leftmost = root;
    while(leftmost->left != NULL && !leftmost->leftThread)
        leftmost = leftmost->left;
    while(leftmost != NULL){
        cout << leftmost->data << " ";
        if(leftmost->rightThread)
            leftmost = leftmost->right;
        else
            leftmost = leftmost->right;
    }
}

// Function to perform threaded inorder traversal
void threadedInorder(node* root){
    threadedInorderUtil(root);
    cout << endl;
}

// Function to perform threaded preorder traversal
void threadedPreorder(node* root){
    if(root == NULL)
        return;
    node* current = root;
    while(current != NULL){
        cout << current->data << " ";
        if(!current->leftThread)
            current = current->left;
        else if(!current->rightThread)
            current = current->right;
        else{
            while(current != NULL && current->rightThread)
                current = current->right;
            if(current != NULL)
                current = current->right;
        }
    }
    cout << endl;
}

// Function to perform threaded postorder traversal
void threadedPostorder(node* root){
    if(root == NULL)
        return;
    node* current = root;
    while(current != NULL && !current->leftThread)
        current = current->left;
    while(current != NULL){
        cout << current->data << " ";
        if(current->rightThread)
            current = current->right;
        else{
            current = current->right;
            while(current != NULL && !current->leftThread)
                current = current->left;
        }
    }
    cout << endl;
}

int main(){
    // Creating a threaded binary tree
    node* root = new node(50);
    root->left = new node(30);
    root->left->left = new node(20);
    root->left->right = new node(40);
    root->right = new node(70);
    root->right->left = new node(60);
    root->right->right = new node(80);
    root->left->rightThread = true;
    root->right->leftThread = true;

    // Threaded inorder traversal before deletion
    cout << "Threaded inorder traversal before deletion is : ";
    threadedInorder(root);

    // Deleting a node with two children (Case 2)
    root = deleteNode(root, 30);

    // Threaded inorder traversal after deletion
    cout << "Threaded inorder traversal after deletion is : ";
    threadedInorder(root);

    // Threaded preorder traversal
    cout << "Threaded preorder traversal is : ";
    threadedPreorder(root);

    // Threaded postorder traversal
    cout << "Threaded postorder traversal is : ";
    threadedPostorder(root);

    return 0;
}
