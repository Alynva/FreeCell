#include "baralho.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include <iostream>

using namespace std;

Baralho::Baralho(int num, SDL_Renderer* renderer){
	this->gRenderer = renderer;
	for(int i = 1; i <= num; i++){
		this->deck.push_back(Carta(i, this->gRenderer));
	}
	this->randomize();
}

void Baralho::generate(int num){
	this->deck.clear();
	for(int i = 1; i <= num; i++){
		this->deck.push_back(Carta(i, this->gRenderer));
	}
}

void Baralho::randomize(){
	srand(time(0));
	random_shuffle(this->deck.begin(), this->deck.end());
}

Carta Baralho::getCard(){
	if(this->deck.size() > 0) {
		Carta elem = this->deck[this->deck.size()-1];
		this->deck.pop_back();
		return elem;
	}
}
