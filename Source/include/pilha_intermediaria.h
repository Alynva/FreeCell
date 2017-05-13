#ifndef PILHA_INTERMEDIARIA
#define PILHA_INTERMEDIARIA

#include "pilha_inteligente.h"

class PilhaIntermediaria : public PilhaInteligente {
	public:
		PilhaIntermediaria() {};
		void push(Carta&, bool&);
};

void PilhaIntermediaria::push(Carta& pushValue, bool& check) {
	check = false;
	if (this->isEmpty()) {
		Node<Carta>* aux = new(Node<Carta>);
		aux->value = pushValue;
		aux->dir = &header;
		aux->esq = header.esq;
		header.esq->dir = aux;
		header.esq = aux;
		this->size++;
		check = true;
	} else {
		if (pushValue.getValue() == this->peek().value.getValue()-1) {
			if (this->isDifferentColor(pushValue,this->peek().value)) {
				Node<Carta>* aux = new(Node<Carta>);
				aux->value = pushValue;
				aux->dir = &header;
				aux->esq = header.esq;
				header.esq->dir = aux;
				header.esq = aux;
				this->size++;
				this->peek().value.setPosition(this->getCoord());
				check = true;
			}
		}
	}
}

#endif
