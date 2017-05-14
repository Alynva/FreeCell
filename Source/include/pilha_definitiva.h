#ifndef PILHA_DEFINITIVA
#define PILHA_DEFINITIVA

#define CARD_WIDTH 100 // largura final do fundo da pilha
#define CARD_HEIGHT 156 // altura final do fundo da pilha

#include "pilha_inteligente.h"

class PilhaDefinitiva : public PilhaInteligente {
	public:
		PilhaDefinitiva() {};
		virtual void pushChild(const Carta, bool&);
		bool setTexture(SDL_Renderer*);
		void organize();
		virtual bool canBeMoved(Carta *) const;
		virtual bool canPush(Carta, Carta) const;
};

void PilhaDefinitiva::pushChild(const Carta pushValue, bool& check) {
	if (this->isEmpty() && pushValue.getValue() == 1) {
		Node<Carta>* aux = new(Node<Carta>);
		aux->value = pushValue;
		aux->dir = &header;
		aux->esq = header.esq;
		header.esq->dir = aux;
		header.esq = aux;
		this->size++;
		check = true;
	} else if (pushValue.getValue() == this[0][0]->value.getValue() + 1 && pushValue.getSuit() == this[0][0]->value.getSuit()) {
		Node<Carta>* aux = new(Node<Carta>);
		aux->value = pushValue;
		aux->dir = &header;
		aux->esq = header.esq;
		header.esq->dir = aux;
		header.esq = aux;
		this->size++;
		this->peek()->dir->value.setPosition(this->getCoord());
		check = true;
	} else
		check = false;
	SDL_Log("Tentativa de pushChild em PilhaDefinitiva; R: %c", check ? 's' : 'n');
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
	for (int i = 0; i < this->getSize(); i++) {
		this[0][i]->value.setPosition(this->coord);
	}
}

bool PilhaDefinitiva::canBeMoved(Carta * c) const {
	return false;
}

bool PilhaDefinitiva::canPush(Carta c1, Carta c2) const {
	SDL_Log("Tentativa de canPush em PilhaDefinitiva; R: %c", (c1.getValue() + 1 == c2.getValue() && c1.getSuit() == c2.getSuit()) ? 's' : 'n');
	return (c1.getValue() + 1 == c2.getValue() && c1.getSuit() == c2.getSuit());
}

#endif
