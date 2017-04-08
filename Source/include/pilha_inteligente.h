#ifndef PILHA_INTELIGENTE_H
#define PILHA_INTELIGENTE_H

#include "SDL2/SDL.h" // SDL_QueryTexture()
#include "pilha.h" // TAD base "pilha"
#include "carta.h" // texturas de carta e funcoes do baralho

class PilhaInteligente : public Pilha{
  //TODO: mudar os setTexture() e qualquer coisa da SDL pra ca
};


class PilhaIntermediaria : public PilhaInteligente{
public:
  bool push(const Carta&);
};

bool PilhaIntermediaria::push(const Carta& pushValue){
  if(!this->isFull()){
    if(pushValue.getValue() == this->peek().getValue()-1){
      if(pushValue.getSuit() != this->peek().getSuit()){
        if(top != NULL){
          top++;
        } else {
          top = &stack[0];
        }
    //TODO:		element.setPosition(this->coord);
        *top = element;
        return true;
      }
    }
  }
  return false;
}

class PilhaDefinitiva : public PilhaInteligente{
public:
  bool push(const Carta&);
  void setTexture(SDL_Renderer* renderer) {this->backTexture = Textura("../textures/pilhaDefinitiva.png", renderer, this->coord.x, this->coord.y, 69, 100);}
};

bool PilhaIntermediaria::push(const Carta& pushValue){
  if(!this->isFull()){
    if(pushValue.getValue() == this->peek().getValue()+1){
      if(pushValue.getSuit() == this->peekSuit()){
        if(top != NULL){
          top++;
        } else {
          top = &stack[0];
        }
    //TODO:		element.setPosition(this->coord);
        *top = element;
        return true;
      }
    }
  }
  return false;
}

#endif
