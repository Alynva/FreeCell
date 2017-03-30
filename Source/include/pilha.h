#ifndef PILHA_H
#define PILHA_H

#include <iostream>
using namespace std;

template <class T>
class Stack{
public:
    Stack(int s){
        size = (s > 0 ? s : 10);
        top = -1;
        stackPtr = new T[size];
    }
    ~Stack(){delete []stackPtr;};

    bool push(const T& pushValue){
      if (!isFull()){
          stackPtr[++top] = pushValue;
          return true;
      }
      return false;
    };

    bool pop(T& popValue){
      if (!isEmpty()){
        popValue = stackPtr[top--];
        return true;
      }
      return false;
    };

    bool isEmpty() const{
      return top == -1;
    }
    bool isFull() const{
      return top == size - 1;
    };

private:
    int size;
    int top;
    T *stackPtr;
};

#endif
