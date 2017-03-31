#ifndef CARTA_H
#define CARTA_H

#include "textura.h"

class Carta {
	int value;
	char suit;
	Textura gTexture;

	public:
	Carta(int, SDL_Renderer*);

	void renderCard();

	int getValue();
	char getSuit();
	Textura getTexture();
	void setPosition(int, int);
};

#endif
