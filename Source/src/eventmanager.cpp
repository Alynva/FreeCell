#include "../include/eventmanager.h"
#include <iostream>

EventManager::EventManager(bool* mQuit){
	this->quit = mQuit;
}

void EventManager::update(){
	while(SDL_PollEvent(&this->handler)){
		switch(handler.type){
			case SDL_QUIT:
				*quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseDown(handler.button);
				break;
			case SDL_MOUSEBUTTONUP:
				mouseUp(handler.button);
				break;
		}
	}
}

void EventManager::mouseDown(SDL_MouseButtonEvent& mouseEvent){
	if(mouseEvent.button = SDL_BUTTON_LEFT){
		std::cout << "Teste apertado." << std::endl;
	}
}

void EventManager::mouseUp(SDL_MouseButtonEvent& mouseEvent){
	if(mouseEvent.button = SDL_BUTTON_LEFT){
		std::cout << "Teste solto." << std::endl;
	}
}

