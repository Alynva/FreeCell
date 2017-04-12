#ifndef NODE_H
#define NODE_H

template<class T>
class Node{
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
Node<T>::~Node(){
	delete this->next;
}

template<class T>
Node<T>::Node(T elementVal){
	this->element = elementVal;
	this->setNext(NULL);
}

template<class T>
void Node<T>::setNext(Node* nextVal){
	this->next = nextVal;
}

template<class T>
Node* Node<T>::getNext() const{
  return this->next;
}

template<class T>
T Node<T>::getElement() const{
  return  this->element;
}

class Stack{
private:
  Node* stack_ptr;
  int size;

public:
  Stack();
	~Stack();
  void push(const T&);
  bool pop(Node);
  bool isEmpty() const;
  int getSize() const;
};

Stack::Stack(){
  this->stack_ptr = NULL;
  this->size = 0;
}

Stack::~Stack(){
	delete this->stack_ptr;
}

template<class T>
void Stack::push(const T& pushValue){
  Node* aux = new Node<T>(pushValue);
  aux.setNext(stack_ptr);
  this->stack_ptr = *aux;
  this->tamanho++;
}

bool Stack::pop(Node popValue){
  if(!this->isEmpty()){
    Node* aux = this->stack_ptr;
    popValue = *this->stack_ptr;
		delete this->stack_ptr;
		this->stack_ptr = aux->next;
    return true;
  }
  return false;
}

bool Stack::isEmpty() const{
  if(!this->stack_ptr){
    return true;
  }
  return false;
}

int Stack::getSize() const{
  return this->size;
}

#endif
