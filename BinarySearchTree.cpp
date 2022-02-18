#include <bits/stdc++.h>
using namespace std;

struct BST {
    int data;
    BST * left;
    BST * right;

    BST(int val) {
        data = val;
        left = right = NULL;
    }
};

BST* insert(BST* root, int val) {
    if (root == NULL)
        return new BST(val);
    BST* cur = root;
    while (true) {
        if (cur->data <= val) {
            if (cur->right != NULL)
                cur = cur->right;
            else {
                cur->right = new BST(val);
                break;
            }
        } else {
            if (cur->left != NULL)
                cur = cur->left;
            else {
                cur->left = new BST(val);
                break;
            }
        }
    }
    return root;
}

BST* search(BST * root, int val) {
    while (root != NULL && root->data != val) {
        root = (val < root->data) ? root->left : root->right;
    }
    return root;
}

BST* search(BST * root, BST * node) {
    while (root != NULL && root->data != node->data) {
        root = (node->data < root->data) ? root->left : root->right;
    }
    return root;
}

void inorder(BST * root) {
    if (!root)
        return;
    inorder(root->left);
    cout << root->data << ' ';
    inorder(root->right);
}

int findCeil(BST * root, int key) {
    int ceil = -1;

    while (root) {
        if (root->data == key)
            return root->data;

        if (key > root->data)
            root = root->right;
        else {
            ceil = root->data;
            root = root->left;
        }
    }
    return ceil;
}

int findFloor(BST * root, int key) {
    int floor = -1;

    while (root) {
        if (root->data == key)
            return root->data;

        if (key > root->data) {
            floor = root->data;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return floor;
}

// DELETE A NODE FROM BINARY SEARCH TREE
BST* findLastRight(BST* root) {
    if (root->right == NULL)
        return root;

    return findLastRight(root->right);
}

BST* helper(BST* root) {
    if (root->left == NULL)
        return root->right;
    else if (root->right == NULL)
        return root->left;

    BST* lastRight = findLastRight(root->left);
    lastRight->right = root->right;

    return root->left;
}

BST* deleteNode(BST* root, int key) {
    if (root == NULL)
        return NULL;

    if (root->data == key)
        return helper(root);

    BST* curr = root;
    while (curr != NULL) {
        if (curr->data > key) {
            if (curr->left != NULL && curr->left->data == key) {
                curr->left = helper(curr->left);
                break;
            } else
                curr = curr->left;
        } else {
            if (curr->right != NULL && curr->right->data == key) {
                curr->right = helper(curr->right);
                break;
            } else
                curr = curr->right;
        }
    }
    return root;
}

// CHECK IF BINARY TREE IS BST OR NOT
bool isBST(BST* root, int low, int high) {
    if (root == NULL)
        return true;
    if (root->data < low || root->data > high)
        return false;

    return isBST(root->left, low, root->data) &&
           isBST(root->right, root->data, high);
}

// FINDING LOWEST COMMON ANCESTOR(LCA) IN BINARY SEARCH TREE
BST* findLCA(BST* root, BST* a, BST* b) {
    if (root == NULL)
        return NULL;
    if (a->data > root->data || b->data > root->data)
        return findLCA(root->right, a, b);
    if (a->data < root->data || b->data < root->data)
        return findLCA(root->left, a, b);

    return root;
}

int KthSmallest(BST* root, int k) {
    // by any inorder traversal
    // kth smallest logic will work

    // we can say that Kth largest element is
    // size of (root-k)th element. we can find total
    // number of nodes using any of traversals
    stack<BST* > st;
    BST* node = root;
    int count = 0;

    while (true) {
        if (node != NULL) {
            st.push(node);
            node = node->left;
        } else {
            if (st.empty())
                break;

            node = st.top();
            st.pop();
            count++;

            if (count == k)
                return node->data;

            node = node->right;
        }
    }
    return -1;
}

BST* build(vector<int> & A, int & i, int bound) {
    if (i == A.size() || A[i] > bound) return NULL;
    BST* root = new BST(A[i++]);
    root->left = build(A, i, root->data);
    root->right = build(A, i, bound);
    return root;
}

BST* bstFromPreorder(vector<int> & A) {
    int i = 0;
    return build(A, i, INT_MAX);
}

int main() {

#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
#endif
    BST * root = new BST(56);
    BST * check;

    for (int i = 3; i < 43; i++) {
        insert(root, i * 2);
        if (i == 22)
            check = insert(root, i * 3);
    }

    // LevelOrder(root);
    // inorder(root);
    // cout << search(root, 466)->data << endl;
    // cout << search(root, check)->data << endl;
    // cout << findCeil(root, 43);
    // cout << findFloor(root, 345);

    // inorder(root);
    // deleteNode(root, 34);
    // cout << endl;
    // inorder(root);

    // cout << isBST(root, INT_MIN, INT_MAX);
    // cout << KthSmallest(root, 3);
    // bstFromPreorder();


    return 0;
}
