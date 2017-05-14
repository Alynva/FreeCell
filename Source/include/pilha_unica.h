#ifndef PILHA_UNICA
#define PILHA_UNICA

#include "pilha_inteligente.h"

class PilhaUnica : public PilhaInteligente {
	public:
		PilhaUnica() {};
		virtual void pushChild(const Carta, bool&);
		virtual bool canBeMoved(Carta *) const;
		virtual bool canPush(Carta, Carta) const;
};

void PilhaUnica::pushChild(const Carta pushValue, bool& check) {
	if (this->isEmpty()) {
		Node<Carta>* aux = new(Node<Carta>);
		aux->value = pushValue;
		aux->dir = &header;
		aux->esq = header.esq;
		header.esq->dir = aux;
		header.esq = aux;
		this->size++;
		
		check = true;
	} else
		check = false;
	SDL_Log("Tentativa de pushChild em PilhaUnica; R: %c", check ? 's' : 'n');
}

bool PilhaUnica::canBeMoved(Carta * c) const {
	return true;
}

bool PilhaUnica::canPush(Carta c1, Carta c2) const {
	return this->isEmpty();
}

#endif
