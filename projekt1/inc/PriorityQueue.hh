#pragma once

#include <iostream>
#include <stdint.h>


template <typename Type>
class PriorityQueue {
  template <typename Type>
  struct Node {
    Type data;
    uint8_t key = { 0 };
    Node* next;
  };
  
  Node<Type>* head;

public:
  PriorityQueue();
  bool insert(const Type& var, const uint8_t& key);
  bool removeMin(Type & var);
  bool min(Type & var) const;
  int size() const;
  bool isEmpty() const;
  void print()const ;
  ~PriorityQueue();
};


template <typename Type>
PriorityQueue<Type>::PriorityQueue() {
  head = nullptr;
}


template <typename Type>
bool PriorityQueue<Type>::insert(const Type& var, const uint8_t& key) {
  try {
    Node<Type>* temp = head; //temporary variable for moving
    Node<Type>* newElement = new Node<Type>; //new list element
    newElement->data = var;
    newElement->next = nullptr;
    newElement->key = key;

    if (head == nullptr) {
      head = newElement;
    }
    else if (head->key > key) {
      newElement->next = head;
      head = newElement;
    }
    else {
      while (temp->next != nullptr && temp->next->key <= key) {
        temp = temp->next;
      }

      newElement->next = temp->next;
      temp->next = newElement;
    }
  }
  catch (std::bad_alloc& e) {
    return false;
  }
  return true;
}

template <typename Type>
bool PriorityQueue<Type>::removeMin(Type & var) {
  Node<Type>* temp = head;

  if(head == nullptr){
    return false;
  }
  
  var = head->data;
  head = head->next;
  delete temp;

  return true;
}

template <typename Type>
bool PriorityQueue<Type>::min(Type & var) const {
  if(head == nullptr){
    return false;
  }
  
  var = head->data;
  
  return true;
}

template <typename Type>
int PriorityQueue<Type>::size() const {
  Node<Type>* temp = head;
  int size = 0;

  while (temp != nullptr) {
    size++;
    temp = temp->next;
  }

  return size;
}

template <typename Type>
bool PriorityQueue<Type>::isEmpty() const {
  return head == nullptr ? true : false;
}

template <typename Type>
void PriorityQueue<Type>::print() const {
  Node<Type>* current = head;
  if (current == nullptr) {
    std::cout << "Brak elementów" << std::endl;
  }

  while (current != nullptr) {
    std::cout << "Data: " << current->data << " \tKey: " << (int)current->key << std::endl;
    current = current->next;
  }
}

template <typename Type>
PriorityQueue<Type>::~PriorityQueue() {
  Node<Type>* temp = head;
  while (head != nullptr) {
    head = head->next;
    delete temp; // nie wiem czy dzia³a git
    temp = head;
  }
}