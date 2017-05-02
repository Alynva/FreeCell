#include "../include/carta.h"
#include "../include/to_string.h"
#include <math.h>

#define CARD_WIDTH 69
#define CARD_HEIGHT 100
#define BLUR_WIDTH_ORIG 118
#define BLUR_HEIGHT_ORIG 174
#define BLUR_WIDTH CARD_WIDTH * BLUR_WIDTH_ORIG / (BLUR_WIDTH_ORIG - 18)
#define BLUR_HEIGHT CARD_HEIGHT * BLUR_HEIGHT_ORIG / (BLUR_HEIGHT_ORIG - 18)
#define BLUR_OFFSET_X round((BLUR_WIDTH - CARD_WIDTH) / 2)
#define BLUR_OFFSET_Y round((BLUR_HEIGHT - CARD_HEIGHT) / 2)

using namespace std;

Carta::Carta(){}

Carta::Carta(const Carta& copyVal){
		this->value = copyVal.getValue();
		this->suit = copyVal.getSuit();
		this->gTexture = copyVal.getTexture();
		this->isBlur = copyVal.isBlur;
		this->blurTexture = copyVal.blurTexture;
}

Carta::Carta(int num, SDL_Renderer* renderer){
	string pathCarta = "", pathBlur = "";
	string dir = "../textures/";
	string folder = "cards/v2/";
	string file = "";

	int i = (num-1)/13;
	this->value = num-13*i;
	this->suit = 65+i;

	file.append(to_string(this->value));
	file.push_back(this->suit);
	file.append(".png");

	pathCarta.append(dir);
	pathCarta.append(folder);
	pathCarta.append(file);

	this->gTexture = Textura(pathCarta, renderer, 0, 0, CARD_WIDTH, CARD_HEIGHT);

	if (this->value == 1)
		this->isBlur = true;
	else // TESTE PARA BLUR NAS CARTAS A
		this->isBlur = false;

	pathBlur.append(dir);
	pathBlur.append("blur_blue.png");
	this->blurTexture = Textura(pathBlur, renderer, -BLUR_OFFSET_X, -BLUR_OFFSET_Y, BLUR_WIDTH, BLUR_HEIGHT);
}

void Carta::setPosition(SDL_Point coord){
	int blurX = coord.x - BLUR_OFFSET_X;	// Aparentemente n�o � poss�vel converter double
	int blurY = coord.y - BLUR_OFFSET_Y;	// para int dentro de {}
	this->blurTexture.setPosition({blurX, blurY});
	this->gTexture.setPosition(coord);
}

void Carta::render() {
	if (this->isBlur)
		this->blurTexture.render();
	this->gTexture.render();
}

int Carta::getValue() const{
	return this->value;
}

char Carta::getSuit() const{
	return this->suit;
}

Textura Carta::getTexture() const{
	return this->gTexture;
}

bool Carta::isInside(SDL_Point point) const{
	SDL_Point size = this->gTexture.getSize();
	SDL_Point position = this->gTexture.getPosition();

	bool inside = ((point.x > position.x && point.x < position.x + size.x) &&
			(point.y > position.y && point.y < position.y + size.y));

	return inside;
}
