#include "../include/eventmanager.h"
#include <iostream>

bool abc;
EventManager::EventManager(bool* mQuit):quit(mQuit), mousePressed(false) {
	this->stacks.clear();
	this->stack_offset = {0, 0};
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
	this->mousePressed = true;

	PilhaInteligente* mouse_stack = this->stacks.peek().dir->dir->value;

	// Alynva: Implementaï¿½ï¿½o do [] continua nï¿½o funcionando
	Node<PilhaInteligente*>* nodeStack = this->stacks.peek().dir->dir;
	for (int i = 1; i < this->stacks.getSize(); i++) { // Inicia em 1 pois o primeiro ï¿½ a pilha que persegue o mouse
		nodeStack = nodeStack->dir;
		bool isHover = nodeStack->value->isInside(mouse_pos);

		if (nodeStack->value->getSize()) {
			bool isMovable = false;
			bool found = false;
			Node<Carta>* nodeCard = nodeStack->value->peek().dir;
			Node<Carta>* lastNodeCard;
			for (int j = 0; j <= nodeStack->value->getSize(); j++) {
				if (nodeCard->value.isInside(mouse_pos)) {
					lastNodeCard = nodeCard;
					found = true;
				}
				nodeCard = nodeCard->dir;
			}
			if (found && nodeStack->value->canBeMoved(&lastNodeCard->value)) {
				this->previous_stack = nodeStack->value; // Salva de onde foi retirado a(s) carta(s)

				bool afterThan = false;
				PilhaInteligente stackTemp;

				nodeCard = nodeStack->value->peek().dir;
				for (int j = 0; j <= nodeStack->value->getSize(); !afterThan ? j++ : j) { // Se encontrar, nï¿½o incrementa o j pois ele serï¿½ retirado da pilha, portanto o prï¿½ximo serï¿½ o atual depois de ser retirado
					if (afterThan || nodeCard == lastNodeCard) {
						afterThan = true;

						Carta cardTemp;
						nodeStack->value->pop(cardTemp);
						cardTemp.setStateHover(false);
						stackTemp.push(cardTemp, abc);
					}
					nodeCard = nodeCard->dir;
				}
				Carta cardTemp;
				while (!stackTemp.isEmpty()) {
					stackTemp.pop(cardTemp);
					mouse_stack->push(cardTemp, abc);
				}
			}
		}
	}
}

void EventManager::mouseLeftUp() {
	this->mousePressed = false;

	PilhaInteligente* mouse_stack = this->stacks.peek().dir->dir->value;
	PilhaInteligente* original_stack = this->previous_stack;
	PilhaInteligente* target_stack = this->previous_stack;
//	mouse_stack->clear();

	bool can_join = false;

	Node<PilhaInteligente*>* nodeStack = this->stacks.peek().dir->dir;
	for (int i = 1; i < this->stacks.getSize(); i++) { // Inicia em 1 pois o primeiro ï¿½ a pilha que persegue o mouse
		nodeStack = nodeStack->dir;
		bool isHover = nodeStack->value->isInside(this->mouse_pos);

		if (nodeStack->value->getSize()) {
			bool isMovable = false;
			bool found = false;
			Node<Carta>* lastNodeCard;
			Node<Carta>* nodeCard = nodeStack->value->peek().dir;
			for (int j = 0; j <= nodeStack->value->getSize(); j++) {
				if (nodeCard->value.isInside(mouse_pos)) {
					lastNodeCard = nodeCard;
					found = true;
				}
				nodeCard = nodeCard->dir;
			}
			if (found && nodeStack->value->canBeMoved(&lastNodeCard->value)) {
				Node<Carta>* first_node_card_mouse = mouse_stack->peek().dir->dir;
				can_join = nodeStack->value->isDifferentColor(lastNodeCard->value, first_node_card_mouse->value) && lastNodeCard->value.getValue() == first_node_card_mouse->value.getValue() + 1;

				if (can_join) target_stack = nodeStack->value;
			}
		} else {
			if (nodeStack->value->isInside(mouse_pos)) target_stack = nodeStack->value;
		}
	}


	PilhaInteligente stack_temp;
	Carta card_temp;
	while (!mouse_stack->isEmpty()) {
		mouse_stack->pop(card_temp);
		stack_temp.push(card_temp, abc);
	}
	while (!stack_temp.isEmpty()) {
		bool test = false;
		stack_temp.pop(card_temp);
		target_stack->push(card_temp, test);
		if (!test) original_stack->push(card_temp, test); // Alynva: o PilhaDefinitiva.push() está sempre retornando true, suspeito que é por que o this->peek().dir não existe, portanto não é possível executar getValue()
		SDL_Log("%c", test ? 's' : 'n');
	}
}

void EventManager::mouseMove() {
	SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);

	// Move a pilha que persegue o mouse
	PilhaInteligente* mouse_stack = this->stacks.peek().dir->dir->value;
	mouse_stack->setPosition({mouse_pos.x + this->stack_offset.x, mouse_pos.y + this->stack_offset.y});

	bool can_join = false;

	// Alynva: Implementaï¿½ï¿½o do [] continua nï¿½o funcionando
	Node<PilhaInteligente*>* nodeStack = this->stacks.peek().dir->dir;
	for (int i = 1; i < this->stacks.getSize(); i++) { // Inicia em 1 pois o primeiro ï¿½ a pilha que persegue o mouse
		nodeStack = nodeStack->dir;
		bool isHover = nodeStack->value->isInside(mouse_pos);
		nodeStack->value->setStateHover(isHover);

		if (nodeStack->value->getSize()) {
			bool isMovable = false;
			bool found = false;
			Node<Carta>* lastNodeCard;
			Node<Carta>* nodeCard = nodeStack->value->peek().dir;
			for (int j = 0; j <= nodeStack->value->getSize(); j++) {
				if (nodeCard->value.isInside(mouse_pos)) {
					lastNodeCard = nodeCard;
					found = true;
				}
					nodeCard->value.setStateHover(false);
				nodeCard = nodeCard->dir;
			}
			if (found && nodeStack->value->canBeMoved(&lastNodeCard->value)) {
				bool afterThan = false;
				nodeCard = nodeStack->value->peek().dir;
				for (int j = 0; j <= nodeStack->value->getSize(); j++) {
					if (afterThan || nodeCard == lastNodeCard) {
						if (!afterThan) {
							if (!mouse_stack->getSize())
								this->stack_offset = {nodeCard->value.getPosition().x - mouse_pos.x, nodeCard->value.getPosition().y - mouse_pos.y};
							else {
								Node<Carta>* first_node_card_mouse = mouse_stack->peek().dir->dir;
								can_join = nodeStack->value->isDifferentColor(lastNodeCard->value, first_node_card_mouse->value) && lastNodeCard->value.getValue() == first_node_card_mouse->value.getValue() + 1;
							}
						}
						afterThan = true;
						if (!mouse_stack->getSize() || can_join)
							nodeCard->value.setStateHover(true);
					}
					nodeCard = nodeCard->dir;
				}
			}
		}
	}

	Node<Carta>* nodeCard = mouse_stack->peek().dir;
	for (int j = 0; j <= mouse_stack->getSize(); j++) {
		nodeCard->value.setStateHover(can_join);
		nodeCard = nodeCard->dir;
	}
}

void EventManager::addStack(PilhaInteligente * stack) {
	this->stacks.push(stack, abc);
}
