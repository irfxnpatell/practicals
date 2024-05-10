#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int key;
    double p;
    double q;
    Node* left;
    Node* right;

    Node(int key, double p, double q) {
        this->key = key;
        this->p = p;
        this->q = q;
        this->left = nullptr;
        this->right = nullptr;
    }
};

double sum(double arr[], int i, int j) {
    double s = 0;
    for (int k = i; k <= j; k++)
        s += arr[k];
    return s;
}

double optimalSearchTree(double p[], double q[], int keys[], int n) {
    double dp[n][n];

    for (int i = 0; i < n; i++)
        dp[i][i] = q[i];

    for (int L = 2; L <= n; L++) {
        for (int i = 0; i < n - L + 1; i++) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;
            for (int r = i; r <= j; r++) {
                double cost = ((r == i)? 0 : dp[i][r - 1]) +
                              ((r == j)? 0 : dp[r + 1][j]) +
                              (p[r] * sum(q, i, j)) +
                              (q[r] * (1 + sum(p, i, j)));
                if (cost < dp[i][j])
                    dp[i][j] = cost;
            }
        }
    }

    return dp[0][n - 1];
}

Node* buildOptimalBST(double p[], double q[], int keys[], int start, int end) {
    if (start > end)
        return nullptr;

    int minCost = INT_MAX;
    int minIndex = -1;

    for (int i = start; i <= end; i++) {
        double cost = ((i == start)? 0 : optimalSearchTree(p, q, keys, i - 1)) +
                      ((i == end)? 0 : optimalSearchTree(p, q, keys, end - i)) +
                      (p[i] * sum(q, start, end)) +
                      (q[i] * (1 + sum(p, start, end)));
        if (cost < minCost) {
            minCost = cost;
            minIndex = i;
        }
    }

    Node* root = new Node(keys[minIndex], p[minIndex], q[minIndex]);
    root->left = buildOptimalBST(p, q, keys, start, minIndex - 1);
    root->right = buildOptimalBST(p, q, keys, minIndex + 1, end);

    return root;
}

void printInOrder(Node* root) {
    if (root == nullptr)
        return;

    printInOrder(root->left);
    cout << root->key << " (" << root->p << ", " << root->q << ") ";
    printInOrder(root->right);
}

int main() {
    int keys[] = {10, 12, 20};
    double p[] = {0.34, 0.08, 0.50};
    double q[] = {0.66, 0.92, 0.50};
    int n = sizeof(keys) / sizeof(keys[0]);

    double minCost = optimalSearchTree(p, q, keys, n);
    cout << "Minimum cost: " << minCost << endl;

    Node* root = buildOptimalBST(p, q, keys, 0, n - 1);

    cout << "Optimal BST: ";
    printInOrder(root);
    cout << endl;

    return 0;
}