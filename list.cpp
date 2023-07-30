#include "list.h"
#include <iostream>
#include <cstring>
template <typename T>
Node<T>::Node(const T& data) : data(data), next(nullptr), pre(nullptr) {}
template <typename T>
LinkedList<T>::LinkedList() : head(new Node<T>(" ")), now(head){}
template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}
template <typename T>
std :: string LinkedList<T>:: get_backdata(){
   if(now -> next == nullptr) return "";
   std :: string res = now ->next -> data;
   now = now -> next;
   return res;
}
template <typename T>
std :: string LinkedList<T>:: get_nextdata(){
   if(now -> pre == nullptr) return "";
   std :: string res = now -> pre -> data;
   now = now -> pre;
   return res;
}

template <typename T>
void LinkedList<T>:: reset(){
    now = head;
}
template <typename T>
void LinkedList<T>::insert(const T& data) {
    Node<T>* newNode = new Node<T>(data);
    if (head == nullptr){
        head = newNode;
    } else {
        newNode -> next = head -> next;
        newNode -> pre = head;
        if(head -> next != nullptr) head -> next -> pre = newNode;
        head -> next = newNode;
    }
}
template <typename T>
void LinkedList<T>::clear() {
    Node<T>* current = head -> next;
    while (current != nullptr){
        Node<T>* temp = current;
        current = current->next;
        delete temp;
    }
    head ->next = nullptr;
}
