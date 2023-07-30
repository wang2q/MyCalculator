#ifndef LIST_H
#define LIST_H
#include <cstring>
#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* pre;
    Node(const T& data);
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* now;
public:
    LinkedList();
    ~LinkedList();
    std :: string get_backdata();
    std :: string get_nextdata();
    void reset();
    void insert(const T& data);
    void clear();
};
template class LinkedList<std :: string>;
#endif // LIST_H
