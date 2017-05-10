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
		Node* dir;
		Node* esq;
		Node():dir(this), esq(this) {};
		Node(const T val): value(val), dir(this), esq(dir) {};
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

		void push(const T);
		bool pop(T&);
		void clear();
		int getSize() const;
		Node<T> peek() const;
};

template<class T>
inline void Stack<T>::push(const T element) {
	Node<T> *aux = new Node<T>;
	aux->value = element;
	aux->dir = &header;
	aux->esq = header.esq;
	header.esq->dir = aux;
	header.esq = aux;
	size++;
}

template<class T>
inline bool Stack<T>::pop(T& element) {
	if (isEmpty())
		return false;
	element = header.esq->value;
	Node<T> *aux = header.esq;
	header.esq = aux->esq;
	aux->esq = &header;
	delete(aux);
	size--;
	return true;
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
Node<T> Stack<T>::peek() const {
	return *header.esq;
}

#endif
