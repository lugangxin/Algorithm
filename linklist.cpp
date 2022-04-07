#include<iostream>
using namespace std;
#include<vector>
#include<unordered_map>
struct ListNode
{
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};
void reverseList1(ListNode* head) {
	ListNode* p = NULL, * cur = head;
	while (cur) {
		ListNode* temp = cur->next;
		cur->next = p;
		p = cur;
		cur = temp;
	}
}
ListNode* reverseBetween(ListNode* head, int m, int n) {
	// write code here
	ListNode* dummyNode = new ListNode(0);
	dummyNode->next = head;
	ListNode* pre = dummyNode;
	int temp1 = m;
	temp1--;
	while(temp1--) pre=pre->next;
	//for (int i = 0; i < m - 1; i++) pre = pre->next;
	ListNode* right = pre;
	int temp=n-m+1;
	while(temp--) right=right->next;
	//for (int i = 0; i < n - m + 1; i++) right = right->next;
	ListNode* left = pre->next;
	ListNode* cur = right->next;
	pre->next = NULL;
	right->next = NULL;
	reverseList1(left);
	pre->next = right;
	left->next = cur;
	return dummyNode->next;
}
ListNode* reverseList(ListNode* head) {
	ListNode* p = NULL;
	ListNode* cur = head, * temp;
	while (cur) {
		temp = cur->next;
		cur->next = p;
		p = cur;
		cur = temp;
	}
	return p;
}
//找到中间节点
ListNode* midListNode(ListNode* head) {
	ListNode* fast = head, * slow = head;
	while (fast->next&&fast->next->next) {
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}
//判断是否是回文链表 1.所有放到栈中 2.一半放到栈中
bool isPalindrome(ListNode* head) {
	ListNode* p1 = head, * p2,*head2;
	ListNode* mid = midListNode(head);
	ListNode* tail2= mid->next;
	mid->next = NULL;
	head2 = reverseList(tail2);
	p2 = head2;
	tail2->next = mid;
	while (p1&&p2) {
		if (p1->val == p2->val) {
			p1 = p1->next;
			p2 = p2->next;
		}
		else return false;
	}
	tail2->next = NULL;
	mid->next = reverseList(head2);
	return true;
}
//单链表划分为左小中间右边大的形式 1.存ListNode数组，根据值做partition，再串起来 
//void swap(int& a, int& b) {
//	int temp = a;
//	a = b;
//	b = temp;
//}
//void arrPartition(vector<ListNode*> nodeArr,int pivot) {
//	int less = -1;
//	int more = nodeArr.size();//不用把最后一个数当作基准了
//	int index = 0;
//	while (index<more) {
//		if (nodeArr[index]->val < pivot) swap(nodeArr[++less], nodeArr[index++]);
//		else if (nodeArr[index]->val < pivot) swap(nodeArr[--more], nodeArr[index]);
//		else index++;
//	}
//}
//2.
ListNode* listPartition(ListNode* head,int pivot) {
	ListNode* sH = NULL, * sT = NULL, * eH = NULL, * eT = NULL, * mH = NULL, * mT = NULL;
	ListNode* next;
	while (head) {
		next = head->next;
		head->next = NULL;
		if (head->val < pivot) {
			if (sH == NULL) {
				sH = head;
				sT = head;
			}
			else {
				sT->next = head;
				sT = head;
			}
		}
		else if (head->val==pivot) {
			if (eH==NULL) {
				eH = head;
				eT = head;
			}
			else {
				eT->next = head;
				eT = head;
			}
		}
		else
		{
			if (mH == NULL) {
				mH = head;
				mT = head;
			}
			else {
				mT->next = head;
				mT = head;
			}
		}
		head = next;
	}
	if (sT) {
		sT->next = eH;
		eT = eT == NULL ? sT : eT;
	}
	if (eT != NULL) eT->next = mH;
	return sH != NULL ? sH : (eH!=NULL?eH:mH);
}
//复制含随机指针的链表
class Node {
public:
	int val;
	Node* next;
	Node* random;

	Node(int _val) {
		val = _val;
		next = NULL;
		random = NULL;
	}
};
//还有一种方法就是放到哈希表里
Node* copyList(Node* head) {
	unordered_map<Node*, Node*> map;
	Node* cur = head;
	while (cur) {
		map[cur] = new Node(cur->val);
		cur = cur->next;
	}
	cur = head;
	while (cur) {
		map[cur]->next = map[cur->next];
		map[cur]->random = map[cur->random];
		cur = cur->next;
	}
	return map[head];
}
Node* copyRandomList(Node* head) {
	if (head == NULL) return NULL;
	Node* cur = head;
	Node* next = NULL;
	while (cur) {
		next = cur->next;
		cur->next = new Node(cur->val);
		cur->next->next = next;
		cur = next;
	}
	cur = head;
	Node* curCopy = NULL;
	while (cur) {
		next = cur->next->next;
		curCopy = cur->next;
		curCopy->random = cur->random != NULL ? cur->random->next : NULL;
		cur = next;
	}
	Node* res = head->next;
	cur = head;
	while (cur) {
		next = cur->next->next;
		curCopy = cur->next;
		cur->next = next;
		curCopy->next = next != NULL ? next->next : NULL;
		cur = next;
	}
	return res;
}
//两个有环或者无环单链表，相交返回第一个节点，不相交返回NULL
ListNode* getLoopNode(ListNode* head) {
	if (head == NULL || head->next == NULL || head->next->next == NULL) return NULL;
	//开始时两指针都在头节点，为了能够进入wile循环，先走一步
	ListNode* fast = head->next->next;
	ListNode* slow = head->next;
	while (fast!=slow) {
		if (fast->next == NULL || fast->next->next == NULL) return NULL;
		fast = fast->next->next;
		slow = slow->next;
	}
	fast = head;
	while (fast!=slow) {
		fast = fast->next;
		slow = slow->next;
	}
	return fast;
}
ListNode* noLoop(ListNode* head1,ListNode* head2) {
	if (head1 == NULL || head2 == NULL) return NULL;
	ListNode* cur1 = head1;
	ListNode* cur2 = head2;
	int n = 0;//记录两个链表长度差
	while (cur1->next!=NULL) { //因为要判断最后一个节点，不是单纯的求链表长度
		n++;
		cur1 = cur1->next;
	}
	while (cur2->next!=NULL) {
		n--;
		cur2 = cur2->next;
	}
	if (cur1 != cur2) return NULL;
	cur1 = n > 0 ? head1 : head2;//谁长谁变为cur1
	cur2 = cur1 == head1 ? head2 : head1;//谁短谁cur2
	n = abs(n);
	while (n) {
		cur1 = cur1->next;
		n--;
	}
	while (cur1!=cur2) {
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return cur1;
}
//都有环的情况
ListNode* hasLoop(ListNode* head1, ListNode* head2) {
	ListNode* loop1 = getLoopNode(head1), * loop2 = getLoopNode(head2);
	ListNode* cur1 = NULL, * cur2 = NULL;
	if (loop1 == loop2) {
		cur1 = head1;
		cur2 = head2;
		int n = 0;
		while (cur1->next != loop1) { //因为要判断最后一个节点，不是单纯的求链表长度
			n++;
			cur1 = cur1->next;
		}
		while (cur2->next != loop2) {
			n--;
			cur2 = cur2->next;
		}
		if (cur1 != cur2) return NULL;
		cur1 = n > 0 ? head1 : head2;//谁长谁变为cur1
		cur2 = cur1 == head1 ? head2 : head1;//谁短谁cur2
		n = abs(n);
		while (n) {
			cur1 = cur1->next;
			n--;
		}
		while (cur1 != cur2) {
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
		return cur1;
	}
	else {
		cur1 = loop1->next;
		while (cur1!=loop1) {
			if (cur1 == loop2) return loop1;
			cur1 = cur1->next;
		}
		return NULL;
	}
	return NULL;
}
void printList(ListNode* head) {
	ListNode* cur = head;
	while (cur)
	{
		cout << cur->val << " ";
		cur = cur->next;
	}
}
int main10() {
	ListNode* head = new ListNode(1);
	ListNode* head1 = new ListNode(2);
	ListNode* head2 = new ListNode(3);
	ListNode* head3 = new ListNode(4);
	ListNode* head4 = new ListNode(5);
	ListNode* head5;
	head5->val = 6;
	head->next = head1; head1->next = head2; head2->next = head3; head3->next = head4; head4->next = NULL;
	//printList(head);
	//cout << endl;
	//printList(reverseList(head));
	//cout << midListNode(head)->val;
	//cout << isPalindrome(head);
	//printList(head);
	//ListNode* l=listPartition(head,2);
	ListNode* l=reverseBetween(head,2,4);
	printList(l);
	return 0;
}