#ifndef PILHA_DEFINITIVA
#define PILHA_DEFINITIVA

#define CARD_WIDTH 100 // largura final do fundo da pilha
#define CARD_HEIGHT 156 // altura final do fundo da pilha

#include "pilha_inteligente.h"

class PilhaDefinitiva : public PilhaInteligente {
	public:
		PilhaDefinitiva() {};
		bool push(Carta&);
		bool setTexture(SDL_Renderer*);
};

bool PilhaDefinitiva::push(Carta& pushValue) {
	if (this->isEmpty()) {
		Node<Carta>* aux = new(Node<Carta>);
		aux->value = pushValue;
		aux->dir = &header;
		aux->esq = header.esq;
		header.esq->dir = aux;
		header.esq = aux;
		this->size++;
	} else {
		if (pushValue.getValue() == this->peek().value.getValue()+1) {
			if (!this->isDifferentColor(pushValue,this->peek().value)) {
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

bool PilhaDefinitiva::setTexture(SDL_Renderer* renderer) {
	this->backTexture = Textura("../textures/pilhaDefinitiva.png", renderer, this->coord.x, this->coord.y, 69, 100);
	int w = CARD_WIDTH, h = CARD_HEIGHT;
	if (!SDL_QueryTexture(this->backTexture.getTexture(), NULL, NULL, &w, &h)) {
		return true;
	}
	return false;
}

#endif
