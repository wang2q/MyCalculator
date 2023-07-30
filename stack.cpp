#include "stack.h"
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>
template <typename T>
Stack<T>::Stack()
{
    capacity = 1000;
    data = new T[capacity];
    top = -1;
}
template <typename T>
Stack<T>:: Stack(int x){
    capacity = x;
    data = new T[capacity];
    top = -1;
}
template <typename T>
Stack<T>::~Stack() {
    delete[] data;
}//释放栈
template <typename T>
void Stack<T>:: push(T x) {
    if (top == capacity - 1) {
        T *new_data = new T[capacity * 2];
        for (int i = 0; i <= top; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity *= 2;
    }
    data[++top] = x;
}//添加元素
template <typename T>
int Stack<T>:: size(){
    return top +1;
}

template <typename T>
void Stack<T>::pop() {
    if (top == -1) {
        cout << "Error: Stack underflow" << endl;
        return;
    }
    top--;
}//删除栈顶元素
template <typename T>
T Stack<T>::peek(){
    if (top == -1) {
        cout << "Error: Stack empty" << endl;
        return T();
    }
    return data[top];
}//返回栈顶元素
template <typename T>
bool Stack<T>:: empty(){
    return top == -1;
}

