#ifndef BARALHO_H
#define BARALHO_H

#include "carta.h"
#include <vector>

using namespace std;

class Baralho {
	vector<Carta> deck;
	SDL_Renderer* gRenderer;

	public:
	Baralho(int, SDL_Renderer*);

	void generate(int);
	void randomize();

	Carta getCard();
};

#endif
