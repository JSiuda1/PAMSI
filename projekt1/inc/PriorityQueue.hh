#pragma once

#include <iostream>
#include <stdint.h>


template <typename Type>
class PriorityQueue {
  struct Node {
    Type data;
    uint8_t key = { 0 };
    Node* next;
  };
  
  Node* head;

public:
  PriorityQueue();
  void insert(const Type& var, const uint8_t& key);
  Type removeMin();
  Type min() const;
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
void PriorityQueue<Type>::insert(const Type& var, const uint8_t& key) {
  try {
    Node* temp = head; //temporary variable for moving
    Node* newElement = new Node; //new list element
    
    if(key > UINT8_MAX){
      throw std::out_of_range("Prioirty is out of uint8_t range");
    }

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
    throw;
  }
}

template <typename Type>
Type PriorityQueue<Type>::removeMin() {
  Node* temp = head;
  Type var = {};

  if(head == nullptr){
    throw std::logic_error("Priority Queue is empty!");
  }
  
  var = head->data;
  head = head->next;
  delete temp;

  return var;
}

template <typename Type>
Type PriorityQueue<Type>::min() const {
  Type var = {};
  
  if(head == nullptr){
    throw std::logic_error("Priority Queue is empty!");
  }
  
  var = head->data;
  return var;
}

template <typename Type>
int PriorityQueue<Type>::size() const {
  Node* temp = head;
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
  Node* current = head;
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
  Node* temp = head;
  while (head != nullptr) {
    head = head->next;
    delete temp; // nie wiem czy dzia³a git
    temp = head;
  }
}

template class PriorityQueue<std::string>;