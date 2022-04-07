#include<iostream>
using namespace std;
typedef struct LNode {
	int data;
	LNode* next;
	/*LNode() {
		data = 0;
		next = NULL;
	}*/
}LNode,*LinkList;
void Josephus(int n,int k,int m) {
	if (n < 0 || k < 0 || m < 0) return;
	LinkList pnode, prenode, cur;
	pnode = new LNode();
	pnode->data = 1;
	pnode->next = pnode;//�ɻ�
	cur = pnode;
	//�������
	for (int i = 2; i <= n;i++) {
		LinkList temp = new LNode();
		temp->data = i;
		temp->next = cur->next;
		cur->next = temp;
		cur = temp;
	}
	prenode = cur;
	/*���������Ƿ���ȷ
	int num = 6;
	while (num--) {
		cout << pnode->data << " ";
		pnode = pnode->next;
	}*/
	while (--k) {
		prenode = pnode;
		pnode = pnode->next;
	}
	n--;
	while (n--) {
		int s = m;//���ÿ�ζ���m����Խ����ʹm��ֵ�����ı�
		while (--s) {
			prenode = pnode;
			pnode = pnode->next;
		}
		prenode->next = pnode->next;
		cout << "ɾ����λ��" << pnode->data;
		//free(pnode);
		pnode = prenode->next;
	}
	cout << endl;
	cout << "���һ���˵�λ��" << pnode->data;
}
int countDigitOne(int n) {
	if (n <= 0) return 0;
	int i = 1;
	int high = n;
	int count = 0;
	while (high != 0) {
		high = n / pow(10, i);
		int temp = n / pow(10, i - 1);
		int cur = temp % 10;
		int low = n - temp * pow(10, i - 1);
		if (cur < 1) count += high * pow(10, i - 1);
		else if (cur > 1) count += (high + 1) * pow(10, i - 1);
		else {
			count += high * pow(10, i - 1);
			count += low + 1;
		}
		i++;
	}
	return count;
}
int main1() {
	Josephus(6,1,3);
	/*for (int i = 1; i < INT_MAX; i++) {
		if (countDigitOne(i) == i) cout<<i<<" ";
	}*/
	return 0;
}