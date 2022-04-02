#pragma once

#include <iostream>

/**
 * @brief Linked list 
 * 
 * @tparam Type typ danych
 */
template<typename Type>
class LinkedList { //lifo
	struct Node {
		Type data;
		Node* next;
	};
	
	Node* head;
	Node* tail;

public:
	LinkedList();
	void addLast(const Type & data);
	void addFront(const Type & data);
	Type front();
	bool isEmpty() const;
	int size() const;
	Type getElement(const int & elem);
	void clear();
	void print() const;
	~LinkedList();
};

/**
 * @brief Construct a new Linked List< Type>:: Linked List object
 * 
 * @tparam Type typ danych
 */
template <typename Type>
LinkedList<Type>::LinkedList() {
	head = nullptr;
	tail = nullptr;
}

/**
 * @brief dodaje dane na początek listy
 * 
 * @tparam Type typ danych
 * @param data dane
 */
template <typename Type>
void LinkedList<Type>::addFront(const Type & data){
	try{
		Node* newElement = new Node;
		newElement->data = data;
		newElement->next = nullptr;

		if(head == nullptr){
			head = newElement;
		}else{
			newElement->next = head;
			head = newElement;
		}
	}catch(std::bad_alloc e){
		throw;
	}
}

/**
 * @brief dodaje dane na koniec listy
 * 
 * @tparam Type typ danych
 * @param data dane
 */
template <typename Type>
void LinkedList<Type>::addLast(const Type & data) {
	try {
		Node* tmp = head;
		Node* newElement = new Node;
		newElement->data = data;
		newElement->next = nullptr;

		if (tmp == nullptr) {
			head = newElement;
			tail = newElement;
		}
		else {
			tail->next = newElement;
			tail = newElement;
		}
	}
	catch (std::bad_alloc e) {
		throw;
	}
}

/**
 * @brief Zwraca element z początku listy
 * 
 * @tparam Type typ danych
 * @return Type dane
 */
template <typename Type>
Type LinkedList<Type>::front() {
	Node* tmp = head;
	Type var = {};

	if (head == nullptr) {
		throw std::logic_error("Linked list is empty!");
	}
	else if (head == tail) {
		tail = nullptr;
	}
	
	head = head->next;
	var = tmp->data;
	delete tmp;

	return var;
}

/**
 * @brief sprawdzenie czy lista jest pusta
 * 
 * @tparam Type typ danych
 * @return true 
 * @return false 
 */
template <typename Type>
bool LinkedList<Type>::isEmpty() const{
	return head == nullptr ? true : false;
}

/**
 * @brief zwraca rozmiar listy
 * 
 * @tparam Type typ danych
 * @return int ilosc elementow
 */
template <typename Type>
int LinkedList<Type>::size() const {
	int size = 0;
	Node* tmp = head;
	
	while (tmp != nullptr) {
		tmp = tmp->next;
		size += 1;
	}

	return size;
}

/**
 * @brief zwraca wybrany element z listy
 * 
 * @tparam Type typ danych
 * @param elem numer elementu
 * @return Type dane
 */
template <typename Type>
Type LinkedList<Type>::getElement(const int & elem) {
	Node* temp = head;
	Node* delTemp = nullptr;
	Type var = {};

	if (size() < elem || elem < 0) {
		throw std::invalid_argument("Elem greather than queue size or zero!");
	}

	if (elem == 0) {
		var= temp->data;
		delTemp = temp;
		head = temp->next;
		delete delTemp;
	}
	else {
		for (int i = 0; i < (elem - 1); ++i) {
			temp = temp->next;
		}
		var = temp->next->data;
		delTemp = temp->next;
		temp->next = delTemp->next;

		delete delTemp;
	}

	return var;
}

/**
 * @brief czyszczenie listy
 * 
 * @tparam Type typ danych
 */
template <typename Type>
void LinkedList<Type>::clear(){ //chyba nie potrzebne
	Node* tmp = head;

	while (head != nullptr) {
		head = head->next;
		delete tmp;
		tmp = head;
	}
	tail = nullptr;
}

/**
 * @brief wypisuje w konsoli elementy kolejki
 * 
 * @tparam Type typ danych
 */
template <typename Type>
void LinkedList<Type>::print() const {
	Node* temp = head;
	while (temp != nullptr) {
		std::cout << temp->data << std::endl;
		temp = temp->next;
	}
}

/**
 * @brief Destroy the Linked List< Type>:: Linked List object
 * 
 * @tparam Type typ danych
 */
template <typename Type>
LinkedList<Type>::~LinkedList() {
	Node* tmp = head;

	while (head != nullptr) {
		head = head->next;
		delete tmp;
		tmp = head;
	}
	tail = nullptr;
}