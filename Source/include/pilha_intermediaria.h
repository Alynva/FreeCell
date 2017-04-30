#ifndef PILHA_INTERMEDIARIA
#define PILHA_INTERMEDIARIA

#include "pilha_inteligente.h"

class PilhaIntermediaria : public PilhaInteligente{
	public:
		PilhaIntermediaria();
		bool push(Carta&);
};

bool PilhaIntermediaria::push(Carta& pushValue){
		if(this->isEmpty()){
			Node<Carta>* aux = new Node<Carta>(pushValue);
			aux->setNext(*stack_ptr);
			this->stack_ptr = aux;
			this->size++;
		}
		else{
			if(pushValue.getValue() == this->peek().getElement().getValue()-1){
				if(this->isDifferentColor(pushValue,this->peek().getElement())){
					Node<Carta>* aux = new Node<Carta>(pushValue);
					aux->setNext(*stack_ptr);
					this->stack_ptr = aux;
					this->size++;
					this->peek().getElement().setPosition(this->getCoord());
					return true;
				}
			}
		}
	return false;
}

#endif
