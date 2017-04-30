#ifndef NODE_H
#define NODE_H

template<class T>
class Node {
	protected:
		T element;
		Node<T>* next;
	
	public:
		Node();
		Node(T);
		Node(const Node<T>&);
		~Node(){};
		void setNext(Node<T>&);
		Node<T>* getNext() const;
		T getElement() const;
};

template<class T>
Node<T>::Node() {}

template<class T>
Node<T>::Node(T elementVal) {
	this->element = elementVal;
	this->next = nullptr;
}

template<class T>
Node<T>::Node(const Node<T>& copyNode){
	this->element = copyNode.getElement();
	this->next = copyNode.getNext();
}

template<class T>
void Node<T>::setNext(Node<T>& nextVal) {
	this->next = &nextVal;
}

template<class T>
Node<T>* Node<T>::getNext() const {
	return this->next;
}

template<class T>
T Node<T>::getElement() const {
	return  this->element;
}

template <class T>
class Stack {
	protected:
		Node<T>* stack_ptr;
		int size;
	
	public:
		Stack();
		~Stack(){};
		void push(const T&);
		bool pop(T&);
		void clear();
		bool isEmpty() const;
		int getSize() const;
		Node<T> peek() const;
};

template<class T>
Stack<T>::Stack() {
	this->stack_ptr = new Node<T>();
	this->size = 0;
}

template<class T>
void Stack<T>::push(const T& pushValue) {
	Node<T>* aux = new Node<T>(pushValue);
	aux->setNext(*stack_ptr);
	this->stack_ptr = aux;
	this->size++;
}

template<class T>
bool Stack<T>::pop(T& popValue) {
	if(!this->isEmpty()) {
		Node<T>* aux = new Node<T>(*this->stack_ptr);
		popValue = aux->getElement();
		delete this->stack_ptr;
		this->stack_ptr = new Node<T>(*aux->getNext());
		this->size--;
		return true;
	}
	return false;
}

template<class T>
void Stack<T>::clear() {
	while (!this->isEmpty()) {
		Node<T>* aux = new Node<T>(*this->stack_ptr);
		delete this->stack_ptr;
		this->stack_ptr = new Node<T>(*aux->getNext());
		this->size--;
	}
}

template<class T>
bool Stack<T>::isEmpty() const {
	if(!this->stack_ptr->getNext()) {
		return true;
	}
	return false;
}

template<class T>
int Stack<T>::getSize() const {
	return this->size;
}

template<class T>
Node<T> Stack<T>::peek() const {
	return *this->stack_ptr;
}

#endif
