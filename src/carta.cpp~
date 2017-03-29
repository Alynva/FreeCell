#include "carta.h"
#include "textura.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <string>

using namespace std;

Carta::Carta(int num, SDL_Renderer* renderer){
	string dir = "../texture/cards/";
	int i = (num-1)/13;
	this->value = num-13*i;
	this->suit = 65+i;
	dir.append(to_string(this->value));
	dir.push_back(this->suit);
	dir.append(".png");
	cout << dir << endl;
	this->gTexture = Textura(dir, renderer, 0, 0, 250, 326);
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

