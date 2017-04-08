#ifndef PILHA_H
#define PILHA_H

template <class T>
class Stack{
public:
    Stack(int s);
    ~Stack(){delete []stackPtr;};

    bool push(const T&);
    bool pop(T&);

    T peek(){return this->stackPtr[top];};
    bool isEmpty() const{return this->top == -1;};
    bool isFull() const{return this->top == size - 1;};

private:
    int size;
    int top;
    T *stackPtr;
};

template <class T>
Stack<T>::Stack(int s){
    this->size = (s > 0 ? s : 10);
    this->top = -1;
    this->stackPtr = new T[this->size];
}

template <class T>
bool Stack<T>::push(const T& pushValue){
    if (!this->isFull()){
        this->stackPtr[++top] = pushValue;
        return true;
    }
    return false;
}

template <class T>
bool Stack<T>::pop(T& popValue){
    if (!this->isEmpty()){
        popValue = this->stackPtr[top--];
        return true;
    }
    return false;
}
#endif
