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
//�ж�һ�����Ƿ�����ȫ������
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
			//��仰�����±߱ȽϺ�
			if (!node->left && !node->right) flag = true;
		}
	}
	return true;
}
//�Ƿ��Ƕ���������     �Ƿ���������������
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
//�Ƿ���ƽ�������
int getHeight(TreeNode* root) {
	if (root == NULL) return 0;
	int leftHeight = getHeight(root->left);
	//-1��ǲ���ƽ�������
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
//�����ڵ�����Ĺ�������
TreeNode* nearestCommonAncestor(TreeNode* root,TreeNode *p,TreeNode *q) {
	if (root == p || root == q || root == NULL) return root;
	TreeNode* left = nearestCommonAncestor(root->left,p,q);
	TreeNode* right = nearestCommonAncestor(root->right,p,q);
	if (left != NULL && right != NULL) return root;
	if (left == NULL && right != NULL) return right;
	else if (left != NULL && right == NULL) return left;
	else return NULL;
}
//����������ĺ��
// ����һ��ָ�򸸽ڵ��ָ��
//1.���ҽڵ㣬���ҽڵ�������ߵ�2.���ҽڵ㣬������ĳ���ڵ��ǲ���˭����ڵ�  ��һ����������ұߵĽڵ�
int main4() {
	TreeNode* root = new TreeNode(1);
	TreeNode* left = new TreeNode(0);
	TreeNode* right = new TreeNode(2);
	TreeNode* testBalance = new TreeNode(2);
	//root->left = left;
	root->right = right;
	right->right = testBalance;
	/*if (isCompleteBinaryTree(root)) cout << "����ȫ������";
	else cout << "������ȫ������";*/
	/*if (isBST(root)) cout << "�Ƕ���������";
	else cout << "���Ƕ���������";*/
	//if (isBalanceBT(root)) cout << "��ƽ�������";
	return 0;
}