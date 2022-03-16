#pragma once

#include <iostream>

template <typename Type>
struct Node {
  Type data;
  Node* next;
};

//dzia³a jako buffor .. dane przychodz¹ do momentu kiedy maj¹ przyjœæ potem je segregujemy
//fifo
template <typename Type>
class Queue{
  Node<Type>* head;
public:
  Queue();
  void push(const Type & var);
  Type pop();
  void print();
  ~Queue();
};


template <typename Type>
Queue<Type>::Queue() {
  head = nullptr;
}


template <typename Type>
void Queue<Type>::push(const Type & var) {
  try {
    Node<Type>* temp = head; //temporary variable for moving
    Node<Type>* newElement = new Node<Type>; //new list element
    newElement->data = var;
    newElement->next = nullptr;

    if (head == nullptr) {
      head = newElement;
    }
    else {
      while (temp->next != nullptr) {
        temp = temp->next;
      }

      temp->next = newElement;
    }
  }
  catch (std::bad_alloc & e) {
    std::cerr << "Allocation error: " << e.what() << std::endl;
  }
}

template <typename Type>
Type Queue<Type>::pop() {
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
void Queue<Type>::print() {
  Node<Type>* current = head;
  if (current == nullptr) {
    std::cout << "Brak elementów" << std::endl;
  }
  
  while (current != nullptr) {
    std::cout << current->data << std::endl;
    current = current->next;
  }
}

template <typename Type>
Queue<Type>::~Queue() {
  Node<Type>* temp = head;
  while (head != nullptr) {
    head = head->next;
    delete temp; // nie wiem czy dzia³a git
    temp = head;
  }
}

