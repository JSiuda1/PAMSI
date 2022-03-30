#pragma once

#include <iostream>

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

template <typename Type>
LinkedList<Type>::LinkedList() {
	head = nullptr;
	tail = nullptr;
}

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
	}catch(std::bad_alloc & e){
		throw;
	}
}

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
		else { //jedyne co usprawni�o tail
			tail->next = newElement;
			tail = newElement;
		}
	}
	catch (std::bad_alloc& e) {
		throw;
	}
}

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

template <typename Type>
bool LinkedList<Type>::isEmpty() const{
	return head == nullptr ? true : false;
}

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

template <typename Type>
Type LinkedList<Type>::getElement(const int & elem) {
	Node* temp = head;
	Node* delTemp = nullptr;
	Type var = {};

	if (size() < elem || elem < 0) {
		throw std::invalid_argument("Elem greater than queue size or zero!");
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

template <typename Type>
void LinkedList<Type>::clear(){
	Node* tmp = head;

	while (head != nullptr) {
		head = head->next;
		delete tmp;
		tmp = head;
	}
	tail = nullptr;
}


template <typename Type>
void LinkedList<Type>::print() const {
	Node* temp = head;
	while (temp != nullptr) {
		std::cout << temp->data << std::endl;
		temp = temp->next;
	}
}

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