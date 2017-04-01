#include <iostream>
#include "../include/baralho.h"
#include "../include/carta.h"
#include "../include/eventmanager.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

using namespace std;

int main(int argv, char** args){
	// Janela principal
	SDL_Window* gWindow = NULL;

	// Renderizador principal
	SDL_Renderer* gRenderer = NULL;

	// Responsavel pelo loop principal
	bool quit = false;
	
	// Eventos
	EventManager event = EventManager(&quit);

	// Cria a janela
	gWindow = SDL_CreateWindow("Freecell", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

	Baralho b = Baralho(gRenderer);
	Carta c;
	b.getCard(c);
	b.organize();

	// Loop  principal
	while(!quit){
		// Responsavel pelos eventos em espera
		event.update();

		// Limpa a tela
		SDL_RenderClear(gRenderer);

		// Renderiza o baralho
		b.render();
		
		// Renderiza a carta
//		c.renderCard();

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
