#ifndef PILHA_DEFINITIVA
#define PILHA_DEFINITIVA

#include "pilha_inteligente.h"

class PilhaDefinitiva : public PilhaInteligente{
	public:
		PilhaDefinitiva();
		bool push(Carta&);
		void setTexture(SDL_Renderer* renderer) {this->backTexture = Textura("../textures/pilhaDefinitiva.png", renderer, this->coord.x, this->coord.y, 69, 100);}
};

//PilhaDefinitiva::PilhaDefinitiva() : PilhaInteligente(){}

bool PilhaDefinitiva::push(Carta& pushValue){
		if(this->isEmpty()){
			Node<Carta>* aux = new Node<Carta>(pushValue);
			aux->setNext(*stack_ptr);
			this->stack_ptr = aux;
			this->size++;
		}
		else{
			if(pushValue.getValue() == this->peek().getElement().getValue()+1){
				if(!this->isDifferentColor(pushValue,this->peek().getElement())){
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
