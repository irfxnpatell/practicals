#include <bits/stdc++.h>
using namespace std;

class Node {
    string key;
    string meaning;
    Node* left;
    Node* right;
    int height;

public:
    Node() {
        key = "";
        meaning = "";
        left = NULL;
        right = NULL;
        height = 0;
    }

    Node(string key, string meaning) {
        this->key = key;
        this->meaning = meaning;
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
    }

    friend class AVL;
};

class AVL {
public:
    Node* root;

    AVL() {
        root = NULL;
    }

    int height(Node* root) {
        if (root == NULL) {
            return 0;
        }
        return root->height;
    }

    int getBF(Node* root) {
        if (root == NULL) {
            return 0;
        }
        return height(root->left) - height(root->right);
    }

    // Rotate right
    Node* rotateRight(Node* root) {
        Node* rootlc = root->left;
        Node* rootlrc = rootlc->right;

        rootlc->right = root;
        root->left = rootlrc;

        root->height = 1 + max(height(root->left), height(root->right));
        rootlc->height = 1 + max(height(rootlc->left), height(rootlc->right));

        return rootlc;
    }

    // Rotate left
    Node* rotateLeft(Node* root) {
        Node* rootrc = root->right;
        Node* rootrlc = rootrc->left;

        rootrc->left = root;
        root->right = rootrlc;

        root->height = 1 + max(height(root->left), height(root->right));
        rootrc->height = 1 + max(height(rootrc->left), height(rootrc->right));

        return rootrc;
    }

    void insert(Node*& root, string key, string meaning) {
        if (root == NULL) {
            root = new Node(key, meaning);
            return;
        }

        if (key < root->key) {
            insert(root->left, key, meaning);
        } else if (key > root->key) {
            insert(root->right, key, meaning);
        }

        root->height = 1 + max(height(root->left), height(root->right));

        int BF = getBF(root);

        // LL
        if (BF > 1 && key < root->left->key) {
            root = rotateRight(root);
        }

        // RR
        if (BF < -1 && key > root->right->key) {
            root = rotateLeft(root);
        }

        // LR
        if (BF > 1 && key > root->left->key) {
            root->left = rotateLeft(root->left);
            root = rotateRight(root);
        }

        // RL
        if (BF < -1 && key < root->right->key) {
            root->right = rotateRight(root->right);
            root = rotateLeft(root);
        }
    }

    Node* minValue(Node* root) {
        Node* curr = root;
        while (curr->left != NULL) {
            curr = curr->left;
        }
        return curr;
    }

    void remove(Node*& root, string key) {
        if (root == NULL) {
            return;
        }

        if (key < root->key) {
            remove(root->left, key);
        } else if (key > root->key) {
            remove(root->right, key);
        } else {
            if ((root->left == NULL) || (root->right == NULL)) {
                Node* temp = root->left != NULL ? root->left : root->right;

                if (temp == NULL) {
                    delete root;
                    root = NULL;
                } else {
                    *root = *temp;
                    delete temp;
                }
            } else {
                Node* temp = minValue(root->right);
                root->key = temp->key;
                root->meaning = temp->meaning;
                remove(root->right, temp->key);
            }
        }

        if (root == NULL) {
            return;
        }

        root->height = 1 + max(height(root->left), height(root->right));

        int BF = getBF(root);

        // LL
        if (BF > 1 && key < root->left->key) {
            root = rotateRight(root);
        }

        // RR
        if (BF < -1 && key > root->right->key) {
            root = rotateLeft(root);
        }

        // LR
        if (BF > 1 && key > root->left->key) {
            root->left = rotateLeft(root->left);
            root = rotateRight(root);
        }

        // RL
        if (BF < -1 && key < root->right->key) {
            root->right = rotateRight(root->right);
            root = rotateLeft(root);
        }
    }

    void inorder(Node* node) {
        if (node != NULL) {
            inorder(node->left);
            cout << node->key << " \t " << node->meaning << endl;
            inorder(node->right);
        }
    }
};

int main() {
    AVL al;
    al.insert(al.root, "VP", "Don");
    al.insert(al.root, "VR", "Doctor");
    al.insert(al.root, "MM", "Marc");

    al.inorder(al.root);

    al.remove(al.root, "VP");
    al.inorder(al.root);

    return 0;
}