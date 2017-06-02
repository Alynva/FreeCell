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
#include "button.h"

class EventManager {
	SDL_Event handler;
	bool* t_fullscreen;
	bool* quit;
	bool* play;
	SDL_Point* window_size;
	bool mouse_pressed;
	SDL_Point mouse_pos;
	
	Textura* logo;
	
	Stack<PilhaInteligente*> stacks;
	PilhaInteligente* stack_joining;
	PilhaInteligente* stack_hovered;
	Carta* card_hovered;
	PilhaInteligente* previous_stack;
	SDL_Point stack_offset;
	
	Stack<Button*> buttons;

	public:
		EventManager(bool*, bool*, bool*, SDL_Point*);
	
		void update();
		void mouseMove();
		void mouseLeftDown();
		void mouseLeftUp();
		void addLogo(Textura*);
		void clearLogo();
		void addStack(PilhaInteligente*);
		void clearStacks();
		void addButton(Button*);
		void clearButtons();
		void windowResized(int, int);
		void dClick(SDL_Point = {-10, -10});
};

#endif
