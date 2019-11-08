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
		bool stateHover;

	public:
		PilhaInteligente();
		virtual void pushChild(Carta c, bool& check) {
			this->push(c, check);
		};
		SDL_Point getCoord() const { return this->coord; };
		bool setTexture(SDL_Renderer*);
		bool setPosition(SDL_Point);
		SDL_Point getPosition() const;
		void render();
		void organize();
		bool isInside(SDL_Point);
		bool isDifferentColor(Carta, Carta) const;
		Node<Carta>* operator[](int) const;
		void setStateHover(bool);
		virtual bool canBeMoved(Carta *) const;
		virtual bool canPush(Carta, Carta) const;
};

#endif
