#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include <queue>
// 一个会议室宣讲，不能同时宣讲两个项目    给定开始和结束时间， 安排日程      宣讲场次最多，返回最多的场次
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
//字符串数组    找策略使拼接起来的字符串字典序最小
//证明贪心就是证明传递性 ab ba  |  bc  cb | ac  ca
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
//切割金条 [10,20,30] 总长60，每切一次需要金条长度的铜板，最少需要多少    哈夫曼编码
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
//项目和对应利润   m：启动资金   k：最多可以做几个项目
//按花费进小根堆  根据资金弹出按利润进大根堆
//返回最后手中剩的钱
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
		//可能做到某个项目时   资金不够下一个项目
		if (q2.empty()) return m;
		m += q2.top()[1];
	}
	return m;
}
//数据流的中位数   只是堆的应用，与贪心无关
/*
1.第一个数进大根堆
2.判断当前数是否小于等于大根堆堆顶   是的话入大根堆，否则进小根堆
3.两个堆大小之差达到2的时候，多的一个弹出进另一个堆
*/
//N皇后问题      使用位运算可以进行常数项的时间优化
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