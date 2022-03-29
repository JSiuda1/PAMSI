#pragma once

template<typename Type>
class LinkedList { //lifo
	template <typename Type>
	struct Node {
		Type data;
		Node* next;
	};
	
	Node<Type>* head;
	Node<Type>* tail;

public:
	LinkedList();
	bool push(const Type & data);
	bool pop(Type & var);
	bool isEmpty() const;
	int size() const;
	bool getElement(const int & elem, Type& data);
	void print() const;
	~LinkedList();
};

template <typename Type>
LinkedList<Type>::LinkedList() {
	head = nullptr;
	tail = nullptr;
}

template <typename Type>
bool LinkedList<Type>::push(const Type & data) {
	try {
		Node<Type>* tmp = head;
		Node<Type>* newElement = new Node<Type>;
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
		return false;
	}

	return true;
}

template <typename Type>
bool LinkedList<Type>::pop(Type & var) {
	Node<Type>* tmp = head;

	if (head == nullptr) {
		return false;
	}
	else if (head == tail) {
		tail = nullptr;
	}
	
	head = head->next;
	var = tmp->data;
	
	delete tmp;

	return true;
}

template <typename Type>
bool LinkedList<Type>::isEmpty() const{
	return head == nullptr ? true : false;
}

template <typename Type>
int LinkedList<Type>::size() const {
	int size = 0;
	Node<Type>* tmp = head;
	
	while (tmp != nullptr) {
		tmp = tmp->next;
		size += 1;
	}

	return size;
}

template <typename Type>
bool LinkedList<Type>::getElement(const int & elem, Type& data) {
	Node<Type>* temp = head;
	Node<Type>* delTemp = nullptr;
	if (size() < elem || elem < 0) {
		return false;
	}

	if (elem == 0) {
		data = temp->data;
		delTemp = temp;
		head = temp->next;
		delete delTemp;
	}
	else {
		for (int i = 0; i < (elem - 1); ++i) {
			temp = temp->next;
		}
		data = temp->next->data;
		delTemp = temp->next;
		temp->next = delTemp->next;

		delete delTemp;
	}

	return true;
}


template <typename Type>
void LinkedList<Type>::print() const {
	Node<Type>* temp = head;
	while (temp != nullptr) {
		std::cout << temp->data << std::endl;
		temp = temp->next;
	}
}

template <typename Type>
LinkedList<Type>::~LinkedList() {
	Node<Type>* tmp = head;

	while (head != nullptr) {
		head = head->next;
		delete tmp;
		tmp = head;
	}
	tail = nullptr;
}