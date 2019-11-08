#ifndef PILHA_AUXILIAR
#define PILHA_AUXLIAR

#include "pilha_inteligente.h"

class PilhaAuxiliar : public PilhaInteligente {
	public:
		PilhaAuxiliar() {};
		virtual void pushChild(const Carta, bool&);
		virtual bool canBeMoved(Carta *) const;
		virtual bool canPush(Carta, Carta) const;
};

void PilhaAuxiliar::pushChild(const Carta pushValue, bool& check) {
	if (this->isEmpty()) {
		Node<Carta>* aux = new(Node<Carta>);
		aux->value = pushValue;
		aux->next = &header;
		aux->previous = header.previous;
		header.previous->next = aux;
		header.previous = aux;
		this->size++;

		check = true;
	} else
		check = false;
}

bool PilhaAuxiliar::canBeMoved(Carta * c) const {
	return true;
}

bool PilhaAuxiliar::canPush(Carta c1, Carta c2) const {
	return this->isEmpty();
}

#endif
