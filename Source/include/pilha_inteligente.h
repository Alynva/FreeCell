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

template<>
class PilhaInteligente<Carta> : public Stack {
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

template<>
PilhaInteligente<Carta>::PilhaInteligente() {
	this->coord = {0, 0};
}

template<>
bool PilhaInteligente<Carta>::setTexture(SDL_Renderer* renderer) {
	this->backTexture = Textura("../textures/pilha.png", renderer, this->coord.x, this->coord.y, 69, 100);
	int w = CARD_WIDTH, h = CARD_HEIGHT;
	if(!SDL_QueryTexture(this->backTexture.getTexture(), NULL, NULL, &w, &h)){
		return true;
	}
	return false;
}

template<>
bool PilhaInteligente<Carta>::setPosition(SDL_Point pos) {
	this->coord = pos;

	return true; // Por hora, nao faz nenhuma verificacao de ser negativo ou ultrapassar a tela
}

template<>
void PilhaInteligente<Carta>::randomize() {
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

template<>
void PilhaInteligente<Carta>::render() {
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

template<>
void PilhaInteligente<Carta>::organize() {
	
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

template<>
bool PilhaInteligente<Carta>::isInside(SDL_Point point) {
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
		this->push(t_temp);
	}

	return inside;
}

#endif
