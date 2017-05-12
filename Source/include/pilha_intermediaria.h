#ifndef PILHA_INTERMEDIARIA
#define PILHA_INTERMEDIARIA

#include "pilha_inteligente.h"

class PilhaIntermediaria : public PilhaInteligente {
	public:
		PilhaIntermediaria() {};
		bool push(Carta&);
};

bool PilhaIntermediaria::push(Carta& pushValue) {
	if (this->isEmpty()) {
		Node<Carta>* aux = new(Node<Carta>);
		aux->value = pushValue;
		aux->dir = &header;
		aux->esq = header.esq;
		header.esq->dir = aux;
		header.esq = aux;
		this->size++;
		return true;
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
				return true;
			}
		}
	}
	return false;
}

#endif
