/*
	Classe responsável por facilitar o uso das texturas SDL.
	
	Declaração: o construtor sem parâmetros não inicializa nada, enquanto que o que recebe seis parâmetros, uma string, um renderizador do SDL e quatro inteiros, cria a textura, utilizando os dois primeiros inteiros para a posição e os outros dois para o tamanho.
	Métodos:
		setSize: recebe dois inteiros, x e y, respectivamente, e muda a posição da carta, usando os valores de x e y.
		setPosition: recebe dois inteiros, h e w, altura e largura, respectivamente, e muda o tamanho da carta, usando os valores de h e w.
		render: renderiza a carta na janela principal.
	Detalhes:
*/	

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

	void setSize(int, int);
	void setPosition(int, int);
	void render();
};

#endif
