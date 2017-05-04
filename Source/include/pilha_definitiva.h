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
			Node<Carta>* aux = new(Node<Carta>);
			aux->value = pushValue;
			aux->dir = &header;
			aux->esq = header.esq;
			header.esq->dir = aux;
			header.esq = aux;
			this->size++;
		}
		else{
			if(pushValue.getValue() == this->peek().value.getValue()+1){
				if(!this->isDifferentColor(pushValue,this->peek().value)){
					Node<Carta>* aux = new(Node<Carta>);
					aux->value = pushValue;
					aux->dir = &header;
					aux->esq = header.esq;
					header.esq->dir = aux;
					header.esq = aux;
					this->size++;
					this->peek().value.setPosition(this->getCoord());
					return true;
				}
			}
		}
	return false;
}

#endif
