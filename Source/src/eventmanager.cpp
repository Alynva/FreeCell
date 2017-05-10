#include "../include/eventmanager.h"
#include <iostream>

EventManager::EventManager(bool* mQuit):quit(mQuit), mousePressed(false) {
	this->stacks.clear();
}

void EventManager::update() {
	//SDL_WaitEvent(&this->handler);
	while (SDL_PollEvent(&this->handler)) {
		switch (handler.type) {
			case SDL_QUIT:
				*quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
//				if (handler.button.button == SDL_BUTTON_LEFT)
					mouseDown();
				break;
			case SDL_MOUSEBUTTONUP:
//				if (handler.button.button == SDL_BUTTON_LEFT)
					mouseUp();
				break;
			case SDL_MOUSEMOTION:
				mouseMove();
				break;
		}
	}
}

void EventManager::mouseDown() {
	this->mousePressed = true;
	SDL_Log("Mouse apertado.");
}

void EventManager::mouseUp() {
	this->mousePressed = false;
	SDL_Log("Mouse solto.");
}

void EventManager::mouseMove() {
	SDL_Point mouse_pos;
	SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
	
	// Move a pilha que persegue o mouse
	PilhaInteligente* mouse_stack = this->stacks.peek().dir->dir->value;
	mouse_stack->setPosition(mouse_pos);

	// Alynva: Implementação do [] continua não funcionando
	/*
	Node<PilhaInteligente*>* nodeStack = this->stacks.peek().dir->dir;
	for (int i = 1; i < this->stacks.getSize(); i++) { // Inicia em 1 pois o primeiro ï¿½ a pilha que persegue o mouse
		nodeStack = nodeStack->dir;
		bool isHover = nodeStack->value->isInside(mouse_pos);
		nodeStack->value->setStateHover(isHover);

		if (nodeStack->value->getSize()) {
			bool isMovable = false;
			Node<Carta>* nodeCard = nodeStack->value->peek().dir;
			for (int j = 0; j <= nodeStack->value->getSize(); j++) {
				if (nodeStack->value->canBeMoved(&nodeCard->value)) {
					if ((nodeCard->value.isInside(mouse_pos) || isMovable) && isHover)
						nodeCard->value.setStateHover(true);
					else
						nodeCard->value.setStateHover(false);
					isMovable = true;
				}
				nodeCard = nodeCard->dir;
			}
		}
	}
	*/
}

void EventManager::addStack(PilhaInteligente * stack) {
	this->stacks.push(stack);
}
