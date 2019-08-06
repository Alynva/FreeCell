#ifndef FILA_H
#define FILA_H

#include <iostream> //cout
#include <random> //random_device
#include <cstdlib> // rand

using namespace std;

template<class T>
class Node {
	public:
		T value;
		Node* next;
		
		Node():next(this){};
		Node(const T val): value(val), next(this){};
};

template<class T>
class Queue {
	protected:
		Node<T> *atual, *ultimo;
		int size;

	public:
		Queue():size(0) {};
		~Queue() { this->clear(); };
	
		bool isEmpty() const { return !size; };
		void push(const T, bool&);
		bool pop(T&);
		void clear();
		int getSize() const;
};

template<class T>
inline void Queue<T>::push(const T element, bool& check){
	Node<T> *aux = new Node<T>;
	aux->value = element;
	aux->next = NULL;
    ultimo->next = aux;
	ultimo = aux;
	size++;
	aux = NULL;
	check = true;
	// SDL_Log("Tentativa de push em Queue; R: %c", check ? 's' : 'n');
}

template<class T>
inline bool Stack<T>::pop(T& element) {
	if (!this->isEmpty()){
		Node<T> *aux = atual;
		element = atual->value;
		atual = atual->next;
		delete(aux);
		size--;
		aux = NULL;
		return true;
	}
	return false;
}

template<class T>
inline void Queue<T>::clear() {
	while (!isEmpty()) {
		T a;
		this->pop(a);
	}
}

template<class T>
inline int Queue<T>::getSize() const {
	return size;
}

#endif
