//#include<iostream>
//using namespace std;
//#include<string>
//#include<vector>
//#include<algorithm>
////汉诺塔问题
//void func(int i,string from,string to,string mid) {
//	if (i == 1) cout << "Move 1 from " + from + " to " + to<<endl;
//	else {
//		func(i - 1, from, mid, to);
//		cout << "Move "<<i<<" from "+from+" to "+to<<endl;
//		func(i - 1, mid, to, from);
//	}
//}
//void hanoi(int n) {
//	if (n > 0) func(n,"左","右","中");
//}
////打印一个字符串全部子字符串，包括空字符串
//void printString(vector<char> res) {
//	string result = "";
//	for (char c : res) result.push_back(c);
//	cout << result<<endl;
//}
////来到i位置要不要做选择，res表示i位置之前所做的选择
//void process(string str,int i,vector<char> res) {
//	if (i == str.size()) {
//		printString(res);
//		return;
//	}
//	vector<char> select = res;
//	res.push_back(str[i]);
//	process(str, i + 1, select);
//	vector<char> abandon = res;
//	process(str,i+1,abandon);
//}
//void printChildString(string str) {
//	vector<char> res;
//	process(str,0,res);
//}
////打印一个字符串全部的排列     不要重复
//void swap(string &chs,int i,int j) {
//	char tmp = chs[i];
//	chs[i] = chs[j];
//	chs[j] = tmp;
//}
//void process(string str,int i,vector<string> &res) {
//	if (i == str.size()) res.push_back(str);
//	vector<bool> visit(26);
//	for (int j = i; j < str.size();j++) {
//		if (!visit[str[j] - 'a']) {
//			visit[str[j] - 'a'] = true;
//			swap(str, i, j);//i往后所有的字符都可以来到i位置
//			process(str, i + 1, res);
//			swap(str, i, j);//还原为原来的样子
//		}
//	}
//}
//void allArrange(string str) {
//	vector<string> res;
//	process(str,0,res);
//	for (string s:res) {
//		cout << s << endl;
//	}
//}
////两个人每次只能拿两边的数，     求拿到总和最大的数
//int first(int arr[],int l,int r) {
//	if (l == r) return arr[l];
//	return max(arr[l]+second(arr,l+1,r),arr[r]+second(arr,l,r-1));
//}
//int second(int arr[],int l,int r) {
//	if (l == r) return 0;
//	return min(first(arr,l+1,r),first(arr,l,r-1));
//}
//int winMax(int arr[]) {
//	return max(first(arr,0,sizeof(arr)/sizeof(arr[0])),second(arr, 0, sizeof(arr) / sizeof(arr[0])));
//}
//int main() {
//	//hanoi(3);
//	//printChildString("abc");
//	allArrange("abc");
//	return 0;
//}