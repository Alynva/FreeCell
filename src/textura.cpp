#include "textura.h"
#include <iostream>
#include <string>

using namespace std;

SDL_Texture* Textura::loadTexture(){
	// Textura final
	SDL_Texture* newTexture = NULL;
	
	// Carrega imagem a partir de um caminho
	SDL_Surface* loadedSurface = IMG_Load(this->pPath.c_str());
	if(loadedSurface == NULL){
		cout << "Unable to load image " << this->pPath.c_str() << ". SDL_Image Error: " << IMG_GetError() << endl;
	} else {
		// Cria textura dos pixels da superficie
		newTexture = SDL_CreateTextureFromSurface(this->pRenderer, loadedSurface);
		if( newTexture == NULL) {
			cout << "Unable to create texture from " << this->pPath.c_str() << ". SDL Error: " << SDL_GetError() << endl;
		}
		
		// Deleta a superficie
		SDL_FreeSurface(loadedSurface);
	}
	
	return newTexture;
}

Textura::Textura() {}

Textura::Textura(string path, SDL_Renderer* renderer, int x, int y, int w, int h){
	this->pRenderer = renderer;
	this->pPath = path;
	this->pTexture = this->loadTexture();
	this->recFormat.x = x;
	this->recFormat.y = y;
	this->recFormat.w = w;
	this->recFormat.h = h;
}

void Textura::setSize(int w, int h){
	this->recFormat.w = w;
	this->recFormat.h = h;
}

void Textura::setPosition(int x, int y){
	this->recFormat.x = x;
	this->recFormat.y = y;
}

void Textura::render(){
	SDL_RenderCopy(this->pRenderer, this->pTexture, NULL, &this->recFormat);
}
