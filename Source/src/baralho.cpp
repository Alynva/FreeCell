#include "../include/baralho.h"

Baralho::Baralho(SDL_Renderer* renderer) {
	this->deck.setTexture(renderer);
	this->gRenderer = renderer;
	for (int i = 1; i <= MAX_CARD; i++) {
		this->deck.push(Carta(i, this->gRenderer));
	}
	this->randomize();
}

void Baralho::generate() {
	this->deck.clear();
	for (int i = 1; i <= MAX_CARD; i++) {
		this->deck.push(Carta(i, this->gRenderer));
	}
}

void Baralho::randomize() {
	srand(time(NULL));
	int iter = rand()%(MAX_ITER_RANDOM-MIN_ITER_RANDOM)+MIN_ITER_RANDOM;
	while(iter > 0){
		int i = rand()%this->deck.getSize();
		Node<Carta>* elem = this->deck[i];
		Node<Carta> aux = *elem;
		elem->dir->esq = aux.esq;
		elem->esq->dir = aux.dir;
		elem->dir = this->deck[0]->esq;
		elem->esq = this->deck[-1];
		this->deck[-1]->dir = elem;
		this->deck[0]->esq->esq = elem;
		iter--;
	}
}

bool Baralho::getCard(Carta& card) {
	if (this->deck.pop(card))
		return true;
	return false;
}

void Baralho::render() {
	this->deck.render();
}

void Baralho::organize() {
	this->deck.organize();
}

bool Baralho::isInside(SDL_Point point) {
	return this->deck.isInside(point);
}
