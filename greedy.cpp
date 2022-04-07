#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include <queue>
// һ������������������ͬʱ����������Ŀ    ������ʼ�ͽ���ʱ�䣬 �����ճ�      ����������࣬�������ĳ���
static bool cmp(const vector<int> &a,const vector<int> &b) {
	return a[1] < b[1];
}
int assignMeetings(vector<vector<int>> nums,int curTime) {
	sort(nums.begin(),nums.end(),cmp);
	int result = 0;
	for (int i = 0; i < nums.size();i++) {
		if (curTime <= nums[i][0]) {
			result++;
			curTime = nums[i][1];
		}
	}
	return result;
}
//�ַ�������    �Ҳ���ʹƴ���������ַ����ֵ�����С
//֤��̰�ľ���֤�������� ab ba  |  bc  cb | ac  ca
static bool cmps(string a,string b) {
	return (a + b) < (b+a);
}
string lowestString(vector<string> strs) {
	if (strs.size()==0) return "";
	sort(strs.begin(),strs.end(),cmps);
	string res;
	for (int i = 0; i < strs.size();i++) {
		res += strs[i];
	}
	return res;
}
//�и���� [10,20,30] �ܳ�60��ÿ��һ����Ҫ�������ȵ�ͭ�壬������Ҫ����    ����������
int lessCost(vector<int> nums) {
	priority_queue<int, vector<int>, greater<int>> que;
	for (int i : nums) que.push(i);
	int sum = 0;
	int cur = 0;
	while (que.size()>1) {
		int temp = que.top(); que.pop();
		cur = temp + que.top(); que.pop();
		sum += cur;
		que.push(cur);
	}
	return sum;
}
//��Ŀ�Ͷ�Ӧ����   m�������ʽ�   k����������������Ŀ
//�����ѽ�С����  �����ʽ𵯳�������������
//�����������ʣ��Ǯ
struct minQue {
	bool operator()(const vector<int> &a,const vector<int> &b) {
		return a[0] > b[0];
	}
};
struct maxQue{
	bool operator()(const vector<int>& a, const vector<int>& b) {
		return a[1] < b[1];
	}
};
int profit(vector<vector<int>> nums,int m,int k) {
	priority_queue<vector<int>,vector<vector<int>>,minQue> q1;
	priority_queue<vector<int>, vector<vector<int>>, maxQue> q2;
	for (vector<int> i:nums) {
		q1.push(i);
	}
	for (int i = 0; i < k;i++) {
		while (!q1.empty() && q1.top()[0] <= m) {
			q2.push(q1.top()); q1.pop();
		}
		//��������ĳ����Ŀʱ   �ʽ𲻹���һ����Ŀ
		if (q2.empty()) return m;
		m += q2.top()[1];
	}
	return m;
}
//����������λ��   ֻ�Ƕѵ�Ӧ�ã���̰���޹�
/*
1.��һ�����������
2.�жϵ�ǰ���Ƿ�С�ڵ��ڴ���ѶѶ�   �ǵĻ������ѣ������С����
3.�����Ѵ�С֮��ﵽ2��ʱ�򣬶��һ����������һ����
*/
//N�ʺ�����      ʹ��λ������Խ��г������ʱ���Ż�
bool isValid(vector<int> record,int i,int j) {
	for (int k = 0; k < i;k++) {
		if (j==record[k]||abs(record[k]-j)==abs(i-k)) {
			return false;
		}
	}
	return true;
}
int process(int i,vector<int> record,int n) {
	if (i == n) return 1;
	int res = 0;
	for (int j = 0; j < n;j++) {
		if (isValid(record,i,j)) {
			record[i] = j;
			res += process(i+1,record,n);
		}
	}
	return res;
}
int NQueens(int n){
	if (n < 1) return 0;
	vector<int> record(n);
	return process(0,record,n);
}
int main6() {
	vector<string> strs{"b","ba"};
	//cout << lowestString(strs);
	cout << NQueens(8);
	return 0;
}