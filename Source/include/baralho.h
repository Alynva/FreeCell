/*
	Classe relacionada ao baralho.
	
	Declaração: Os parâmetros de construção são um inteiro especificando a quantidade de cartas e um renderizador do SDL para a criação das cartas.
	Métodos:
		generate: recebe um inteiro para a quantidade de cartas e gera um novo baralho.
		randomize: "embaralha" o baralho, randomizando a lista.
	Detalhes:
		Seria bom trocar o vetor deck, por uma variável da pilha protótipo, que já tem uma função randomize.
*/

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
