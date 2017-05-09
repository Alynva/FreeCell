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
	this->deck.randomize();
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
