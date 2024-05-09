#include<iostream>
#include<queue>
using namespace std;

class node{
public:
    int data;
    node* left;
    node* right;

    node(int d){
        this->data=d;
        this->left=NULL;
        this->right=NULL;
    }
};

node* buildTree(node* root){
    cout<<"Enter the data: "<<endl;
    int data;
    cin>>data;
    root = new node(data);

    if(data == -1){
        return NULL;
    }

    cout<<"Enter the data for inserting in left of "<<data<<endl;
    root->left=buildTree(root->left);
    cout<<"Enter the data for inserting in right of "<<data<<endl;
    root->right=buildTree(root->right);
    return root;
}

void preorder(node* root){
    if(root == NULL){
        return ;
    }
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
    
}
void inorder(node* root){
    if(root == NULL){
        return ;
    }
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);    
} 
void postorder(node* root){
    if(root == NULL){
        return ;
    }
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";    
} 
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

int height(node* root){
    if(root == NULL){
        return 0 ;
    }
    int leftheight=height(root->left);
    int rightheight=height(root->right);

    return max(leftheight,rightheight) + 1;
}

int main(){

    node* root = NULL;

    root = buildTree(root);

    cout << "Inorder traversal is :";
    inorder(root);
    cout << endl;

    cout << "Preorder traversal is :";
    preorder(root);
    cout << endl;

    cout << "Postorder traversal is :";
    postorder(root);
    cout << endl;

    cout << "Level order traversal is :";
    levelorder(root);
    cout << endl;

    cout << "Height of the tree is: " << height(root) << endl;

    return 0;
}


/* Non-recursive traversals

void inorder(node* root){
    if(root == NULL){
        return;
    }

    stack<node*> s;
    node* current = root;

    while(current != NULL || !s.empty()){
        while(current != NULL){
            s.push(current);
            current = current->left;
        }

        current = s.top();
        s.pop();

        cout << current->data << " ";

        current = current->right;
    }
}

void preorder(node* root){
    if(root == NULL){
        return;
    }

    stack<node*> s;
    s.push(root);

    while(!s.empty()){
        node* current = s.top();
        s.pop();

        cout << current->data << " ";

        if(current->right != NULL){
            s.push(current->right);
        }
        if(current->left != NULL){
            s.push(current->left);
        }
    }
}

void postorder(node* root){
    if(root == NULL){
        return;
    }

    stack<node*> s1;
    stack<node*> s2;
    s1.push(root);

    while(!s1.empty()){
        node* current = s1.top();
        s1.pop();
        s2.push(current);

        if(current->left != NULL){
            s1.push(current->left);
        }
        if(current->right != NULL){
            s1.push(current->right);
        }
    }

    while(!s2.empty()){
        node* current = s2.top();
        s2.pop();
        cout << current->data << " ";
    }
}

*/