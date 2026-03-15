#include <bits/stdc++.h>
using namespace std;

class BiNODE {
public:
    char data; // 结点值，字符类型，可以按字典序比较大小
    BiNODE* lchild; // 左子节点
    BiNODE* rchild; // 右子节点

    BiNODE(char d = '\0');//构造函数
    ~BiNODE();//析构函数
};

BiNODE::BiNODE(char d) : data(d), lchild(nullptr), rchild(nullptr) {}

BiNODE::~BiNODE() {
    delete lchild;
    delete rchild;
}

class BinaryTree {
public:

    BinaryTree(BiNODE* r = nullptr);  // 构造函数
    ~BinaryTree(); //析构函数

    BiNODE* BuildTree();  // 构建二叉树的函数
    void Recursion_Pre_Order(BiNODE* node);  // 递归前序遍历函数
    void NoRecursion_Pre_Order(BiNODE* node);  // 非递归前序遍历函数
    void Recursion_In_Order(BiNODE* node);  // 递归中序遍历函数
    void NoRecursion_In_Order(BiNODE* node);  // 非递归中序遍历函数
    void Recursion_Post_Order(BiNODE* node);  // 递归后序遍历函数
    void NoRecursion_Post_Order(BiNODE* node);  // 非递归后序遍历函数
    void Hierachicalorder(BiNODE* node);  // 层次遍历函数

    int Size_Of_Tree(BiNODE* node);  // 计算二叉树大小的函数
    int Height_Of_Tree(BiNODE* node);  // 计算二叉树高度的函数
    bool Is_Full_Tree(BiNODE* node);  // 判断是否为满二叉树的函数
    bool Is_Complete_Tree(BiNODE* node);  // 判断是否为完全二叉树的函数
    bool Is_Perfect_Tree(BiNODE* node);  // 判断是否为完美二叉树的函数
    BiNODE* GetRoot();  // 获取根节点的函数
    void SetRoot(BiNODE* node);  // 修改根节点的函数

private:
    BiNODE* root;  // 二叉树的根节点
    void freeTree(BiNODE* node);  // 释放二叉树节点的函数
};

BinaryTree::BinaryTree(BiNODE* r) : root(r) {}

BinaryTree::~BinaryTree() {
    freeTree(root);
}

void BinaryTree::freeTree(BiNODE* node) {
    if (node) {
        delete node;
    }
}

BiNODE* BinaryTree::GetRoot() {
    return root;
}

void BinaryTree::SetRoot(BiNODE* node) {
    root = node;
}

//二叉树基本操作 
BiNODE* maketree1(int pl,int pr,int midl,int midr,char *pre,char *mid,unordered_map<char,int> pos){
	BiNODE* root=new BiNODE(pre[pl]);
	int k=pos[pre[pl]];
	if(k>midl) root->lchild=maketree(pl+1,pl+k-midl,midl,k-1,pre,mid,pos);
	if(k<midr) root->rchild=maketree(pl+k-midl+1,pr,k+1,midr,pre,mid,pos);
	return root;
}
BiNODE* BinaryTree:: BuildTree(){ 
	unordered_map<char,int> pos;
	int n;cin>>n;
	if(n==0){
		root=nullptr;
		return root;
	}
	char *pre=new char[n+1];
	char *mid=new char[n+1];
	for(int i=1;i<=n;i++) cin>>pre[i];
	for(int i=1;i<=n;i++){
		cin>>mid[i];
		pos[mid[i]]=i;
	}
	root=maketree1(1,n,1,n,pre,mid,pos);
	delete[] pre;
	delete[] mid;
    return root;
};//前序+中序建树，在函数中处理输入

BiNODE* maketree2(int postl, int postr, int midl, int midr, const char *post, const char *mid, unordered_map<char,int> &pos){
    if (postl > postr) return nullptr; // 边界检查
    
    BiNODE* root = new BiNODE(post[postr]); // 根据后序遍历的特点，根节点在最后
    int k = pos[root->data]; // 在中序遍历中找到根节点的位置
    
    // 计算左子树大小
    int leftSize = k - midl;
    
    // 递归构建左右子树
    if(leftSize > 0) root->lchild = maketree(postl, postl + leftSize - 1, midl, k - 1, post, mid, pos);
    if(k < midr) root->rchild = maketree(postl + leftSize, postr - 1, k + 1, midr, post, mid, pos);

    return root;
}
BiNODE* BinaryTree::BuildTree() { 
    unordered_map<char,int> pos;
    int n;
    cin >> n;
    if(n == 0) {
        return nullptr; // 如果n为0，则返回空指针
    }
    
    char *post = new char[n+1];
    char *mid = new char[n+1];
    for(int i = 0; i < n; ++i) cin >> post[i]; // 注意这里与原题不同，下标从0开始
    for(int i = 0; i < n; ++i){
        cin >> mid[i];
        pos[mid[i]] = i; // 构建中序遍历中每个字符的位置映射
    }
    
    BiNODE* root = maketree2(0, n-1, 0, n-1, post, mid, pos); // 调用maketree函数构建二叉树
    
    delete[] post;
    delete[] mid;
    return root;
}//后序+中序建树，在函数中处理输入 

void BinaryTree:: Recursion_Pre_Order(BiNODE* root){
	if(root){
		cout<<root->data<<" ";
		Recursion_Pre_Order(root->lchild);
		Recursion_Pre_Order(root->rchild);
	}
};//递归前序遍历（*）
 
void BinaryTree:: NoRecursion_Pre_Order(BiNODE* root){
	if(!root) return;
	stack<BiNODE*> s1;
	s1.push(root);
	while(!s1.empty()){
		BiNODE* q=s1.top();
		s1.pop();
		cout<<q->data<<" ";
		if(q->rchild) s1.push(q->rchild);
		if(q->lchild) s1.push(q->lchild);
	}
};//非递归前序遍历（*）

void BinaryTree:: Recursion_In_Order(BiNODE* root){
	if(root){
		Recursion_In_Order(root->lchild);
		cout<<root->data<<" ";
		Recursion_In_Order(root->rchild);
	}
};//递归中序遍历（*）

void BinaryTree:: NoRecursion_In_Order(BiNODE* root){
	stack<BiNODE*> s1;
	while(root||!s1.empty()){
	while(root){
		s1.push(root);
		root=root->lchild;
	}
	if(!s1.empty()){
		root=s1.top();
		s1.pop();
		cout<<root->data<<" ";
		root=root->rchild;
	}
	}
};//非递归中序遍历

void BinaryTree:: Recursion_Post_Order(BiNODE* root){
	if(root){
		Recursion_Post_Order(root->lchild);
		Recursion_Post_Order(root->rchild);
		cout<<root->data<<" ";
	}
};//递归后序遍历（*）

void BinaryTree:: NoRecursion_Post_Order(BiNODE* root){
	stack<BiNODE*> s1;
	stack<BiNODE*> s2;
	s1.push(root);
	while(!s1.empty()){
		BiNODE* p=s1.top();
		s1.pop();
		s2.push(p);
		if(p->lchild) s1.push(p->lchild);
		if(p->rchild) s1.push(p->rchild);
	}
	while(!s2.empty()){
		cout<<s2.top()->data<<" ";
		s2.pop();
	}
};//非递归后序遍历

void BinaryTree:: Hierachicalorder(BiNODE* root){
	if(!root) return;
	queue<BiNODE*> q1;
	q1.push(root);
	while(!q1.empty()){
		BiNODE* temp=q1.front();
		q1.pop();
		cout<<temp->data<<" ";
		if(temp->lchild) q1.push(temp->lchild);
		if(temp->rchild) q1.push(temp->rchild);
	}
};//层次遍历（*）

int BinaryTree:: Size_Of_Tree(BiNODE* root){
	int cnt=0;
	if(!root) return 0;
	queue<BiNODE*> q1;
	q1.push(root);
	while(!q1.empty()){
		BiNODE* temp=q1.front();
		q1.pop();
		cnt++;
		if(temp->lchild) q1.push(temp->lchild);
		if(temp->rchild) q1.push(temp->rchild);
	}
	return cnt;
};//求结点个数

int BinaryTree:: Height_Of_Tree(BiNODE* root)
{
	if(!root) return 0;
	int lh=Height_Of_Tree(root->lchild);
	int rh=Height_Of_Tree(root->rchild);
	return max(lh,rh)+1;
};//返回二叉树的高度，这里定义空树高度为0.无需输出，返回即可

bool BinaryTree:: Is_Full_Tree(BiNODE* root){
    if(!root) return true;
    queue<BiNODE*> q1;
    q1.push(root);
    while(!q1.empty()){
        BiNODE* temp=q1.front();
        q1.pop();
        if((temp->lchild&&!temp->rchild)||(!temp->lchild&&temp->rchild)) return false;
        if(temp->lchild) q1.push(temp->lchild);
        if(temp->rchild) q1.push(temp->rchild);
    }
    return true;
};//判断是否是满二叉树

bool BinaryTree:: Is_Complete_Tree(BiNODE* root) {
    if (!root) return true;
    queue<BiNODE*> q1;
    q1.push(root);
    bool flag = false; // 标记是否遇到过不完全节点
    while (!q1.empty()) {
        BiNODE* temp = q1.front();
        q1.pop();
        if (temp->lchild) {
            if (flag) return false; // 如果已经遇到过不完全节点，则返回 false
            q1.push(temp->lchild);
        } else {
            flag = true; // 遇到不完全节点
        }
        if (temp->rchild) {
            if (flag) return false; // 如果已经遇到过不完全节点，则返回 false
            q1.push(temp->rchild);
        } else {
            flag = true; // 遇到不完全节点
        }
    }
    return true;
}//判断是否是完全二叉树 

bool BinaryTree:: Is_Perfect_Tree(BiNODE* root){
    return Size_Of_Tree(root)==pow(2,Height_Of_Tree(root))-1;
};//判断是否是完美二叉树
