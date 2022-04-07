#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<queue>
void swap(int &a,int &b) {
	int temp = a;
	a = b;
	b = temp;
}
void swap1(int &a,int &b) {
	//0^a=a     a^a=0
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}
//���ȶ�
void select_sort(vector<int> &arr) {
	for (int i = 0; i < arr.size() - 1;i++) {
		int minIndex = i;
		for (int j = i + 1; j < arr.size();j++) {
			if (arr[j] < arr[minIndex]) minIndex=j;
		}
		if (minIndex != i) swap(arr[i],arr[minIndex]);
	}
}
//�ȶ�
void bubble_sort(vector<int>& arr) {
	for (int i = arr.size()-1; i > 0;i--) {
		for (int j = 0; j < i;j++) {
			if (arr[j] > arr[j + 1]) swap1(arr[j],arr[j+1]);
		}
	}
}
//�ȶ�    ����״����ͬO(N)-O(N^2)
void insert_sort(vector<int>& arr) {
	for (int i = 1; i < arr.size();i++) {
		for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--) swap(arr[j],arr[j+1]);
	}
}
#pragma region �鲢������ʹ��
//�鲢���� T(N)=2*T(N/2)+O(N)     nlogn    �ռ� n    �ȶ�
void merge(vector<int>& arr, int l, int m, int r) {
	vector<int> temp(r - l + 1);
	int i = 0, p1 = l, p2 = m + 1;
	while (p1 <= m && p2 <= r) {
		temp[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
	}
	while (p1 <= m) temp[i++] = arr[p1++];
	while (p2 <= r) temp[i++] = arr[p2++];
	for (i = 0; i < temp.size(); i++) arr[l + i] = temp[i];
}
void process(vector<int>& arr, int l, int r) {
	if (l == r) return;
	int mid = l + ((r - l) >> 1);
	process(arr, l, mid);
	process(arr, mid + 1, r);
	merge(arr, l, mid, r);
}
void merge_sort(vector<int>& arr) {
	int l = 0, r = arr.size() - 1;
	process(arr, l, r);
}
//С�����⣬ÿ����ǰ�߱���С���ۼ�����
//ת��Ϊ�ұ��ж��ٸ���������   ��ǰ�������ұ߱���������ĸ���  �ۼ�
int merge1(vector<int> arr, int l, int m, int r) {
	vector<int> temp(r - l + 1);
	int i = 0, p1 = l, p2 = m + 1, result = 0;
	while (p1 <= m && p2 <= r) {
		result += arr[p1] < arr[p2] ? (r - p2 + 1) * arr[p1] : 0;
		temp[i++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
	}
	while (p1 <= m) temp[i++] = arr[p1++];
	while (p2 <= r) temp[i++] = arr[p2++];
	for (i = 0; i < temp.size(); i++) arr[l + i] = temp[i];
	return result;
}
//��Ҫ�ź���ҲҪ��С��
int process1(vector<int> arr, int l, int r) {
	if (l == r) return 0;
	int mid = l + ((r - l) >> 1);
	return process1(arr, l, mid) + process1(arr, mid + 1, r) + merge1(arr, l, mid, r);
}
int smallSum(vector<int> arr) {
	return process1(arr, 0, arr.size() - 1);
}
//����� ��ߵ������ұߵĴ�����������һ�������
//ת��Ϊ���ұߵ�������С����
int merge2(vector<int> arr, int l, int m, int r) {
	vector<int> temp(r - l + 1);
	int i = 0, p1 = l, p2 = m + 1, result = 0;
	while (p1 <= m && p2 <= r) {
		result += arr[p1] > arr[p2] ? (r - p2 + 1) : 0;
		temp[i++] = arr[p1] > arr[p2] ? arr[p1++] : arr[p2++];
	}
	while (p1 <= m) temp[i++] = arr[p1++];
	while (p2 <= r) temp[i++] = arr[p2++];
	for (i = 0; i < temp.size(); i++) arr[l + i] = temp[i];
	return result;
}
int process2(vector<int> arr, int l, int r) {
	if (l == r) return 0;
	int mid = l + ((r - l) >> 1);
	return process2(arr, l, mid) + process2(arr, mid + 1, r) + merge2(arr, l, mid, r);
}
int inverseCount(vector<int> arr) {
	return process2(arr, 0, arr.size() - 1);
}
#pragma endregion
//�������� nlogn �n^2   �ռ� logn
//�м�����������߽���ұ߽�  ��������
vector<int> partition(vector<int>& arr,int l,int r) {
	int less = l - 1;
	int more = r;//���һ�����Ȳ���
	while (l<more) {
		if (arr[l] < arr[r]) swap(arr[++less], arr[l++]);
		else if (arr[l] > arr[r]) swap(arr[--more], arr[l]);//ע��lû��++  ��Ϊ�������൱���¹���һ����
		else l++;
	}
	swap(arr[more],arr[r]);//�ѻ���ֵ�����м�
	return {less+1,more};//��Ϊ�н���������more����-1
}
void quickSort(vector<int>& arr,int l,int r) {
	if (l<r) {//���ɻ�ȱ
		swap(arr[l+rand()%(r-l+1)],arr[r]);
		vector<int> p = partition(arr,l,r);
		quickSort(arr,l,p[0]-1);
		quickSort(arr,p[1]+1,r);
	}
}
void quick_sort(vector<int>& arr) {
	quickSort(arr,0,arr.size()-1);
}
void quick_sort1(vector<int>& arr,int l,int r) {
	if (l<r) {
		int i = l, j = r, x = arr[l];
		while (i<j) {
			while (i < j && arr[j] >= x) j--;
			if (i < j) arr[i++] = arr[j];
			while (i < j && arr[i] <= x) i++;
			if (i < j) arr[j--] = arr[i];
		}
		arr[i] = x;
		quick_sort1(arr,l,i-1);
		quick_sort1(arr,i+1,r);
	}
}
//������ nlogn   �ռ�O��1��   ���ȶ�
//���� 2*i+1  �Һ��� 2*i+2 ���ڵ� ��i-1��/2     ������
void heapInsert(vector<int>& arr,int index) {
	while (arr[index]>arr[(index-1)/2]) {
		swap(arr[index],arr[(index-1)/2]);
		index = (index - 1) / 2;
	}
}
//������
void heapify(vector<int>& arr,int index,int heapSize) {
	int left = index * 2 + 1;
	while (left<heapSize) {  //���Ӵ���
		//ȡ����������ֵ����±�
		int	largest = (left + 1 < heapSize) &&( arr[left + 1] > arr[left] )? left + 1 : left;
		largest = arr[largest] > arr[index] ? largest : index;
		if (largest == index) break;
		swap(arr[largest],arr[index]);
		index = largest;
		left = index * 2 + 1;
	}
}
void heap_sort(vector<int>& arr) {
	//for (int i = 1; i < arr.size();i++) heapInsert(arr,i);
	for (int i = arr.size() - 1; i >= 0; i--) heapify(arr,i,arr.size());
	int heapSize = arr.size();
	swap(arr[0], arr[--heapSize]);
	while (heapSize>0) {
		heapify(arr, 0, heapSize);
		swap(arr[0],arr[--heapSize]);
	}
}
//������Ӧ��
// �����������飬�����ÿ������ԭ�� ���벻����k       
// ѡ��С���� ά��k+1������ ��С�ķ���0λ��   ���ƣ���С�ķ���1λ��    nlogk
void smallHeap(vector<int> arr,int k) {
	priority_queue<int, vector<int>, greater<int>> heap;
	/*heap.push(2);
	heap.push(8);
	heap.push(3);
	heap.push(7);
	heap.push(1);
	while (!heap.empty()) {
		cout << heap.top() << " ";
		heap.pop();
	} */
	int index = 0;
	int l = arr.size();
	for (; index <=min(l, k);index++) {
		heap.push(arr[index]);
	}
	int i = 0;
	for (; index < arr.size(); i++, index++) {
		heap.push(arr[index]);
		arr[i] = heap.top();
		heap.pop();
	}
	while (!heap.empty())
	{
		arr[i++] = heap.top();
		heap.pop();
	}

}
//����Ҫ�Ƚϵ�����
//1.��������Ԫ��ֵ��Χ��С������һ��ͳ��ÿ�����ĸ�������ԭ�õ�������
// 2.��������������м�λ����������߲�0��׼��һЩͰ��ʮ������Ҫ10��Ͱ����ĩβ�����Ǽ��ͷŵ��ĸ�Ͱ����ε�������ʮλ��һ�飻��λ��һ��
//�ҳ��������ε��Ǹ���

//����ʵ��û��Ͱ���õĴ�Ƶ��   count���鳤��Ϊ10�̶������������Ǽ����ڶ�Ӧλ��1�� �ٱ�Ϊǰ׺��
//�Ӻ���ǰ��arr���飬����λ���ֶ�Ӧcount��������ʾ��λ�ϱ���С�����ж��ٸ�      ��Ӧ����1�����ڸ��������λ��
//ͨ��count�͸���������������Ͱ��Ͱ
int getDigit(int num,int digit) {
	int res = 0;
	while (digit--) {
		res = num % 10;
		num /= 10;
	}
	return res;
}
void radixSort(vector<int>& arr,int l,int r,int digit) {//digit �����������м�λ
	int radix = 10;
	int i = 0, j = 0;
	vector<int> bucket(r-l+1);
	for (int d = 1; d <= digit;d++) { //���ֵ�ж���λ�ͷ������ٴν���Ͱ
		vector<int> count(radix);
		for (i = l; i <= r;i++) {
			j = getDigit(arr[i],d);
			count[j]++;
		}
		for (int i = 1; i < radix; i++) count[i] = count[i] + count[i-1];
		for (i = r; i >= l;i--) {
			j = getDigit(arr[i], d);
			bucket[count[j] - 1] = arr[i];
			count[j]--;
		}
		//Ϊ��һ�γ���Ͱ��׼��
		for (i = l, j = 0; i <= r; i++, j++) arr[i] = bucket[j];
	}

}
int maxbits(vector<int> arr) {
	int maxValue = INT_MIN;
	for (int i = 0; i < arr.size(); i++) maxValue = max(maxValue,arr[i]);
	int res = 0;
	while (maxValue) {
		res++;
		maxValue /= 10;
	}
	return res;
}
void radix_sort(vector<int>& arr) {
	radixSort(arr,0,arr.size()-1,maxbits(arr));
}
//����������
void oneOdd(vector<int> arr) {
	int num = 0;
	for (int i : arr) num=num^ i;
	cout << num;
}
void twoOdd(vector<int> arr) {
	int num1 = 0;
	for (int i : arr) num1=num1^ i;//a^b
	//�����Ҳ��1
	int num2 = 0;
	for (int i:arr) {
		if (i&(num1&(~num1+1))) {
			num2 = num2 ^ i;
		}
	}
	cout << num2 << " " << (num2 ^ num1);
}
#pragma region ���ֲ���
//���ֲ���
int binarySearch(vector<int> arr, int a) {
	int l = 0, r = arr.size() - 1;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (a < arr[mid]) r = mid - 1;
		else if (a > arr[mid]) l = mid + 1;
		else return mid;
	}
	return -1;
}
//�����Ҵ��ڵ���ĳ���������λ��
int findFirstBigNum(vector<int> arr, int a) {
	int l = 0, r = arr.size() - 1;
	int index = -1;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (arr[mid] >= a) {
			index = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	return index;
}
//�ֲ���Сֵ��λ��  ����  ���ҡ��м�
int localMin(vector<int> arr) {
	if (arr[0] < arr[1]) return 0;
	if (arr[arr.size() - 1] < arr[arr.size() - 2]) return arr.size() - 1;
	int l = 1, r = arr.size() - 2;
	//ע��Խ������
	while (l <= r) {
		int mid = (l + r) / 2;
		if (arr[mid] < arr[mid - 1] && arr[mid] < arr[mid + 1]) return mid;
		if (arr[mid] > arr[mid - 1]) r = mid - 1;
		else if (arr[mid] > arr[mid + 1]) l = mid + 1;
	}
	return -1;
}
#pragma endregion
#pragma region ������
//������
//1.��׼
void comparator(vector<int>& arr) {
	sort(arr.begin(), arr.end());
}
//2.�����������
vector<int> generateRandomArray(int maxSize, int maxValue) {
	//rand()���ش�0��������������������������0-100֮��ȡ   ����rand()%100
	//�������[0,1)  ����N ->[0,N)  ȡ��������int�� -> [0,N-1]�ڵ�������� 
	vector<int> result(rand() % maxSize);
	for (int i = 0; i < result.size(); i++) {
		result[i] = rand() % maxValue - rand() % maxValue;
	}
	return result;
}
vector<int> copyArray(vector<int> arr) {
	vector<int> result(arr.size());
	for (int i = 0; i < arr.size(); i++) {
		result[i] = arr[i];
	}
	return result;
}
bool isEqual(vector<int> arr1, vector<int> arr2) {
	for (int i = 0; i < arr1.size(); i++) {
		if (arr1[i] != arr2[i]) return false;
	}
	return true;
}
void testIsSucceed() {
	int testTime = 10000;
	int maxSize = 100;
	int maxValue = 100;
	bool succeed = true;
	for (int i = 0; i < testTime; i++) {
		vector<int> arr1 = generateRandomArray(maxSize, maxValue);
		vector<int> arr2 = copyArray(arr1);
		quick_sort(arr1);
		comparator(arr2);
		if (!isEqual(arr1, arr2)) {
			succeed = false;
			break;
		}
	}
	string s = succeed ? "���Գɹ�" : "����ʧ��";
	cout << s;
}
#pragma endregion
void printArr(vector<int> arr) {
	for (int i : arr) cout << i << " ";
}
//�ݹ���[L,R]��Χ�ڵ����ֵ
//master����  T(N)=a*T(N/b)+O(N^d)    a=2,b=2,d=0
int findMax(vector<int> arr,int l,int r) {
	if (l == r) return arr[l];
	int mid = l + ((r-l)>>1);
	int	leftMax = findMax(arr,l,mid);
	int righMax = findMax(arr,mid+1,r);
	return max(leftMax,righMax);
}
int main2() {
	vector<int> arr{5,4,9,2,3};
	//vector<int> arr{1,1,2,2,3,3,4,4,5,6};
	//printArr(arr);
	//select_sort(arr);
	//bubble_sort(arr);
	//insert_sort(arr);
	//merge_sort(arr);
	//quick_sort(arr);
	//cout << endl;
	//heap_sort(arr);
	radix_sort(arr);
	printArr(arr);
	//smallHeap();
	//testIsSucceed();
	//cout << smallSum(arr);
	//cout << inverseCount(arr);
	//oneOdd(arr);
	//twoOdd(arr);
	//cout<<binarySearch(arr,5);
	//cout << findFirstBigNum(arr,4);
	//cout << localMin(arr);
	//cout << findMax(arr,0,arr.size()-1);
	return 0;
}