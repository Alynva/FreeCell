#ifndef NODE_H
#define NODE_H

template<class T>
class Node {
	private:
		T element;
		Node* next;
	
	public:
		Node(T);
		~Node();
		void setNext(Node*);
		Node* getNext() const;
		T getElement() const;
};

template<class T>
Node<T>::~Node() {
	delete this->next;
}

template<class T>
Node<T>::Node(T elementVal) {
	this->element = elementVal;
	this->setNext(NULL);
}s

template<class T>
void Node<T>::setNext(Node* nextVal) {
	this->next = nextVal;
}

template<class T>
Node* Node<T>::getNext() const {
	return this->next;
}

template<class T>
T Node<T>::getElement() const {
	return  this->element;
}

#endif
