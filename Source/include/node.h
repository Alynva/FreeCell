#ifndef NODE_H
#define NODE_H

template<class T>
class Node{
private:
	T element;
	Node* next;

public:
  Node(T);
  ~Node(){delete next;};
	void setNext(Node*);
  Node* getNext() const;
  T getElement() const;
};

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

template<class T>
class Stack{
private:
  Node* stack_ptr;
  int size;

public:
  Stack();
  void push(const T&);
  bool pop(T&);
  bool isEmpty() const;
  int getSize() const;
};

template<class T>
Stack<T>::Stack(){
  this->stack_ptr = NULL;
  size = 0;
}

template<class T>
void Stack<T>::push(const T& pushValue){
  Node* aux = new Node(pushValue);
  aux.setNext(stack_ptr);
  this->stack_ptr.setNext(aux);
  this->tamanho++;
}

/*template<class T>
bool Stack<T>::pop(T& popValue){
  if(!this->isEmpty()){
    Node* aux;
    popValue = this->stack_ptr->next->element;
    aux = this->stack_ptr;
    return true;
  }
  return false;
}*/

template<class T>
bool Stack<T>::isEmpty() const{
  if(!this->stack_ptr){
    return true;
  }
  return false;
}

template<class T>
int Stack<T>::getSize() const{
  return this->size;
};
#endif
