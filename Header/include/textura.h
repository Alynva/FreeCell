#ifndef TEXTURA_H
#define TEXTURA_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>

class Textura {
	SDL_Rect recFormat;
	SDL_Texture* pTexture;
	SDL_Renderer* pRenderer;
	std::string pPath;
	
	SDL_Texture* loadTexture();
	public:
	Textura();
	Textura(std::string, SDL_Renderer*, int, int, int, int);
	
	void render();
};

#endif
