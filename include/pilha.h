#ifndef PILHA_H
#define PILHA_H

#include <iostream> //cout
#include <random> //random_device
#include <cstdlib> // rand

using namespace std;

template<class T>
class Node {
	public:
		T value;
		Node* next;
		Node* previous;
		Node():next(this), previous(this) {};
		Node(const T val): value(val), next(this), previous(next) {};
};

template<class T>
class Stack {
	protected:
		Node<T> header;
		int size;

	public:
		Stack():size(0) {};
		~Stack() { this->clear(); };
		bool isEmpty() const { return !size; };

		void push(const T, bool&);
		bool pop(T&);
		void clear();
		int getSize() const;
		Node<T>* peek() const;
};

template<class T>
inline void Stack<T>::push(const T element, bool& check){
	Node<T> *aux = new Node<T>;
	aux->value = element;
	aux->next = &header;
	aux->previous = header.previous;
	header.previous->next = aux;
	header.previous = aux;
	size++;
	check = true;
	// SDL_Log("Tentativa de push em Stack; R: %c", check ? 's' : 'n');
}

template<class T>
inline bool Stack<T>::pop(T& element) {
	if (!this->isEmpty()){
		element = header.previous->value;
		Node<T> *aux = header.previous;
		header.previous = aux->previous;
		aux->previous = &header;
		delete(aux);
		size--;
		return true;
	}
	return false;
}

template<class T>
inline void Stack<T>::clear() {
	while (!isEmpty()) {
		T a;
		this->pop(a);
	}
}

template<class T>
inline int Stack<T>::getSize() const {
	return size;
}

template<class T>
Node<T>* Stack<T>::peek() const {
	return header.next;
}

#endif
