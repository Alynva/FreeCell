/*
	Classe responsável pelas cartas.

	Declaração: A construção recebe dois parâmetros, um inteiro, que é usado para definir qual é o valor e o naipe da carta, e um renderizador do SDL, para renderizar as cartas.
	Métodos:
		renderCard: renderiza a carta na janela principal.
		getValue: retorna o valor da carta (Ás, dois, três, ..., damas, valete, reis).
		getSuit: retorna o naipe da carta (Paus = A, Copas = B, Espadas = C, Ouros = D).
		getTexture: retorna a textura da carta (não está sendo utilizada pra nada no momento, poderia ser removido).
		setPosition: recebe dois inteiros, x e y, respectivamente, e muda a posição da carta na tela, utilizando os parâmetros.
	Detalhes:
*/

#ifndef CARTA_H
#define CARTA_H

#include "textura.h"

class Carta {
	int value;
	char suit;
	Textura gTexture;
	bool stateHover;
	Textura blurTexture;

	public:
	Carta(); // meio inútil, mas é necessário para poder declarar a carta sem especificar parâmetros.
	Carta(const Carta&);
	Carta(int, SDL_Renderer*);

	void render();

	int getValue() const;
	char getSuit() const;
	Textura getTexture() const;
	void setPosition(SDL_Point);
	bool isInside(SDL_Point) const;
	void setStateHover(bool);
};

#endif
