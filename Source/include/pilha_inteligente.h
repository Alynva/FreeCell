#ifndef PILHA_INTELIGENTE_H
#define PILHA_INTELIGENTE_H

#include "SDL2/SDL.h" // SDL_QueryTexture()
#include "pilha.h" // TAD base "pilha"
#include "carta.h" // texturas de carta e funcoes do baralho

#include <ctime> // time()
#include <cstdlib> // srand(), rand()

#define DIF_ALTURA 20 // diferenca de altura entre duas cartas
#define CARD_WIDTH 100 // largura final do fundo da pilha
#define CARD_HEIGHT 156 // altura final do fundo da pilha

class PilhaInteligente : public Stack<Carta> {
	private:
		SDL_Point coord;
		Textura backTexture;
		
	public:
		PilhaInteligente();
		bool setTexture(SDL_Renderer*);
		bool setPosition(SDL_Point);
		void randomize();
		void render();
		void organize();
		bool isInside(SDL_Point);
};

#endif

PilhaInteligente::PilhaInteligente() {
	this->coord = {0, 0};
}

bool PilhaInteligente::setTexture(SDL_Renderer* renderer) {
	this->backTexture = Textura("../textures/pilha.png", renderer, this->coord.x, this->coord.y, 69, 100);
	int w = CARD_WIDTH, h = CARD_HEIGHT;
	if(!SDL_QueryTexture(this->backTexture.getTexture(), NULL, NULL, &w, &h)){
		return true;
	}
	return false;
}

bool PilhaInteligente::setPosition(SDL_Point pos) {
	SDL_Point size;
//	SDL_GetWindowSize(gWindow, &size.x, &size.y);
	
//	if (pos.x > 0 && pos.y > 0 && pos.x + CARD_WIDTH < size.x && pos.y + CARD_HEIGHT < size.y) {
		this->coord = pos;
		
		this->organize();

		return true;
//	}
	return false;
}

void PilhaInteligente::randomize() {
	/*
	// Alynva: aguardando a implementação da sobrecarga do operador []
	
	
	srand(time(0));
	int S = this.getSize(), in, out;
	for (int i = 0; i < (rand() % (S * 10) + 50); i++) {
		do {
			in = rand() % S;
			out = rand() % S;
		} while(in == out);
		T aux = stack[out];
		stack[out] = stack[in];
		stack[in] = aux;
	}
	*/
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
	bool inside = false;
	
	Stack<Carta> p_temp;
	Carta c_temp;

	while (!this->isEmpty()) {
		this->pop(c_temp);
		p_temp.push(c_temp);
	}
	while (!p_temp.isEmpty()) {
		p_temp.pop(c_temp);
		if (!inside)
			inside = c_temp.isInside(point);
		this->push(c_temp);
	}

	return inside;
}
