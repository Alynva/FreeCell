#include "carta.h"
#include <iostream>
#include <C:\SDL2-2.0.5\x86_64-w64-mingw32\include\SDL2\SDL.h>
#include <C:\SDL2-2.0.5\x86_64-w64-mingw32\include\SDL2\SDL_image.h>
#include "textura.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

using namespace std;

int main(){
	// Janela principal
	SDL_Window* gWindow = NULL;
	
	// Renderizador principal
	SDL_Renderer* gRenderer = NULL;
	
	// Classe texture
	// Textura t = NULL;
	
	// Eventos
	SDL_Event event;
	
	// Responsavel pelo loop principal
	bool quit = false;

	// Cria a janela
	gWindow = SDL_CreateWindow("Presidente", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL){
		cout << "Window could not be created. SDL Error: " << SDL_GetError() << endl;
	} else {
		// Cria o renderizador
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if(gRenderer == NULL) {
			cout << "Renderer could not be created. SDL Error: " << SDL_GetError() << endl;
		} else {
			// Inicializa a cor do renderizador
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			// Inicializa o carregamento de PNG
			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags) & imgFlags)){
				cout << "SDL could not initialize image. SDL Error: " << IMG_GetError() << endl;
			}
		}
	}
	
	Carta c = Carta(23, gRenderer);
	
	/*if(t == NULL){
		cout << "Failed to load texture." << endl;
	}*/
	
	// Loop  principal
	while(!quit){
		// Responsavel pelos eventos em espera
		while(SDL_PollEvent(&event) != 0){
			// Evento de saída
			if( event.type == SDL_QUIT)
				quit = true;
		}
		
		// Limpa a tela
		SDL_RenderClear(gRenderer);
		
		// Renderiza a carta
		c.render();
		
		// Atualiza a tela
		SDL_RenderPresent(gRenderer);
	}
	
	// Destroi a janela
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;
	
	// Sai dos subsistemas
	IMG_Quit();
	SDL_Quit();

	return 0;
}
