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
		void organize();
};

bool PilhaDefinitiva::push(Carta& pushValue) {
	if (this->isEmpty() && pushValue.getValue() == 1) {
		Node<Carta>* aux = new(Node<Carta>);
		aux->value = pushValue;
		aux->dir = &header;
		aux->esq = header.esq;
		header.esq->dir = aux;
		header.esq = aux;
		this->size++;
		return true;
	} else {
		if (pushValue.getValue() == this->peek().dir->value.getValue()+1) {
			if (pushValue.getSuit() == this->peek().dir->value.getSuit()) {
				Node<Carta>* aux = new(Node<Carta>);
				aux->value = pushValue;
				aux->dir = &header;
				aux->esq = header.esq;
				header.esq->dir = aux;
				header.esq = aux;
				this->size++;
				this->peek().dir->value.setPosition(this->getCoord());
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

void PilhaDefinitiva::organize() {
	Stack<Carta> p_temp;
	Carta c_temp;

	while (!this->isEmpty()) {
		this->pop(c_temp);
		p_temp.push(c_temp);
	}
	while (!p_temp.isEmpty()) {
		p_temp.pop(c_temp);
		c_temp.setPosition(this->coord);
		this->push(c_temp);
	}
}

#endif
