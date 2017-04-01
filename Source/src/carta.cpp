#include "../include/carta.h"
#include "../include/to_string.h"

#define CARD_WIDTH 125
#define CARD_HEIGHT 164

using namespace std;

Carta::Carta(){}

Carta::Carta(int num, SDL_Renderer* renderer){
	string dir = "../textures/cards/";
	int i = (num-1)/13;
	this->value = num-13*i;
	this->suit = 65+i;
	dir.append(to_string(this->value));
	dir.push_back(this->suit);
	dir.append(".png");
	this->gTexture = Textura(dir, renderer, 0, 0, CARD_WIDTH, CARD_HEIGHT);
}

void Carta::setPosition(int x, int y){
	this->gTexture.setPosition(x, y);
}

void Carta::render() {
	this->gTexture.render();
}

int Carta::getValue(){
	return this->value;
}

char Carta::getSuit(){
	return this->suit;
}
