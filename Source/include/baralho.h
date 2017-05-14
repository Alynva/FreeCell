/*
	Classe relacionada ao baralho.

	Declaração: O único parâmetro de construção é um renderizador do SDL para a criação das cartas.
	Métodos:
		generate: gera um novo baralho e logo em seguida, o embaralha.
		randomize: "embaralha" o baralho, randomizando a lista.
	Detalhes:
		Como a pilha protótipo é estática, é necessário especificar um tamanho máximo para a pilha. Como estamos utilizando um baralho comum, o tamanho máximo será 52.
*/

#ifndef BARALHO_H
#define BARALHO_H

#include "pilha_inteligente.h"
#include <cstdlib> // srand, rand
#include <ctime> // time

#define MAX_CARD 52
#define MAX_ITER_RANDOM 5000
#define MIN_ITER_RANDOM	500

class Baralho {
	PilhaInteligente deck;
	SDL_Renderer* gRenderer;

	public:
		Baralho();
		
		void setTexture(SDL_Renderer*);
		void generate();
		void randomize();
	
		bool getCard(Carta&);
};

#endif
