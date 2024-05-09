#include<iostream>
#include<queue>
using namespace std;

class node{
public:
    int data;
    node* left;
    node* right;

    node(int d){
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

// Function to insert a node into the binary search tree
node* insert(node* root, int key) {
    if(root == NULL) {
        return new node(key);
    }
    if(key < root->data) {
        root->left = insert(root->left, key);
    } else if(key > root->data) {
        root->right = insert(root->right, key);
    }
    return root;
}
void preorder(node* root){ //NLR
    if(root == NULL){
        return;
    }
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(node* root) { // LNR
    if(root == NULL)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void postorder(node* root){ // LRN
    if(root == NULL){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Function for level order traversal of the binary search tree
void levelorder(node* root){
    if(root == NULL){
        return ;
    }
    queue<node*> q;
    q.push(root);

    while(!q.empty()){
        int levelsize=q.size();

        for(int i = 0 ; i<levelsize; i++){
            node* current = q.front();
            cout<<current->data<<" ";
            q.pop();


            if(current->left != NULL){
                q.push(current->left);
            }
            if(current->right != NULL){
                q.push(current->right);
            }
        }
        cout<<endl;
    }
}

int main(){
    node* root = NULL;

    // Inserting elements into BST
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // Level order traversal
    cout << endl << "Level order traversal is : ";
    levelorder(root);

    //Different traversals

    cout << endl << "Preorder traversal is : ";
    preorder(root);

    cout <<endl<< "Inorder traversal is : ";
    inorder(root);

    cout << endl << "Postorder traversal is : ";
    postorder(root);
    return 0;
}
