#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

class BST {
private:
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };
    TreeNode* root;

    // 递归中序遍历辅助函数
    void inorder(TreeNode* node, vector<int>& res) {
        if (!node) return;
        inorder(node->left, res);
        res.push_back(node->val);
        inorder(node->right, res);
    }

public:
    BST() : root(nullptr) {}

    // 插入操作（迭代实现）
    void insert(int key) {
        if (root == nullptr) {
            root = new TreeNode(key);
            return;
        }
        TreeNode* cur = root;
        TreeNode* parent = nullptr;
        while (cur) {
            parent = cur;
            if (key < cur->val) {
                cur = cur->left;
            }
            else if (key > cur->val) {
                cur = cur->right;
            }
            else {
                return; // 关键字已存在，忽略
            }
        }
        if (key < parent->val) {
            parent->left = new TreeNode(key);
        }
        else {
            parent->right = new TreeNode(key);
        }
    }

    // 中序遍历
    vector<int> inorderTraversal() {
        vector<int> res;
        inorder(root, res);
        return res;
    }

    // 范围查询（迭代实现，时间复杂度O(h + n)）
    vector<int> rangeQuery(int a, int b) {
        vector<int> res;
        if (root == nullptr) return res;

        stack<TreeNode*> st;
        TreeNode* cur = root;

        while (cur || !st.empty()) {
            // 向左子树深入，只入栈值>=a的节点
            while (cur) {
                if (cur->val >= a) {
                    st.push(cur);
                    cur = cur->left;
                }
                else {
                    cur = cur->right; // 跳过值<a的节点及其左子树
                }
            }

            if (st.empty()) break;
            cur = st.top();
            st.pop();

            // 当前节点值在[a, b]区间内
            if (cur->val >= a && cur->val <= b) {
                res.push_back(cur->val);
            }

            // 若当前节点值大于b，则终止遍历（后续节点值更大）
            if (cur->val > b) {
                break;
            }

            // 转向右子树
            cur = cur->right;
        }
        return res;
    }
};

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");

    int m;
    fin >> m; // 读取操作数

    BST bst;
    char op;
    for (int i = 0; i < m; i++) {
        fin >> op;
        if (op == 'I') {
            int key;
            fin >> key;
            bst.insert(key);
        }
        else if (op == 'T') {
            vector<int> res = bst.inorderTraversal();
            if (res.empty()) {
                fout << "NULL";
            }
            else {
                for (int j = 0; j < res.size(); j++) {
                    fout << res[j];
                    if (j < res.size() - 1) fout << " ";
                }
            }
            fout << endl;
        }
        else if (op == 'Q') {
            int a, b;
            fin >> a >> b;
            vector<int> res = bst.rangeQuery(a, b);
            if (res.empty()) {
                fout << "NULL";
            }
            else {
                for (int j = 0; j < res.size(); j++) {
                    fout << res[j];
                    if (j < res.size() - 1) fout << " ";
                }
            }
            fout << endl;
        }
    }

    fin.close();
    fout.close();
    return 0;
}