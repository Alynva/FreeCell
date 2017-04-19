#ifndef PILHA_INTERMEDIARIA
#define PILHA_INTERMEDIARIA

#include "pilha_inteligente.h"

class PilhaIntermediaria : public PilhaInteligente{
	public:
		PilhaIntermediaria();
		bool push(const Carta&);
};

//TODO: Implementar push() para lista encadeada
bool PilhaIntermediaria::push(const Carta& pushValue){
	if(!this->isFull()){
		if(pushValue.getValue() == this->peek().getValue()-1){
			if(pushValue.getSuit() != this->peek().getSuit()){
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
