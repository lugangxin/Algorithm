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
//不稳定
void select_sort(vector<int> &arr) {
	for (int i = 0; i < arr.size() - 1;i++) {
		int minIndex = i;
		for (int j = i + 1; j < arr.size();j++) {
			if (arr[j] < arr[minIndex]) minIndex=j;
		}
		if (minIndex != i) swap(arr[i],arr[minIndex]);
	}
}
//稳定
void bubble_sort(vector<int>& arr) {
	for (int i = arr.size()-1; i > 0;i--) {
		for (int j = 0; j < i;j++) {
			if (arr[j] > arr[j + 1]) swap1(arr[j],arr[j+1]);
		}
	}
}
//稳定    数据状况不同O(N)-O(N^2)
void insert_sort(vector<int>& arr) {
	for (int i = 1; i < arr.size();i++) {
		for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--) swap(arr[j],arr[j+1]);
	}
}
#pragma region 归并排序及其使用
//归并排序 T(N)=2*T(N/2)+O(N)     nlogn    空间 n    稳定
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
//小和问题，每个数前边比它小的累加起来
//转换为右边有多少个数比它大   当前数乘以右边比它大的数的个数  累加
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
//既要排好序，也要求小和
int process1(vector<int> arr, int l, int r) {
	if (l == r) return 0;
	int mid = l + ((r - l) >> 1);
	return process1(arr, l, mid) + process1(arr, mid + 1, r) + merge1(arr, l, mid, r);
}
int smallSum(vector<int> arr) {
	return process1(arr, 0, arr.size() - 1);
}
//逆序对 左边的数比右边的大，两个数构成一个逆序对
//转化为找右边的数比它小的数
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
//快速排序 nlogn 最坏n^2   空间 logn
//中间等于区域的左边界和右边界  荷兰国旗
vector<int> partition(vector<int>& arr,int l,int r) {
	int less = l - 1;
	int more = r;//最后一个数先不动
	while (l<more) {
		if (arr[l] < arr[r]) swap(arr[++less], arr[l++]);
		else if (arr[l] > arr[r]) swap(arr[--more], arr[l]);//注意l没有++  因为交换后相当于新过来一个数
		else l++;
	}
	swap(arr[more],arr[r]);//把划分值换到中间
	return {less+1,more};//因为有交换，所以more不用-1
}
void quickSort(vector<int>& arr,int l,int r) {
	if (l<r) {//不可或缺
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
//堆排序 nlogn   空间O（1）   不稳定
//左孩子 2*i+1  右孩子 2*i+2 父节点 （i-1）/2     往上走
void heapInsert(vector<int>& arr,int index) {
	while (arr[index]>arr[(index-1)/2]) {
		swap(arr[index],arr[(index-1)/2]);
		index = (index - 1) / 2;
	}
}
//往下走
void heapify(vector<int>& arr,int index,int heapSize) {
	int left = index * 2 + 1;
	while (left<heapSize) {  //孩子存在
		//取两个孩子中值大的下标
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
//堆排序应用
// 几乎有序数组，排序后每个数与原来 距离不超过k       
// 选择小根堆 维护k+1个数字 最小的放在0位置   右移，最小的放在1位置    nlogk
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
//不需要比较的排序
//1.计数排序：元素值范围较小，遍历一遍统计每个数的个数，还原得到排序结果
// 2.基数排序：最大数有几位，不够的左边补0，准备一些桶（十进制需要10个桶），末尾数字是几就放到哪个桶里；依次倒出来；十位来一遍；百位来一遍
//找出现奇数次的那个数

//代码实现没有桶，用的词频表   count数组长度为10固定，出现数字是几就在对应位加1， 再变为前缀和
//从后往前看arr数组，看个位数字对应count的数，表示个位上比它小的数有多少个      对应数减1就是在辅助数组的位置
//通过count和辅助数组等于完成入桶出桶
int getDigit(int num,int digit) {
	int res = 0;
	while (digit--) {
		res = num % 10;
		num /= 10;
	}
	return res;
}
void radixSort(vector<int>& arr,int l,int r,int digit) {//digit 代表最大的数有几位
	int radix = 10;
	int i = 0, j = 0;
	vector<int> bucket(r-l+1);
	for (int d = 1; d <= digit;d++) { //最大值有多少位就发生多少次进出桶
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
		//为下一次出入桶做准备
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
//出现奇数次
void oneOdd(vector<int> arr) {
	int num = 0;
	for (int i : arr) num=num^ i;
	cout << num;
}
void twoOdd(vector<int> arr) {
	int num1 = 0;
	for (int i : arr) num1=num1^ i;//a^b
	//找最右侧的1
	int num2 = 0;
	for (int i:arr) {
		if (i&(num1&(~num1+1))) {
			num2 = num2 ^ i;
		}
	}
	cout << num2 << " " << (num2 ^ num1);
}
#pragma region 二分查找
//二分查找
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
//二分找大于等于某个数最左的位置
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
//局部最小值的位置  无序  左右、中间
int localMin(vector<int> arr) {
	if (arr[0] < arr[1]) return 0;
	if (arr[arr.size() - 1] < arr[arr.size() - 2]) return arr.size() - 1;
	int l = 1, r = arr.size() - 2;
	//注意越界问题
	while (l <= r) {
		int mid = (l + r) / 2;
		if (arr[mid] < arr[mid - 1] && arr[mid] < arr[mid + 1]) return mid;
		if (arr[mid] > arr[mid - 1]) r = mid - 1;
		else if (arr[mid] > arr[mid + 1]) l = mid + 1;
	}
	return -1;
}
#pragma endregion
#pragma region 对数器
//对数器
//1.标准
void comparator(vector<int>& arr) {
	sort(arr.begin(), arr.end());
}
//2.生成随机样本
vector<int> generateRandomArray(int maxSize, int maxValue) {
	//rand()返回从0到最大随机数的任意整数，若在0-100之间取   则用rand()%100
	//若随机数[0,1)  乘以N ->[0,N)  取整操作（int） -> [0,N-1]内的随机整数 
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
	string s = succeed ? "测试成功" : "测试失败";
	cout << s;
}
#pragma endregion
void printArr(vector<int> arr) {
	for (int i : arr) cout << i << " ";
}
//递归求[L,R]范围内的最大值
//master定理  T(N)=a*T(N/b)+O(N^d)    a=2,b=2,d=0
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