#ifndef PILHA_INTELIGENTE_H
#define PILHA_INTELIGENTE_H

#include "SDL2/SDL.h" // SDL_QueryTexture()
#include "pilha.h" // TAD base "pilha"
#include "carta.h" // texturas de carta e funcoes do baralho
#include <algorithm> // random_shuffle()
//#include <ctime> // time()
//#include <cstdlib> // srand(), rand()


class PilhaInteligente : public Stack<Carta> {
	protected:
		SDL_Point coord;
		Textura backTexture;

	public:
		PilhaInteligente();
		SDL_Point getCoord() const {return this->coord;};
		bool setTexture(SDL_Renderer*);
		bool setPosition(SDL_Point);
		void randomize();
		void render();
		void organize();
		bool isInside(SDL_Point);
		bool isDifferentColor(Carta, Carta) const;
		Node<Carta>* operator[](int);
};

#endif
