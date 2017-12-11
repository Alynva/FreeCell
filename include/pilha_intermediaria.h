#ifndef PILHA_INTERMEDIARIA
#define PILHA_INTERMEDIARIA

#include "pilha_inteligente.h"

class PilhaIntermediaria : public PilhaInteligente {
	public:
		PilhaIntermediaria() {};
		virtual void pushChild(const Carta, bool&);
		virtual bool canBeMoved(Carta *) const;
		virtual bool canPush(Carta, Carta) const;
};

void PilhaIntermediaria::pushChild(const Carta pushValue, bool& check) {
	// SDL_Log("%i%c > %i%c", this->peek()->previous->previous->value.getValue(), this->peek()->previous->previous->value.getSuit(), pushValue.getValue(), pushValue.getSuit());
	if (this->isEmpty()) {
		Node<Carta>* aux = new(Node<Carta>);
		aux->value = pushValue;
		aux->next = &header;
		aux->previous = header.previous;
		header.previous->next = aux;
		header.previous = aux;
		this->size++;
		check = true;
	} else if (pushValue.getValue() == this->peek()->previous->previous->value.getValue() - 1 && this->isDifferentColor(pushValue, this->peek()->previous->previous->value)) {
		Node<Carta>* aux = new(Node<Carta>);
		aux->value = pushValue;
		aux->next = &header;
		aux->previous = header.previous;
		header.previous->next = aux;
		header.previous = aux;
		this->size++;
		this->peek()->value.setPosition(this->getCoord());
		check = true;
	} else
		check = false;
	// SDL_Log("Tentativa de pushChild em PilhaIntermediaria; R: %c", check ? 's' : 'n');
}

bool PilhaIntermediaria::canBeMoved(Carta * c) const {
	bool isDifferent = false;
	int i;
	for (i = 0; i < this->getSize(); i++) {
		if (&(this[0][i]->value) == c) {
			isDifferent = true;
			break;
		}
	}
	while (i < this->getSize() - 1 && isDifferent) {
		isDifferent = this->isDifferentColor(this[0][i]->value, this[0][i+1]->value) && this[0][i]->value.getValue() == this[0][i+1]->value.getValue() + 1;
		i++;
	}
	return isDifferent;
}

bool PilhaIntermediaria::canPush(Carta c1, Carta c2) const {
	return (this->isDifferentColor(c1, c2) && c1.getValue() == c2.getValue() + 1);
}

#endif
