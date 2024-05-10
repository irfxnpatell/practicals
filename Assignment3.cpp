#include<bits/stdc++.h>
using namespace std;

class Node{
    int data;
    Node* left;
    Node* right;
    bool lbit, rbit;

public:
    Node()
    {
        data = 0;
        left = NULL;
        right = NULL;
        lbit = 0;
        rbit = 0;
    }
    Node(int data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
        lbit = 0;
        rbit = 0;
    }
    friend class TBST;
};

class TBST{
    Node* root;
    Node* head;

public:
    TBST(){
        head = root = NULL;
    }

    Node* getRoot(){
        return this->root;
    }

    void insert(int d){
        // if tree is empty
        if(root == NULL){
            head = new Node(-9999);
            head->right = head;

            root = new Node(d);

            head->left = root;
            head->lbit = 1;
            root->left = head;
            root->right = head;
            return;
        }
        // if tree is not empty
        else{
            Node* parent = root;
            Node* temp = new Node(d);

            while(true){
                if(d == parent->data){
                    delete temp;
                    return;
                }
                else if(d < parent->data){
                    if(parent->lbit == 1){
                        parent = parent->left;
                    }
                    else{
                        temp->left = parent->left;
                        temp->right = parent;
                        parent->left = temp;
                        parent->lbit = 1;
                        return;
                    }
                }
                else{
                    if(parent->rbit == 1){
                        parent = parent->right;
                    }
                    else{
                        temp->right = parent->right;
                        temp->left = parent;
                        parent->right = temp;
                        parent->rbit = 1;
                        return;
                    }
                }
            }
        }
    }

    void inorder(){
        Node* temp = root;
        while(temp->lbit == 1){
            temp = temp->left;
        }
        while(temp != head){
            cout<<temp->data<<" ";
            if(temp->rbit == 1){
                temp = temp->right;
                while(temp->lbit == 1){
                    temp = temp->left;
                }
            }
            else{
                temp = temp->right;
            }
        }
        cout<<endl;
    }

    void preorder(){
        bool flag = 0;
        Node* temp = root;
        while(temp != head){
            if(flag == 0){
                cout<<temp->data<<" ";
            }
            if(flag == 0 && temp->lbit == 1){
                temp = temp->left;
            }
            else{
                flag = (temp->rbit == 1) ? 0 : 1;
                temp = temp->right;
            }
        }
        cout<<endl;
    }

    bool search(int d, Node* &curr, Node* &par){
        while(curr != head){
            if(curr->data == d){
                return 1;
            }
            else{
                par = curr;
                if(d < curr->data){
                    curr = curr->left;
                }
                else{
                    curr = curr->right;
                }
            }
        }
        return false;
    }

    void deleteNode(Node* &par, Node* &curr){
        // 2 childs
        if(curr->lbit == 1 && curr->rbit == 1){
            Node* temp = curr->right;
            par = curr;
            while(temp->lbit == 1){
                par = temp;
                temp = temp->left;
            }
            curr->data = temp->data;
            curr = temp;
            cout<<"Deleting node having 2 links!!!"<<endl;
        }

        if(curr->lbit == 0 && curr->rbit == 0){
            if(par->left == curr){
                cout<<"Deleting left leaf "<<endl;
                par->left = curr->left;
                par->lbit = 0;
            }
            else{
                cout<<"Deleting right leaf "<<endl;
                par->right = curr->right;
                par->rbit = 0;
            }
            delete curr;
        }

        if(curr->lbit == 1 && curr->rbit == 0){
            Node* temp = curr->left;
            if(par->left == curr){
                par->left = temp;
            }
            else{
                par->right = temp;
            }
            while(temp->rbit == 1){
                temp = temp->right;
            }
            temp->right = curr->right;
            delete curr;
        }

        if(curr->lbit == 0 && curr->rbit == 1){
            Node* temp = curr->right;
            if(par->left == curr){
                par->left = temp;
            }
            else{
                par->right = temp;
            }
            while(temp->lbit == 1){
                temp = temp->left;
            }
            temp->left = curr->left;
            delete curr;
        }
    }
};

int main(){

    TBST tst;
    int n;
    cout<<"Enter no of nodes: ";
    cin>>n;
    int val;
    while(n--){
        cout<<"Enter value: ";
        cin>>val;
        tst.insert(val);
    }
    cout<<endl;
    tst.inorder();
    cout<<endl;
    tst.preorder();
    cout<<endl;

    int del;
    cout<<"Enter no to delete: ";
    cin>>del;

    Node* curr = tst.getRoot();
    Node* par = NULL;

    if(tst.search(del, curr, par)){
        tst.deleteNode(par, curr);
        cout<<del<<" Deleted"<<endl;
    }
    else{
        cout<<"Not found"<<endl;
    }
    
    cout<<endl;
    tst.inorder();
    return 0;
}