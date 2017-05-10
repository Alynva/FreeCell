#include "../include/pilha_inteligente.h"

#define DIF_ALTURA 20 // diferenca de altura entre duas cartas
#define CARD_WIDTH 100 // largura final do fundo da pilha
#define CARD_HEIGHT 156 // altura final do fundo da pilha

PilhaInteligente::PilhaInteligente() : Stack<Carta>() {
	this->coord = {0, 0};
	this->stateHover = false;
}

bool PilhaInteligente::setTexture(SDL_Renderer* renderer) {
	this->backTexture = Textura("../textures/pilha.png", renderer, this->coord.x, this->coord.y, 69, 100);
	int w = CARD_WIDTH, h = CARD_HEIGHT;
	if (!SDL_QueryTexture(this->backTexture.getTexture(), NULL, NULL, &w, &h)) {
		return true;
	}
	return false;
}

bool PilhaInteligente::setPosition(SDL_Point pos) {
//	SDL_Point size;
//	SDL_GetWindowSize(gWindow, &size.x, &size.y);

//	if (pos.x > 0 && pos.y > 0 && pos.x + CARD_WIDTH < size.x && pos.y + CARD_HEIGHT < size.y) {
		this->coord = pos;
		this->backTexture.setPosition(this->coord);

		this->organize();

		return true;
//	}
//	return false;
}

SDL_Point PilhaInteligente::getPosition() const {
	return this->coord;
}

void PilhaInteligente::render() {
	this->backTexture.render();

	Stack<Carta> p_temp;
	Carta c_temp;

	while (!this->isEmpty()) {
		this->pop(c_temp);
		p_temp.push(c_temp);
	}
	while (!p_temp.isEmpty()) {
		p_temp.pop(c_temp);
		c_temp.render();
		this->push(c_temp);
	}
}

void PilhaInteligente::organize() {
	Stack<Carta> p_temp;
	Carta c_temp;

	int y = 0;
	while (!this->isEmpty()) {
		this->pop(c_temp);
		p_temp.push(c_temp);
	}
	while (!p_temp.isEmpty()) {
		p_temp.pop(c_temp);
		c_temp.setPosition({this->coord.x, this->coord.y + y});
		y += DIF_ALTURA;
		this->push(c_temp);
	}
}

bool PilhaInteligente::isInside(SDL_Point point) {
	SDL_Point position = this->backTexture.getPosition();
//	SDL_Log("P %i %i", position.x, position.y);
	SDL_Point size = this->backTexture.getSize();

	bool inside = ((point.x > position.x && point.x < position.x + size.x) &&
		(point.y > position.y && point.y < position.y + size.y));

	Node<Carta>* element = this->peek().dir;
	for (int i = 0; i < this->getSize(); i++) {
		element = element->dir;
		inside = inside || element->value.isInside(point);
	}

	// Alynva: N�O FUNCIONOU ISSO
//	for (int i = 0; i < this->getSize(); i++) {
//		inside = inside || this[1].isInside(point);
//	}

	return inside;
}

//Faz a verificacao de naipes para dizer se duas cartas sao da mesma cor
bool PilhaInteligente::isDifferentColor(Carta c1, Carta c2) const {
	if ((c1.getSuit() == 'A' || c1.getSuit() == 'C') && (c2.getSuit() == 'A' || c2.getSuit() == 'C'))
		return true;

	else if ((c1.getSuit() == 'B' || c1.getSuit() == 'D') && (c2.getSuit() == 'B' || c1.getSuit() == 'D'))
		return true;

	return false;
}

//P[x] deve retornar o node da posicao x, nao a carta da posicao x, que eh P[x]->getElement()
//P[-1] retorna o último elemento
Node<Carta>* PilhaInteligente::operator[](int index) const {
	if (size > index && index >= 0) {
		Node<Carta>* returnNode = header.dir;
		while (index > 0) {
			returnNode = returnNode->dir;
			index--;
		}
		return returnNode;
	} else if(index == -1) {
		return header.esq;
	}
	return nullptr;
}

void PilhaInteligente::setStateHover(bool state) {
	this->stateHover = state;
}

bool PilhaInteligente::canBeMoved(const Carta * c) const {
	/*bool isDifferent = false;
	int i;
	for (i = 0; i < this->getSize(); i++) {
		if (*(this[0][i]->value) == c) {
			isDifferent = true;
			break;
		}
	}
	while (i < this->getSize() - 1 && isDifferent) {
		isDifferent = this->isDifferentColor(this[0][i]->value, this[0][i+1]->value);
		i++;
	}
	return isDifferent;*/
	return true;
}
