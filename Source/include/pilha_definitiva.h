#ifndef PILHA_DEFINITIVA
#define PILHA_DEFINITIVA

#include "pilha_inteligente.h"

class PilhaDefinitiva : public PilhaInteligente{
	public:
		PilhaDefinitiva();
		bool push(const Carta&);
		void setTexture(SDL_Renderer* renderer) {this->backTexture = Textura("../textures/pilhaDefinitiva.png", renderer, this->coord.x, this->coord.y, 69, 100);}
};

//TODO: implementar push() para lista encadeada
bool PilhaDefinitiva::push(const Carta& pushValue){
	if(!this->isFull()){
		if(pushValue.getValue() == this->peek().getValue()+1){
			if(pushValue.getSuit() == this->peekSuit()){
				if(top != NULL){
					top++;
				} else {
					top = &stack[0];
				}
				//TODO:	element.setPosition(this->coord);
				*top = element;
				return true;
			}
		}
	}
	return false;
}

#endif
