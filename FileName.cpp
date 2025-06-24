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

    // �ݹ����������������
    void inorder(TreeNode* node, vector<int>& res) {
        if (!node) return;
        inorder(node->left, res);
        res.push_back(node->val);
        inorder(node->right, res);
    }

public:
    BST() : root(nullptr) {}

    // �������������ʵ�֣�
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
                return; // �ؼ����Ѵ��ڣ�����
            }
        }
        if (key < parent->val) {
            parent->left = new TreeNode(key);
        }
        else {
            parent->right = new TreeNode(key);
        }
    }

    // �������
    vector<int> inorderTraversal() {
        vector<int> res;
        inorder(root, res);
        return res;
    }

    // ��Χ��ѯ������ʵ�֣�ʱ�临�Ӷ�O(h + n)��
    vector<int> rangeQuery(int a, int b) {
        vector<int> res;
        if (root == nullptr) return res;

        stack<TreeNode*> st;
        TreeNode* cur = root;

        while (cur || !st.empty()) {
            // �����������룬ֻ��ջֵ>=a�Ľڵ�
            while (cur) {
                if (cur->val >= a) {
                    st.push(cur);
                    cur = cur->left;
                }
                else {
                    cur = cur->right; // ����ֵ<a�Ľڵ㼰��������
                }
            }

            if (st.empty()) break;
            cur = st.top();
            st.pop();

            // ��ǰ�ڵ�ֵ��[a, b]������
            if (cur->val >= a && cur->val <= b) {
                res.push_back(cur->val);
            }

            // ����ǰ�ڵ�ֵ����b������ֹ�����������ڵ�ֵ����
            if (cur->val > b) {
                break;
            }

            // ת��������
            cur = cur->right;
        }
        return res;
    }
};

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");

    int m;
    fin >> m; // ��ȡ������

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