#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    struct Node * left;
    struct Node * right;

    Node(int data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

void printVector(const vector<int> v) {
    for (auto it : v)
        cout << it << ' ';
}

void printVector(const vector<vector<int>> v) {
    for (auto it : v) {
        for (auto itr : it)
            cout << itr << ' ';
        cout << endl;
    }
}

void preorder(Node * root) {
    if (!root)
        return;
    cout << root->data << ' ';
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node * root) {
    if (!root)
        return;
    inorder(root->left);
    cout << root->data << ' ';
    inorder(root->right);
}

void postorder(Node * root) {
    if (!root)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << ' ';
}

void levelOrder(Node * root) {
    if (!root)
        return;

    queue<Node * > q;
    q.push(root);
    while (!q.empty()) {
        Node * temp = q.front();
        cout << temp->data << endl;
        q.pop();

        if (temp->left)
            q.push(temp->left);
        if (temp->right)
            q.push(temp->right);
    }
}

void iterativepreorder(Node * root) {
    if (!root)
        return;

    stack<Node * > st;
    st.push(root);
    while (!st.empty()) {
        Node * temp = st.top();
        st.pop();

        cout << temp->data << endl;

        if (temp->right)
            st.push(temp->right);
        if (temp->left)
            st.push(temp->left);
    }
}

void iterativeinorder(Node * root) {
    if (!root)
        return;

    stack<Node * > st;
    Node * temp = root;

    while (1) {
        if (temp != NULL) {
            st.push(temp);
            temp = temp->left;
        } else {
            if (st.empty()) {
                break;
            }
            temp = st.top();
            st.pop();

            cout << temp->data << endl;
            temp = temp->right;
        }
    }
}

void iterativePostOrder(Node * root) {
    if (!root)
        return;

    // Using 2 stacks
    stack<Node * > st;
    stack<int> rev;
    st.push(root);
    while (!st.empty()) {
        Node * temp = st.top();
        st.pop();
        rev.push(temp->data);

        if (temp->left)
            st.push(temp->left);
        if (temp->right)
            st.push(temp->right);
    }

    while (!rev.empty()) {
        cout << rev.top() << endl;
        rev.pop();
    }
}

void iterativePostOrder1stack(Node * root) {
    if (!root)
        return;

    stack<Node * > st;
    Node * curr = root;

    while (curr || !st.empty()) {
        if (curr != NULL) {
            st.push(curr);
            curr = curr->left;
        } else {
            Node * temp = st.top()->right;

            if (temp == NULL) {
                temp = st.top();
                st.pop();
                cout << temp->data << endl;

                while (!st.empty() && st.top()->right == temp) {
                    temp = st.top();
                    st.pop();
                    cout << temp->data << endl;
                }
            } else {
                curr = temp;
            }
        }
    }
}

void AllInOneTraversal(Node * root, vector<int> & Pre, vector<int> & In, vector<int> & post) {
    if (!root)
        return;

    stack<pair<Node *, int>> st;
    st.push({root, 1});

    while (!st.empty()) {
        auto it = st.top();
        st.pop();

        if (it.second == 1) {
            Pre.push_back(it.first->data);
            it.second++;
            st.push(it);

            if (it.first->left)
                st.push({it.first->left, 1});
        } else if (it.second == 2) {
            In.push_back(it.first->data);
            it.second++;
            st.push(it);

            if (it.first->right)
                st.push({it.first->right, 1});
        } else {
            post.push_back(it.first->data);
        }
    }
}

int maxDepth(Node * root) {
    if (!root)
        return 0;

    int leftHeight = maxDepth(root->left);
    int rightHeight = maxDepth(root->right);

    return 1 + max(leftHeight, rightHeight);
}

// bool balancedBinaryTree()
int height(Node * root) {
    if (!root)
        return 0;

    int leftHeight = height(root->left);
    if (leftHeight == -1)
        return -1;

    int rightHeight = height(root->right);
    if (rightHeight == -1)
        return -1;

    if (abs(leftHeight - rightHeight) > 1)
        return -1;

    return 1 + max(leftHeight, rightHeight);
}

int height(Node * root, int & maxi) {
    if (!root)
        return 0;

    int lh = height(root->left, maxi);
    int rh = height(root->right, maxi);

    maxi = max(maxi, lh + rh);

    return 1 + max(lh, rh);
}

void diameter(Node * root) {
    if (!root)
        return;

    int maxi = INT_MIN;
    height(root, maxi);
    cout << maxi << endl;
}

int maxPathSum(Node * root, int & Sum) {
    if (!root)
        return 0;

    // If sum is less than 0
    int leftSum = max(0, maxPathSum(root->left, Sum));
    int rightSum = max(0, maxPathSum(root->right, Sum));

    Sum = max(Sum, leftSum + rightSum);

    return (root->data + max(leftSum, rightSum));
}

bool identicalOrNot(Node * root1, Node * root2) {
    if (root1 == NULL || root2 == NULL)
        return (root1 == root2);

    return (root1->data == root2->data) &&
           identicalOrNot(root2->left, root2->left) &&
           identicalOrNot(root1->right, root2->right);
}

vector<vector<int>> zigZagLevelOrder(Node * root) {
    if (!root)
        return {};

    vector<vector<int>> res;
    queue<Node * > q;
    q.push(root);

    bool leftToRight = true;

    while (!q.empty()) {
        int size = q.size();
        vector<int> row(size);

        for (int i = 0; i < size; i++) {
            Node * temp = q.front();
            q.pop();

            //Index according to zigZag
            int index = (leftToRight) ? i : size - i - 1;

            row[index] = temp->data;

            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }

        res.push_back(row);
        leftToRight = !leftToRight;
    }

    return res;
}

bool isLeaf(Node * root) {
    if (!root->left && !root->right)
        return true;
    return false;
}

void addLeftBoundry(Node * root, vector<int> & res) {
    while (root) {
        if (!isLeaf(root))
            res.emplace_back(root->data);
        if (root->left)
            root = root->left;
        else
            root = root->right;
    }
}

void addRightBoundry(Node * root, vector<int> & res) {
    stack<int> st;
    while (root) {
        if (!isLeaf(root))
            st.push(root->data);
        if (root->right)
            root = root->right;
        else
            root = root->left;
    }

    while (!st.empty()) {
        res.emplace_back(st.top());
        st.pop();
    }
}

void addLeafs(Node * root, vector<int> & res) {
    if (isLeaf(root)) {
        res.emplace_back(root->data);
        return;
    }

    if (root->left)
        addLeafs(root->left, res);
    if (root->right)
        addLeafs(root->right, res);
}

vector<int> BoundryTraversal(Node * root) {
    if (!root)
        return {};

    vector<int> res;
    if (!isLeaf(root))
        res.emplace_back(root->data);

    addLeftBoundry(root->left, res);
    addLeafs(root, res);
    addRightBoundry(root->right, res);

    return res;
}

vector<vector<int>> verticalTraversal(Node * root) {
    if (!root)
        return {};

    queue<pair<Node *, pair<int, int>>> nodes;
    map<int, map<int, multiset<int>>> vert;

    nodes.push({root, {0, 0}});
    while (!nodes.empty()) {
        auto it = nodes.front();
        nodes.pop();

        Node * temp = it.first;
        int x = it.second.first, y = it.second.second;
        vert[x][y].insert(temp->data);

        if (temp->left)
            nodes.push({temp->left, {x - 1, y + 1}});
        if (temp->right)
            nodes.push({temp->right, {x + 1, y + 1}});
    }

    vector<vector<int>> trav;
    for (auto it : vert) {
        vector<int> v;
        for (auto el : it.second)
            v.insert(v.begin(), el.second.begin(), el.second.end());

        trav.push_back(v);
    }
    return trav;
}

vector<int> topView(Node * root) {
    if (!root)
        return {};

    map<int, int> mp;
    queue<pair<Node *, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
        auto it = q.front();
        q.pop();

        Node * temp = it.first;
        int X = it.second;
        if (mp.find(X) == mp.end())
            mp[X] = temp->data;

        if (temp->left)
            q.push({temp->left, X - 1});
        if (temp->right)
            q.push({temp->right, X + 1});
    }

    vector<int> res;
    for (auto it : mp)
        res.push_back(it.second);

    return res;
}

vector<int> bottomView(Node * root) {
    if (!root)
        return {};

    map<int, int> mp;
    queue<pair<Node *, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
        auto it = q.front();
        q.pop();

        Node * temp = it.first;
        int X = it.second;
        mp[X] = temp->data;

        // Child of right side of node will come on last if we push left first else left will come in last if we push right first
        if (temp->left)
            q.push({temp->left, X - 1});
        if (temp->right)
            q.push({temp->right, X + 1});
    }

    vector<int> res;
    for (auto it : mp)
        res.push_back(it.second);

    return res;
}

void recursion(Node * root, int level, vector<int> & res) {
    if (!root)
        return;

    if (level == res.size())
        res.push_back(root->data);

    if (root->right)
        recursion(root->right, level + 1, res);
    if (root->left)
        recursion(root->left, level + 1, res);
}

void rightSideView(Node * root) {
    if (!root)
        return;

    vector<int> res;
    recursion(root, 0, res);
    printVector(res);
}

bool checkSymmetry(Node * left, Node * right) {
    if (!left || !right)
        return left == right;

    if (left->data != right->data)
        return false;

    return checkSymmetry(left->left, right->right) && checkSymmetry(left->right, right->left);
}

bool isSymmetric(Node * root) {
    return (root == NULL || checkSymmetry(root->left, root->right));
}

bool findPath(Node * root, int value, vector<int> & path) {
    if (!root)
        return false;

    path.push_back(root->data);

    if (root->data == value)
        return true;

    if (findPath(root->left, value, path) || findPath(root->right, value, path))
        return true;

    path.pop_back();
    return false;
}

void rootToNode(Node * root, int value) {
    if (!root)
        return;

    vector<int> path;
    findPath(root, value, path);
    printVector(path);
}

int maxWidth(Node * root) {
    if (!root)
        return 0;

    queue<pair<Node *, int>> q;
    q.push({root, 0});

    int ans = 0;
    while (!q.empty()) {
        int size = q.size();
        int mmin = q.front().second;
        int first, last;

        for (int i = 0; i < size; i++) {
            int curr_id = q.front().second - mmin;
            Node * node = q.front().first;
            q.pop();

            if (i == 0)
                first = curr_id;
            if (i == size - 1)
                last = curr_id;

            if (node->left)
                q.push({node->left, curr_id * 2 + 1});
            if (node->right)
                q.push({node->right, curr_id * 2 + 2});
        }
        ans = max(ans, last - first + 1);
    }
    return ans;
}

void reorder(Node * root) {
    if (!root)
        return;

    int child = 0;
    if (root->left)
        child += root->left->data;
    if (root->right)
        child += root->right->data;

    if (child < root->data) {
        if (root->left)
            root->left->data = root->data;
        else if (root->right)
            root->right->data = root->data;
    }

    reorder(root->left);
    reorder(root->right);

    int total = 0;
    if (root->left)
        total += root->left->data;
    if (root->right)
        total += root->right->data;

    if (root->left || root->right)
        root->data = total;
}

void childrenSum(Node * root) {
    reorder(root);
    printVector(zigZagLevelOrder(root));
}

Node * lowestCommonAncestor(Node * root, Node * a, Node * b) {
    if (!root || root == a || root == b)
        return root;

    Node * left = lowestCommonAncestor(root->left, a, b);
    Node * right = lowestCommonAncestor(root->right, a, b);

    if (left == NULL)
        return right;
    else if (right == NULL)
        return left;
    else
        return root;
}

// PRINT ALL NODES AT DISTANCE OF K NODES FROM A GIVEN NODE
void markParents(Node * root, unordered_map<Node *, Node * > & parent) {
    queue<Node * > q;
    q.push(root);

    while (!q.empty()) {
        Node * current = q.front();
        q.pop();

        if (current->left) {
            parent[current->left] = current;
            q.push(current->left);
        }
        if (current->right) {
            parent[current->right] = current;
            q.push(current->right);
        }
    }
}

vector<int> printNodesAtDistanceK(Node * root, Node * target, int K) {
    if (!root)
        return {};

    unordered_map<Node *, Node * > parents; // child -> parent
    markParents(root, parents);

    unordered_map<Node *, bool> visited;
    queue<Node * > q;
    visited[target] = true;
    q.push(target);
    int level = 0;

    while (!q.empty()) {
        int size = q.size();
        if (level++ == K)
            break;

        for (int i = 0; i < size; i++) {
            Node * node = q.front();
            q.pop();

            if (node->left && !visited[node->left]) {
                q.push(node->left);
                visited[node->left] = true;
            }

            if (node->right && !visited[node->right]) {
                q.push(node->right);
                visited[node->right] = true;
            }

            if (parents[node] && !visited[parents[node]]) {
                q.push(parents[node]);
                visited[parents[node]] = true;
            }
        }
    }

    vector<int> results;
    while (!q.empty()) {
        results.push_back(q.front()->data);
        q.pop();
    }

    return results;
}

// END OF PRINT ALL NODES AT DISTANCE OF K NODES FROM A GIVEN NODE

int findMaxDistance(map<Node *, Node * > & mpp, Node * target) {
    queue<Node * > q;
    q.push(target);
    map<Node *, int> vis;
    vis[target] = 1;
    int maxi = 0;
    while (!q.empty()) {
        int sz = q.size();
        int fl = 0;
        for (int i = 0; i < sz; i++) {
            auto node = q.front();
            q.pop();
            if (node->left && !vis[node->left]) {
                fl = 1;
                vis[node->left] = 1;
                q.push(node->left);
            }
            if (node->right && !vis[node->right]) {
                fl = 1;
                vis[node->right] = 1;
                q.push(node->right);
            }

            if (mpp[node] && !vis[mpp[node]]) {
                fl = 1;
                vis[mpp[node]] = 1;
                q.push(mpp[node]);
            }
        }
        if (fl)
            maxi++;
    }
    return maxi;
}
Node * bfsToMapParents(Node * root, map<Node *, Node * > & mpp, int start) {
    queue<Node * > q;
    q.push(root);
    Node * res;
    while (!q.empty()) {
        Node * node = q.front();
        if (node->data == start)
            res = node;
        q.pop();
        if (node->left) {
            mpp[node->left] = node;
            q.push(node->left);
        }
        if (node->right) {
            mpp[node->right] = node;
            q.push(node->right);
        }
    }
    return res;
}
int timeToBurnTree(Node * root, int start) {
    map<Node *, Node * > mpp;
    Node * target = bfsToMapParents(root, mpp, start);
    int maxi = findMaxDistance(mpp, target);
    return maxi;
}

////////////////////////////////////////////////////////////////

int findHeightLeft(Node * node) {
    int hght = 0;
    while (node) {
        hght++;
        node = node->left;
    }
    return hght;
}
int findHeightRight(Node * node) {
    int hght = 0;
    while (node) {
        hght++;
        node = node->right;
    }
    return hght;
}

int countNodes(Node * root) { // ONLY IN CASE OF COMPLETE BINARY TREES
    if (root == NULL)
        return 0;

    int lh = findHeightLeft(root);
    int rh = findHeightRight(root);

    if (lh == rh)
        return (1 << lh) - 1;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

// //////////////////////////////////////////////////////////////////
Node * treeFromPreIn(vector<int> & preorder, int preStart, int preEnd, vector<int> & inorder, int inStart, int inEnd, map<int, int> & inMap) {
    if (preStart > preEnd || inStart > inEnd)
        return NULL;

    Node * root = new Node(preorder[preStart]);
    int inRoot = inMap[root->data];
    int numsLeft = inRoot - inStart;

    root->left = treeFromPreIn(preorder, preStart + 1, preStart + numsLeft, inorder, inStart, inRoot - 1, inMap);
    root->right = treeFromPreIn(preorder, preStart + numsLeft + 1, preEnd, inorder, inRoot + 1, inEnd, inMap);

    return root;
}
Node * treeFromPreIn(vector<int> & preorder, vector<int> & inorder) {
    map<int, int> inMap;

    for (int i = 0; i < inorder.size(); i++) {
        inMap[inorder[i]] = i;
    }

    Node * root = treeFromPreIn(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, inMap);
    return root;
}

// ////////////////////////////////////////////////////////////////////

Node * treeFromInPost(vector<int> & inorder, int inStart, int inEnd, vector<int> & postorder, int postStart, int postEnd, map<int, int> & inMap) {
    if (postStart > postEnd || inStart > inEnd)
        return NULL;

    Node * root = new Node(postorder[postEnd]);
    int rootIndex = inMap[postorder[postEnd]];
    Node * leftchild = treeFromInPost(inorder, inStart, rootIndex - 1, postorder, postStart, postStart + rootIndex - inStart - 1, inMap);
    Node * rightchild = treeFromInPost(inorder, rootIndex + 1, inEnd, postorder, postStart + rootIndex - inStart, postEnd - 1, inMap);
    root->left = leftchild;
    root->right = rightchild;
    return root;
}

Node * treeFromInPost(vector<int> & inorder, vector<int> & postorder) {
    if (inorder.size() != postorder.size())
        return NULL;

    map<int, int> inMap;
    for (int i = 0; i < inorder.size(); ++i)
        inMap[inorder[i]] = i;

    return treeFromInPost(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1, inMap);
}

// ///////////////////////////////////////////////////////////////////

// Encodes a tree to a single string.
string serialize(Node * root) {
    if (!root)
        return "";

    string s = "";
    queue<Node * > q;
    q.push(root);
    while (!q.empty()) {
        Node * curNode = q.front();
        q.pop();
        if (curNode == NULL)
            s.append("#,");
        else
            s.append(to_string(curNode->data) + ',');
        if (curNode != NULL) {
            q.push(curNode->left);
            q.push(curNode->right);
        }
    }
    return s;
}

// Decodes your encoded data to tree.
Node * deserialize(string data) {
    if (data.size() == 0)
        return NULL;
    stringstream s(data);
    string str;
    getline(s, str, ',');
    Node * root = new Node(stoi(str));
    queue<Node * > q;
    q.push(root);
    while (!q.empty()) {

        Node * node = q.front();
        q.pop();

        getline(s, str, ',');
        if (str == "#") {
            node->left = NULL;
        } else {
            Node * leftNode = new Node(stoi(str));
            node->left = leftNode;
            q.push(leftNode);
        }

        getline(s, str, ',');
        if (str == "#") {
            node->right = NULL;
        } else {
            Node * rightNode = new Node(stoi(str));
            node->right = rightNode;
            q.push(rightNode);
        }
    }
    return root;
}

///////////////////////////////////////////////////////////

vector<int> morrisTraversal(Node * root) {
    vector<int> preorder;
    Node * curr = root;

    while (curr != NULL) {
        if (curr->left == NULL) {
            preorder.push_back(curr->data);
            curr = curr->right;
        } else {
            Node * prev = curr->left;
            while (prev->right && prev->right != curr) {
                prev = prev->right;
            }

            if (prev->right == NULL) {
                prev->right = curr;
                preorder.push_back(curr->data);
                curr = curr->left;
            } else {
                prev->right = NULL;
                curr = curr->right;
            }
        }
    }

    return preorder;
}

//////////////////////////////////////////////////////////////////////

void flattenToLinkedList(Node * root) {
    if (!root) return;

    stack<Node * >st;
    st.push(root);

    while (!st.empty()) {
        Node * curr = st.top();
        st.pop();

        if (curr->right)
            st.push(curr->right);
        if (curr->left)
            st.push(curr->left);

        if (!st.empty())
            curr->right = st.top();

        curr->left = NULL;
    }
}

int main() {
#ifndef RITIK_RANJAN
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
#endif

    // Node* root = NULL;
    // root = new Node(1);
    // root->left = new Node(2);
    // root->right = new Node(3);
    // root->left->left = new Node(4);
    // root->left->right = new Node(5);
    // root->right->left = new Node(6);
    // root->right->right = new Node(7);
    // root->left->right->left = new Node(8);
    // root->right->right->left = new Node(9);
    // root->right->right->right = new Node(10);

    // preorder(root);
    // cout << endl;
    // inorder(root);
    // cout << endl;
    // postorder(root);
    // cout << endl;
    // levelOrder(root);
    // iterativepreorder(root);
    // iterativeinorder(root);
    // iterativePostOrder(root);

    // Node *rooot = NULL;
    // rooot = new Node(1);
    // rooot->left = new Node(2);
    // rooot->right = new Node(3);
    // rooot->left->left = new Node(4);
    // rooot->left->right = new Node(5);
    // rooot->right->left = new Node(6);
    // rooot->right->right = new Node(7);
    // rooot->left->left->left = new Node(8);
    // rooot->left->right->left = new Node(9);
    // rooot->right->left->right = new Node(10);
    // rooot->right->right->left = new Node(11);

    Node * root = NULL;
    root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    root->left->left->left = new Node(8);
    root->left->right->left = new Node(9);
    root->right->left->right = new Node(10);
    root->right->right->left = new Node(11);
    // preorder(root);
    // inorder(root);
    // postorder(root);

    // vector<int> a, b, c;
    // AllInOneTraversal(root, a, b, c);
    // cout << endl;
    // for (auto it : c)
    //     cout << it << ' ';

    // bool balanced = height(root);
    // if (balanced)
    //     cout << "Balanced" << endl;
    // else
    //     cout << "Not Balanced" << endl;

    // diameter(root);
    // int PathSum = INT_MIN;
    // maxPathSum(root, PathSum);
    // cout << PathSum << endl;

    // cout << identicalOrNot(rooot, root);

    // printVector(zigZagLevelOrder(root));

    // printVector(BoundryTraversal(root));

    // printVector(verticalTraversal(root));

    // printVector(topView(root));

    // printVector(bottomView(root));

    // rightSideView(root);

    // cout << isSymmetric(root);

    // rootToNode(root, 10);

    // std::cout << maxWidth(root) << std::endl;

    // childrenSum(root);

    // Node *first = root->left->left->left;
    // Node *second = root->right->left->right;
    // cout << lowestCommonAncestor(root, first, second)->data;

    // printVector(printNodesAtDistanceK(root, root->right, 2));

    // cout << timeToBurnTree(root, 11);

    // cout << countNodes(root);

    // vector<int> pre, in, post;
    // AllInOneTraversal(root, pre, in, post);
    // levelOrder(treeFromPreIn(pre, in));
    // levelOrder(treeFromInPost(in, post));

    // cout << serialize(root);
    // string nodes = serialize(root);
    // Node *check = deserialize(nodes);
    // inorder(check);

    // printVector(morrisTraversal(root));

    // flattenToLinkedList(root);
    // while (root->right) {
    //     cout << root->data << ' ';
    //     root = root->right;
    // }

    


    return 0;
}
