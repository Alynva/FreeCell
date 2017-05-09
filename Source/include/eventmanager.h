/*
	Classe responsável pelos eventos do SDL(cliques, botões do teclaso, finalização do programa, etc.).

	Declaração: O único parâmetro a ser passo é um ponteiro para uma variávl booleana, responsável por avisar o programa que o usuário deseja finalizá-lo.
	Métodos:
		update: checa todos os eventos na fila, e trata cada caso com um switch.
		mouseDown: chamado assim que um botão do mouse é pressionado.
		mouseUp: chamado assim que um botão do mouse é largado.
	Detalhes:
		Os valores do case vem da biblioteca SDL, portanto informações sobre os valores podem ser encontradas em https://wiki.libsdl.org/SDL_EventType;
*/

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "SDL2/SDL.h"
#include "pilha_inteligente.h"

class EventManager {
	SDL_Event handler;
	bool* quit;
	bool mousePressed;
	Stack<PilhaInteligente*> stacks;

	public:
	EventManager(bool*);

	void update();
	void mouseDown();
	void mouseUp();
	void mouseMove();
	void addStack(PilhaInteligente*);
};

#endif
