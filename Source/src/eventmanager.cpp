#include "../include/eventmanager.h"
#include <iostream>

bool abc;
EventManager::EventManager(bool* mQuit, SDL_Point* mWinSize):quit(mQuit), window_size(mWinSize), mouse_pressed(false) {
	this->stacks.clear();
	this->stack_offset = {0, 0};
	
	this->stack_joining = nullptr;
	this->stack_hovered = nullptr;
	this->card_hovered = nullptr;
}

void EventManager::update() {
	SDL_GetMouseState(&this->mouse_pos.x, &this->mouse_pos.y);
	while (SDL_PollEvent(&this->handler)) {
		switch (this->handler.type) {
			case SDL_QUIT:
				*this->quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (handler.button.button == SDL_BUTTON_LEFT)
					this->mouseLeftDown();
				break;
			case SDL_MOUSEBUTTONUP:
				if (handler.button.button == SDL_BUTTON_LEFT)
					this->mouseLeftUp();
				break;
			case SDL_MOUSEMOTION:
				this->mouseMove();
				break;
			case SDL_WINDOWEVENT:
		        switch (this->handler.window.event) {
			        case SDL_WINDOWEVENT_SHOWN:
//			            SDL_Log("Window %d shown", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_HIDDEN:
//			            SDL_Log("Window %d hidden", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_EXPOSED:
//			            SDL_Log("Window %d exposed", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_MOVED:
//			            SDL_Log("Window %d moved to %d,%d",
//			                    this->handler.window.windowID, this->handler.window.data1,
//			                    this->handler.window.data2);
			            break;
			        case SDL_WINDOWEVENT_RESIZED:
//			            SDL_Log("Window %d resized to %dx%d",
//			                    this->handler.window.windowID, this->handler.window.data1,
//			                    this->handler.window.data2);
						this->windowResized(this->handler.window.data1, this->handler.window.data2);
			            break;
			        case SDL_WINDOWEVENT_SIZE_CHANGED:
//			            SDL_Log("Window %d size changed to %dx%d",
//			                    this->handler.window.windowID, this->handler.window.data1,
//			                    this->handler.window.data2);
			            break;
			        case SDL_WINDOWEVENT_MINIMIZED:
//			            SDL_Log("Window %d minimized", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_MAXIMIZED:
//			            SDL_Log("Window %d maximized", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_RESTORED:
//			            SDL_Log("Window %d restored", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_ENTER:
//			            SDL_Log("Mouse entered window %d",
//			                    this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_LEAVE:
//			            SDL_Log("Mouse left window %d", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_FOCUS_GAINED:
//			            SDL_Log("Window %d gained keyboard focus",
//			                    this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_FOCUS_LOST:
//			            SDL_Log("Window %d lost keyboard focus",
//			                    this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_CLOSE:
//			            SDL_Log("Window %d closed", this->handler.window.windowID);
			            break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
			        case SDL_WINDOWEVENT_TAKE_FOCUS:
//			            SDL_Log("Window %d is offered a focus", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_HIT_TEST:
//			            SDL_Log("Window %d has a special hit test", this->handler.window.windowID);
			            break;
#endif
			        default:
			            SDL_Log("Window %d got unknown event %d",
			                    this->handler.window.windowID, this->handler.window.event);
			            break;
		        }
		        break;
		}
	}
}

void EventManager::mouseLeftDown() {
	this->mouse_pressed = true;

	PilhaInteligente* mouse_stack = this->stacks.peek()->value;
	
	if (this->stack_hovered && this->card_hovered) {
		bool finded = false;
		for (int i = 0; i < this->stack_hovered->getSize(); i++) {
			if (&this->stack_hovered[0][i]->value == this->card_hovered) {
				finded = true;
				break;
			}
		}
		
		if (finded) {
			PilhaInteligente stack_temp;
			Carta card_temp;
			bool is_after = false;

			Node<Carta>* node_card = this->stack_hovered->peek();
			for (int i = 0; i < this->stack_hovered->getSize(); !is_after ? i++ : i) { // Se encontrar, n�o incrementa o j pois ele ser� retirado da pilha, portanto o pr�ximo ser� o atual depois de ser retirado
				if (is_after || &node_card->value == this->card_hovered) {
					is_after = true;

					this->stack_hovered->pop(card_temp);
					this->previous_stack = this->stack_hovered;
					card_temp.setStateHover(false);
					stack_temp.push(card_temp, abc);
				}
				node_card = node_card->dir;
			}
			while (!stack_temp.isEmpty()) {
				stack_temp.pop(card_temp);
				mouse_stack->push(card_temp, abc);
			}
		}
	}
}

void EventManager::mouseLeftUp() {
	this->mouse_pressed = false;

	PilhaInteligente* mouse_stack = this->stacks.peek()->value;
	
	PilhaInteligente stack_temp;
	Carta card_temp;
	while (!mouse_stack->isEmpty()) {
		mouse_stack->pop(card_temp);
		stack_temp.push(card_temp, abc);
	}
	while (!stack_temp.isEmpty()) {
		abc = false;
		stack_temp.pop(card_temp);
		card_temp.setStateHover(false);
		if (this->stack_joining)
			this->stack_joining->pushChild(card_temp, abc);
			
		SDL_Log("%s %s", abc ? "ok" : "!ok", this->stack_joining ? "target" : "!target");
		if (!this->stack_joining || !abc)
			this->previous_stack->push(card_temp, abc);
	}
}

void EventManager::mouseMove() {
	SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);

	// Move a pilha que persegue o mouse
	if (this->stacks.getSize()) {
		PilhaInteligente* mouse_stack = this->stacks.peek()->value;
		mouse_stack->setPosition({mouse_pos.x + this->stack_offset.x, mouse_pos.y + this->stack_offset.y});
	
		bool found = false;
		bool can_join = false;
		Node<Carta>* last_node_card;
		this->stack_hovered = nullptr;
		// Alynva: Implementa��o do [] continua n�o funcionando
		Node<PilhaInteligente*>* node_stack = this->stacks.peek()->dir;
		for (int i = 1; i < this->stacks.getSize(); i++) { // Inicia em 1 pois o primeiro � a pilha que persegue o mouse
			bool is_stack_hover = node_stack->value->isInside(mouse_pos);
			if (is_stack_hover)
				this->stack_hovered = node_stack->value;
			node_stack->value->setStateHover(is_stack_hover);
	
			if (node_stack->value->getSize()) {
				Node<Carta>* node_card = node_stack->value->peek();
				for (int j = 0; j < node_stack->value->getSize(); j++) {
					if (node_card->value.isInside(mouse_pos)) {
						if (!this->mouse_pressed || mouse_stack->getSize()) {
							last_node_card = node_card;
							found = true;
						}
					}
					node_card->value.setStateHover(false);
					node_card = node_card->dir;
				}
			}
			node_stack = node_stack->dir;
		}
		if (this->stack_hovered) {
			if (found && this->stack_hovered->canBeMoved(&last_node_card->value)) {
				this->card_hovered = &last_node_card->value;
	//			this->card_hovered->setStateHover(true);
	
				bool is_after = false;
				Node<Carta>* node_card = this->stack_hovered->peek();
				for (int i = 0; i < this->stack_hovered->getSize(); i++) {
					if (!is_after) {
						if (&node_card->value == this->card_hovered) {
							is_after = true;
							
							if (!mouse_stack->getSize())
								this->stack_offset = {node_card->value.getPosition().x - mouse_pos.x, node_card->value.getPosition().y - mouse_pos.y};
							else {
								can_join = this->stack_hovered->canPush(*this->card_hovered, mouse_stack->peek()->value);
								this->stack_joining = can_join ? this->stack_hovered : nullptr;
							}
						}
					}
					
					if (is_after) {
						if (!mouse_stack->getSize() || can_join) {
							node_card->value.setStateHover(true);
						}
					}
					node_card = node_card->dir;
				}
			} else if (!this->stack_hovered->getSize() || (mouse_stack->getSize() && found && this->stack_hovered->canPush(last_node_card->value, mouse_stack->peek()->value))) {
				this->card_hovered = &last_node_card->value;
				this->stack_joining = this->stack_hovered;
			} else {
				this->card_hovered = nullptr;
				this->stack_joining = nullptr;
			}
		} else {
			this->card_hovered = nullptr;
			this->stack_joining = nullptr;
		}
	
		if (mouse_stack->getSize()) {
			Node<Carta>* node_card = mouse_stack->peek();
			for (int j = 0; j < mouse_stack->getSize(); j++) {
				node_card->value.setStateHover(can_join);
				node_card = node_card->dir;
			}
		}
	}
}

void EventManager::addStack(PilhaInteligente * stack) {
	this->stacks.push(stack, abc);
}

void EventManager::windowResized(int w, int h) {
	*this->window_size = {w, h};
	Node<PilhaInteligente*>* node_stack = this->stacks.peek()->dir;
	for (int i = 1; i < this->stacks.getSize(); i++) { // Inicia em 1 pois o primeiro � a pilha que persegue o mouse
		if (i >= 1 && i <= 4)
			node_stack->value->setPosition({w/2 - 385 + 90 * (i-1), 50});
		if (i >= 5 && i <= 8)
			node_stack->value->setPosition({w/2 + 45 + 90 * (i-5), 50});
		if (i >= 9 && i <= 16)
			node_stack->value->setPosition({w/2 - 385 + 100 * (i-9), 200});
		node_stack = node_stack->dir;
	}
}
