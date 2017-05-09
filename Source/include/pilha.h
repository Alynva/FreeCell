#ifndef PILHA_H
#define PILHA_H

#define MAX_ITER_RANDOM 500
#define MIN_ITER_RANDOM 50

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
		void randomize();
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
inline void Stack<T>::randomize() {
	random_device seed;
	srand(seed());
	int iter = rand()%(MAX_ITER_RANDOM-MIN_ITER_RANDOM)+MIN_ITER_RANDOM;
	while (iter > 0) {
		int it1 = rand()%size+1;
		Node<T>* elem = &header;
		while (it1 > 0) {
			elem = elem->dir;
			it1--;
		}
		Node<T> aux = *elem;
		elem->dir->esq = aux.esq;
		elem->esq->dir = aux.dir;
		elem->dir = &header;
		elem->esq = header.esq;
		header.esq->dir = elem;
		header.esq = elem;
		iter--;
	}
}

template<class T>
Node<T> Stack<T>::peek() const {
	return *header.esq;
}

#endif
