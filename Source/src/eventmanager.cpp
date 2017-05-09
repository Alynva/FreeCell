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
	
	Node<PilhaInteligente*>* element = this->stacks.peek().dir;
	for (int i = 0; i < this->stacks.getSize(); i++) {
		element = element->dir;
		element->value->setStateHover(element->value->isInside(mouse_pos));
		
		if (element->value->getSize()) {
			Node<Carta>* otherElement = element->value->peek().dir;
			for (int j = 0; j < element->value->getSize(); j++) {
				otherElement = otherElement->dir;
				otherElement->value.setStateHover(otherElement->value.isInside(mouse_pos));
			}
		}
	}
}

void EventManager::addStack(PilhaInteligente * stack) {
	this->stacks.push(stack);
}
