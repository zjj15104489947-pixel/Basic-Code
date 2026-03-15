#include <iostream>
#include <vector>
using namespace std;

// 定义树节点结构体
struct TreeNode {
    char data; // 节点存储的数据
    vector<TreeNode*> children; // 子节点列表
    
    // 构造函数初始化节点
    TreeNode(char val) : data(val) {}
};

//创建树 
TreeNode* createTree() {
    char data;
    cin >> data; // 输入节点值
    
    if (data == '#') { // '#'表示空节点
        return nullptr;
    }
    
    TreeNode* node = new TreeNode(data); // 创建新节点
    
    int numChildren;
    cout << "Enter number of children for " << data << ": ";
    cin >> numChildren;
    
    for (int i = 0; i < numChildren; ++i) {
        cout << "Enter child " << i + 1 << " of " << data << ": ";
        TreeNode* child = createTree(); // 递归创建子树
        if (child) {
            node->children.push_back(child);
        }
    }
    
    return node;
}

//前序遍历 
void preOrderTraversal(TreeNode* root) {
    if (!root) return;
    
    cout << root->data << " "; // 访问根节点
    for (TreeNode* child : root->children) {
        preOrderTraversal(child); // 递归遍历每个子树
    }
}

//后序遍历 
void postOrderTraversal(TreeNode* root) {
    if (!root) return;
    
    for (TreeNode* child : root->children) {
        postOrderTraversal(child); // 递归遍历每个子树
    }
    cout << root->data << " "; // 访问根节点
}

//层次遍历 
void levelOrderTraversal(TreeNode* root) {
    if (!root) return;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        
        cout << current->data << " "; // 访问当前节点
        
        for (TreeNode* child : current->children) {
            q.push(child); // 将子节点加入队列
        }
    }
}

//找出所有叶子结点 
void findLeafNodes(TreeNode* root) {
    if (!root) return;
    
    if (root->children.empty()) {
        cout << root->data << " "; // 当前节点是叶子节点
    } else {
        for (TreeNode* child : root->children) {
            findLeafNodes(child); // 递归查找子树中的叶子节点
        }
    }
}

//计算树的高度 
int calculateHeight(TreeNode* root) {
    if (!root) return 0;
    
    int maxHeight = 0;
    for (TreeNode* child : root->children) {
        maxHeight = max(maxHeight, calculateHeight(child)); // 计算每个子树的高度
    }
    
    return 1 + maxHeight; // 根节点高度为1加上子树的最大高度
}
