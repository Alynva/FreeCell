#ifndef CARTA_H
#define CARTA_H

#include "textura.h"

class Carta {
	int value;
	char suit;
	Textura gTexture;
	
	public:
	Carta(int, SDL_Renderer*);
	
	void render();
	
	int getValue();
	char getSuit();
};

#endif
