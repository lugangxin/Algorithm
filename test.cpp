#include<iostream>
using namespace std;
#include<queue>
#include<string.h>
class Stack {
public:
    Stack(int size_) {
        index = 0;
        size = size_;  // 栈的初始大小
        arr = new int[size];
    }
    void push(int x) {
        /*if (index >= size) {
            int *tmp = arr;
            size *= 2;
            arr = new int[size];
            memcpy(arr, tmp, sizeof(int) * index);
            delete []tmp;
        }*/
        arr[index++] = x;
    }
    int pop() {
        if (index == 0) {
            cout << "error\n";
            return -1;
        }
        else {
            cout << arr[--index] << endl;
            return arr[index];
        }
    }
    void top() {
        if (index == 0) cout << "error\n";
        else cout << arr[index - 1] << endl;
    }

private:
    int index;
    int size;
    int* arr;
};
 /*class Stack{
 public:
     queue<int> q1;
     void push(int x){
         q1.push(x);
     }
     void pop(){
         int size=q1.size();
         if (size == 0) {
             cout << "error\n";
             return;
         }
         size--;
         while(size--){
             q1.push(q1.front());
             q1.pop();
         }
         int res=q1.front();
         q1.pop();
         cout<<res<<endl;
     }
     void top(){
         if (q1.size() == 0) {
             cout << "error\n";
             return;
         }
         int res=q1.back();
         cout<<res<<endl;
     }
 };*/
int main() {
    int n=0;
    //cin >> n;
    Stack* st = new Stack(n);
    string s;
    while (cin >> s) {
        if (s == "push") {
            cin >> n;
            st->push(n);
        }
        else if (s == "pop") st->pop();
        else st->top();
    }
    return 0;
}