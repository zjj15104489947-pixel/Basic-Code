#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>
using namespace std;

//树的操作（二维数组）

//前序遍历
void preOrder(int node, const vector<vector<int>>& children, vector<int>& result) { 
    if (node == -1) return; 
    result.push_back(node);
    for (int child : children[node]) {
        preOrder(child, children, result);
    }
}

//后序遍历
void postOrder(int node, const vector<vector<int>>& children, vector<int>& result) {
    if (node == -1) return;
    for (int child : children[node]) {
        postOrder(child, children, result);
    }
    result.push_back(node);
}

//层次遍历
void levelOrder(int root, const vector<vector<int>>& children, vector<int>& result) {
    if (root == -1) return;
    queue<int> q;
    q.push(root); 
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);
        for (int child : children[node]) {
            q.push(child);
        }
    }
}

//找出所有叶子节点
void findLeaves(int node, const vector<vector<int>>& children, vector<int>& leaves) {
    if (node == -1) return;
    if (children[node].empty()) {
        leaves.push_back(node);
    } else {
        for (int child : children[node]) {
            findLeaves(child, children, leaves);
        }
    }
}

//计算树的高度
int getHeight(int root, const vector<vector<int>>& children) {
    if (root == -1) return 0;
    if (children[root].empty()) return 1;
    int max_h = 0;
    for (int child : children[root]) {
        int h = getHeight(child, children);
        if (h > max_h) max_h = h;
    }
    return max_h + 1;
}

int main() {
    int index, parent;
    vector<pair<int, int>> inputs;
    int maxIndex = -1;
    int n = 0; 

    while (cin >> index >> parent) {
        inputs.push_back(make_pair(index, parent));
        if (index > maxIndex) {
            maxIndex = index;
        }
        n++;
    }


    
    
    vector<int> parents(maxIndex + 1, -1);
    for (const auto& p : inputs) {
        parents[p.first] = p.second;
    }

   
    vector<vector<int>> children(maxIndex + 1);

    int root = -1;
    for (int i = 0; i <= maxIndex; i++) {
        if (parents[i] == -1) {
            root = i;
        } else {
            children[parents[i]].push_back(i);
        }
    }

    cout << root << endl;

    vector<int> preOrderResult;
    preOrder(root, children, preOrderResult);
    for (int node : preOrderResult) {
        cout << node << " ";
    }
    cout << endl;

    vector<int> postOrderResult;
    postOrder(root, children, postOrderResult);
    for (int node : postOrderResult) {
        cout << node << " ";
    }
    cout << endl;

    vector<int> levelOrderResult;
    levelOrder(root, children, levelOrderResult);
    for (int node : levelOrderResult) {
        cout << node << " ";
    }
    cout << endl;
    
    cout<<n<<endl;

    vector<int> leaves;
    findLeaves(root, children, leaves);
    for (int leaf : leaves) {
        cout << leaf << " ";
    }
    cout << endl;
    
    cout<<leaves.size()<<endl;
    
    int treeheight = getHeight(root, children);
    cout<< treeheight << endl;
    
    return 0;
}
