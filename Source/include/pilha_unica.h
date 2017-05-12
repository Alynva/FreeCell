#ifndef PILHA_UNICA
#define PILHA_UNICA

#include "pilha_inteligente.h"

class PilhaUnica : public PilhaInteligente {
	public:
		PilhaUnica() {};
		bool push(Carta&);
		bool isDifferentColor(Carta, Carta) const;
};

bool PilhaUnica::push(Carta& pushValue) {
	if (this->isEmpty()) {
		Node<Carta>* aux = new(Node<Carta>);
		aux->value = pushValue;
		aux->dir = &header;
		aux->esq = header.esq;
		header.esq->dir = aux;
		header.esq = aux;
		this->size++;
		
		return true;
	}
	return false;
}
bool PilhaUnica::isDifferentColor(Carta c1, Carta c2) const {
	return false;
}

#endif
