#include<iostream>
using namespace std;
#include<queue>
struct TreeNode{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() :val(0),left(NULL),right(NULL){}
	TreeNode(int x):val(x), left(NULL), right(NULL) {}
};
//判断一颗树是否是完全二叉树
bool isCompleteBinaryTree(TreeNode* root) {
	if (root == NULL) return true;
	queue<TreeNode*> que;
	if (root != NULL) que.push(root);
	bool flag = false;
	while (!que.empty()) {
		int size = que.size();
		for (int i = 0; i < size;i++) {
			TreeNode* node = que.front();
			que.pop();
			if (!node->left && node->right) return false;
			if (flag && (node->left || node->right)) return false;
			if (node->left) que.push(node->left);
			if (node->right) que.push(node->right);
			//这句话放在下边比较好
			if (!node->left && !node->right) flag = true;
		}
	}
	return true;
}
//是否是二叉搜索树     是否是满二叉树类似
struct ReturnData {
	bool isBST;
	int minVal;
	int maxVal;
	ReturnData(bool isBST,int min,int max):isBST(isBST),minVal(min),maxVal(max) {}
};
ReturnData* process(TreeNode* root) {
	if (root == NULL) return NULL;
	ReturnData* leftData = process(root->left);
	ReturnData* rightData = process(root->right);
	int minVal = root->val;
	int maxVal = root->val;
	if (leftData != NULL) {
		minVal = min(minVal,leftData->minVal);
		maxVal = max(maxVal,leftData->maxVal);
	}
	if (rightData != NULL) {
		minVal = min(minVal, rightData->minVal);
		maxVal = max(maxVal, rightData->maxVal);
	}
	bool isBST = true;
	if (leftData != NULL && (!leftData->isBST||leftData->maxVal>=root->val)) isBST = false;
	if (rightData != NULL && (!rightData->isBST || rightData->minVal <= root->val)) isBST = false;
	return new ReturnData(isBST,minVal,maxVal);
}
bool isBST(TreeNode* root) {
	return process(root)->isBST;
}
//是否是平衡二叉树
int getHeight(TreeNode* root) {
	if (root == NULL) return 0;
	int leftHeight = getHeight(root->left);
	//-1标记不是平衡二叉树
	if (leftHeight == -1) return -1;
	int rightHeight = getHeight(root->right);
	if (rightHeight == -1) return -1;
	int result;
	if (abs(leftHeight - rightHeight) > 1) result = -1;
	else result = max(leftHeight, rightHeight) + 1;
	return result;
}
bool isBalanceBT(TreeNode* root) {
	return getHeight(root)==-1?false:true;
}
//两个节点最近的公共祖先
TreeNode* nearestCommonAncestor(TreeNode* root,TreeNode *p,TreeNode *q) {
	if (root == p || root == q || root == NULL) return root;
	TreeNode* left = nearestCommonAncestor(root->left,p,q);
	TreeNode* right = nearestCommonAncestor(root->right,p,q);
	if (left != NULL && right != NULL) return root;
	if (left == NULL && right != NULL) return right;
	else if (left != NULL && right == NULL) return left;
	else return NULL;
}
//找中序遍历的后继
// 增加一个指向父节点的指针
//1.有右节点，找右节点下最左边的2.无右节点，往上找某个节点是不是谁的左节点  有一种情况是最右边的节点
int main4() {
	TreeNode* root = new TreeNode(1);
	TreeNode* left = new TreeNode(0);
	TreeNode* right = new TreeNode(2);
	TreeNode* testBalance = new TreeNode(2);
	//root->left = left;
	root->right = right;
	right->right = testBalance;
	/*if (isCompleteBinaryTree(root)) cout << "是完全二叉树";
	else cout << "不是完全二叉树";*/
	/*if (isBST(root)) cout << "是二叉搜索树";
	else cout << "不是二叉搜索树";*/
	//if (isBalanceBT(root)) cout << "是平衡二叉树";
	return 0;
}