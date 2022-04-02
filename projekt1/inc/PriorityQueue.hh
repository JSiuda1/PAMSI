#pragma once

#include <iostream>
#include <stdint.h>

/**
 * @brief Kolejka priorytetowa
 * 
 * @tparam Type typ danych
 */
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
  Type removeMax();
  Type max() const;
  int size() const;
  bool isEmpty() const;
  void print() const ;
  void clear();
  ~PriorityQueue();
};

/**
 * @brief Construct a new Priority Queue< Type>:: Priority Queue object
 * 
 * @tparam Type typ danych
 */
template <typename Type>
PriorityQueue<Type>::PriorityQueue() {
  head = nullptr;
}

/**
 * @brief dodanie elementu do kolejki z uwzglednieniem klucza
 * 
 * @tparam Type typ danych
 * @param var dane
 * @param key priorytet
 */
template <typename Type>
void PriorityQueue<Type>::insert(const Type& var, const uint8_t& key) {
  try {
    Node* temp = head; //temporary variable for moving
    Node* newElement = new Node; //new list element

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
  catch (std::bad_alloc e) {
    throw;
  }
}

/**
 * @brief zwraca i usuwa element z najwiekszym priorytetem
 * 
 * @tparam Type typ danych
 * @return Type dane
 */
template <typename Type>
Type PriorityQueue<Type>::removeMax() {
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

/**
 * @brief zwraca element z najwiekszym priorytetem
 * 
 * @tparam Type typ danych
 * @return Type dane
 */
template <typename Type>
Type PriorityQueue<Type>::max() const {
  Type var = {};
  
  if(head == nullptr){
    throw std::logic_error("Priority Queue is empty!");
  }
  
  var = head->data;
  return var;
}

/**
 * @brief zwraca rozmiar kolejki
 * 
 * @tparam Type typ danych
 * @return int ilość elementów w kolejce
 */
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

/**
 * @brief sprawdzenie czy kolejka jest pusta
 * 
 * @tparam Type typ danych
 * @return true kolejka pusta
 * @return false sa elementy na kolejce
 */
template <typename Type>
bool PriorityQueue<Type>::isEmpty() const {
  return head == nullptr ? true : false;
}

/**
 * @brief wypisuje w konsoli elementy kolejki
 * 
 * @tparam Type typ danych
 */
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

/**
 * @brief czyści kolejke
 * 
 * @tparam Type typ danych
 */
template <typename Type>
void PriorityQueue<Type>::clear(){
  Node* temp = head;
  while (head != nullptr) {
    head = head->next;
    delete temp;
    temp = head;
  }
}

/**
 * @brief Destroy the Priority Queue< Type>:: Priority Queue object
 * 
 * @tparam Type 
 */
template <typename Type>
PriorityQueue<Type>::~PriorityQueue() {
  Node* temp = head;
  while (head != nullptr) {
    head = head->next;
    delete temp; 
    temp = head;
  }
}

template class PriorityQueue<std::string>;