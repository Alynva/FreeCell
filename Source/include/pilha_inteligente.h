#ifndef PILHA_INTELIGENTE_H
#define PILHA_INTELIGENTE_H

#include "pilha.h"
#include "carta.h"

class PilhaIntermediaria : public Pilha{
public:
  bool push(const Carta&);
  int peekValue(){return this->stackPtr[top].getValue();};
  char peekSuit(){return this->stackPtr[top].getSuit();};
};

bool PilhaIntermediaria::push(const Carta& pushValue){
  if(!this->isFull()){
    if(pushValue.getValue() == this->peekValue()-1){
      //if(pushValue.getSuit != this->peekSuit()){
        this->stackPtr[++top] = pushValue;
        return true;
    //}
    }
  }
  return false;
}

class PilhaDefinitiva : public Pilha{
public:
  push(const Carta&);
  int peekValue(){return this->stackPtr[top].getValue();};
  char peekSuit(){return this->stackPtr[top].getSuit();};
};

bool PilhaIntermediaria::push(const Carta& pushValue){
  if(!this->isFull()){
    if(pushValue.getValue() == this->peekValue()+1){
      //if(pushValue.getSuit == this->peekSuit()){
        this->stackPtr[++top] = pushValue;
        return true;
    //}
    }
  }
  return false;
}

#endif
