//#include<iostream>
//using namespace std;
//#include<string>
//#include<vector>
//#include<algorithm>
////��ŵ������
//void func(int i,string from,string to,string mid) {
//	if (i == 1) cout << "Move 1 from " + from + " to " + to<<endl;
//	else {
//		func(i - 1, from, mid, to);
//		cout << "Move "<<i<<" from "+from+" to "+to<<endl;
//		func(i - 1, mid, to, from);
//	}
//}
//void hanoi(int n) {
//	if (n > 0) func(n,"��","��","��");
//}
////��ӡһ���ַ���ȫ�����ַ������������ַ���
//void printString(vector<char> res) {
//	string result = "";
//	for (char c : res) result.push_back(c);
//	cout << result<<endl;
//}
////����iλ��Ҫ��Ҫ��ѡ��res��ʾiλ��֮ǰ������ѡ��
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
////��ӡһ���ַ���ȫ��������     ��Ҫ�ظ�
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
//			swap(str, i, j);//i�������е��ַ�����������iλ��
//			process(str, i + 1, res);
//			swap(str, i, j);//��ԭΪԭ��������
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
////������ÿ��ֻ�������ߵ�����     ���õ��ܺ�������
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