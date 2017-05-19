#include "../include/baralho.h"


bool cab;
Baralho::Baralho():gRenderer(nullptr) {}

void Baralho::setTexture(SDL_Renderer* renderer) {
	this->deck.setTexture(renderer);
	this->gRenderer = renderer;
}

void Baralho::generate() {
	this->deck.clear();
	for (int i = 1; i <= MAX_CARD; i++) {
		this->deck.push(Carta(i, this->gRenderer), cab);
	}
}

void Baralho::randomize() {
	srand(time(NULL));
	int iter = rand()%(MAX_ITER_RANDOM-MIN_ITER_RANDOM)+MIN_ITER_RANDOM;
	while(iter > 0){
		int i = rand()%this->deck.getSize();
		Node<Carta>* elem = this->deck[i];
		Node<Carta> aux = *elem;
		elem->next->previous = aux.previous;
		elem->previous->next = aux.next;
		elem->next = this->deck[0]->previous;
		elem->previous = this->deck[-1];
		this->deck[-1]->next = elem;
		this->deck[0]->previous->previous = elem;
		iter--;
	}
}

bool Baralho::getCard(Carta& card) {
	if (this->deck.pop(card))
		return true;
	return false;
}
