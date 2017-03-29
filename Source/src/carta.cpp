#include "../../Header/include/carta.h"
#include "../../Header/include/textura.h"
#include <iostream>
#include <string>

using namespace std;

Carta::Carta(int num, SDL_Renderer* renderer){
	string dir = "../textures/cards/";
	int i = (num-1)/13;
	this->value = num-13*i;
	this->suit = 65+i;
	dir.append(to_string(this->value));
	dir.push_back(this->suit);
	dir.append(".png");
	this->gTexture = Textura("../textures/cards/10B.png", renderer, 0, 0, 250, 326);
}

void Carta::renderCard() {
	this->gTexture.render();
}

int Carta::getValue(){
	return this->value;
}

char Carta::getSuit(){
	return this->suit;
}

