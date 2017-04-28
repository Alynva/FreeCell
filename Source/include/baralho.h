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

#define MAX_CARD 52

class Baralho {
	PilhaInteligente deck;
	SDL_Renderer* gRenderer;

	public:
	Baralho(SDL_Renderer*);

	void generate();
	void randomize();

	bool getCard(Carta&);
	
	// M�todos criados apenas para teste. A classe que realmente � renderizada,
	// organizada e calculada se est� dentro ou fora � a Pilha, que por hora eu
	// adicionei na classe m�e mas depois poder� ser apenas das PilhaIntermedi-
	// aria e PilhaDefinitiva.
	void render();
	void organize();
	bool isInside(SDL_Point);
};

#endif
