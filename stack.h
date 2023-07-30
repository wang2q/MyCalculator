#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>
using namespace std;
//模板栈
template <typename T>
class Stack{
private:
    T *data;
    int top;
    int capacity;
public:
    Stack();
    Stack(int x);
    ~Stack();
    void push(T x);
    void pop();
    int size();
    T peek();
    bool empty();
};
template class Stack<char>;
template class Stack<long double>;
#endif // STACK_H
