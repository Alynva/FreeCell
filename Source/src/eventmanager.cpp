#include "../include/eventmanager.h"
#include <iostream>

EventManager::EventManager(bool* mQuit):quit(mQuit), mousePressed(false) {

}

void EventManager::update() {
	SDL_WaitEvent(&this->handler);
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
	SDL_Log("Mouse apertado.\n");
}

void EventManager::mouseUp() {
	this->mousePressed = false;
	SDL_Log("Mouse solto.\n");
}

void EventManager::mouseMove() {
	this->mousePressed ? SDL_Log("Mouse arrastado.\n") : SDL_Log("Mouse movido.\n");
}
