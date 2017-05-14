#include "../include/eventmanager.h"
#include <iostream>

bool abc;
EventManager::EventManager(bool* mQuit):quit(mQuit), mouse_pressed(false) {
	this->stacks.clear();
	this->stack_offset = {0, 0};
	
	this->stack_joining = nullptr;
	this->stack_hovered = nullptr;
	this->card_hovered = nullptr;
}

void EventManager::update() {
	SDL_GetMouseState(&this->mouse_pos.x, &this->mouse_pos.y);
	while (SDL_PollEvent(&this->handler)) {
		switch (handler.type) {
			case SDL_QUIT:
				*quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (handler.button.button == SDL_BUTTON_LEFT)
					mouseLeftDown();
				break;
			case SDL_MOUSEBUTTONUP:
				if (handler.button.button == SDL_BUTTON_LEFT)
					mouseLeftUp();
				break;
			case SDL_MOUSEMOTION:
				mouseMove();
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

void EventManager::addStack(PilhaInteligente * stack) {
	this->stacks.push(stack, abc);
}
