#pragma once

#include <iostream>
#include <stdint.h>

template <typename Type>
struct Node {
  Type data;
  uint8_t key = {0};
  Node* next;
};


template <typename Type>
class PriorityQueue{
  Node<Type>* head;

public:
  PriorityQueue();
  void insert(const Type & var, const uint8_t& key);
  Type removeMin();
  Type min() const;
  int size() const;
  bool isEmpty() const;
  void print();
  ~PriorityQueue();
};


template <typename Type>
PriorityQueue<Type>::PriorityQueue() {
  head = nullptr;
}


template <typename Type>
void PriorityQueue<Type>::insert(const Type & var, const uint8_t & key) {
  try {
    Node<Type>* temp = head; //temporary variable for moving
    Node<Type>* newElement = new Node<Type>; //new list element
    newElement->data = var;
    newElement->next = nullptr;
    newElement->key = key;

    if (head == nullptr) {
      head = newElement;
    }
    else if(head->key > key){
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
    std::cerr << "Allocation error: " << e.what() << std::endl;
  }
}

template <typename Type>
Type PriorityQueue<Type>::removeMin() {
  Node<Type>* temp = head;
  Type val;

  if (head != nullptr) {
    val = head->data;
    head = head->next;
    delete temp;
  }
  else {
    throw std::exception("Queue empty!");
  }

  return val;
}

template <typename Type>
Type PriorityQueue<Type>::min() const{
  if (head != nullptr) {
    return head->data;
  }
  else {
    throw std::exception("Queue empty!");
  }
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
void PriorityQueue<Type>::print() {
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

