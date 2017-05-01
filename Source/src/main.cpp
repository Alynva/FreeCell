#include <iostream>
#include "../include/baralho.h"
#include "../include/eventmanager.h"
#include "../include/pilha_definitiva.h"
#include "../include/pilha_intermediaria.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

using namespace std;

bool moveCartasParaPilha(Baralho*, PilhaInteligente*, int);

// Janela principal
SDL_Window* gWindow = NULL;

int main(int argv, char** args){
	// Renderizador principal
	SDL_Renderer* gRenderer = NULL;

	// Plano de fundo
	SDL_Texture* gBackground;

	// Responsavel pelo loop principal
	bool quit = false;

	// Eventos
	EventManager event = EventManager(&quit);

	// Cria a janela
	gWindow = SDL_CreateWindow("Freecell", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL){
		cout << "Window could not be created. SDL Error: " << SDL_GetError() << endl;
	} else {
		// Remove a borda da janela

		SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);

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

			// Inicializa o background
			gBackground = SDL_CreateTextureFromSurface(gRenderer, IMG_Load("../textures/backgrounds/1.png"));

		}
	}

	Baralho b(gRenderer);
	b.organize();
	Carta c;
	b.getCard(c);

	PilhaInteligente p[4];
	p[0].setPosition({40, 10});
	p[0].setTexture(gRenderer);
	p[1].setPosition({130, 10});
	p[1].setTexture(gRenderer);
	p[2].setPosition({220, 10});
	p[2].setTexture(gRenderer);
	p[3].setPosition({310, 10});
	p[3].setTexture(gRenderer);

	moveCartasParaPilha(&b, &p[0], 7);
	moveCartasParaPilha(&b, &p[1], 7);
	moveCartasParaPilha(&b, &p[2], 7);
	moveCartasParaPilha(&b, &p[3], 7);

	// Loop  principal
	while(!quit){
		// Responsavel pelos eventos em espera
		event.update();

		// Limpa a tela
		SDL_RenderClear(gRenderer);

		// Renderiza o background
		SDL_RenderCopy(gRenderer, gBackground, NULL, NULL);

		// Renderiza o baralho
		//b.render();

		// Teste para verificar se um ponto est� dentro do baralho
		//if (b.isInside({10, 10}))
		//	SDL_Log("Esta dentro\n");

		// Renderiza a carta
		//c.renderCard();

		// Renderiza as pilhas
		for (int i = 0; i < 4; i++)
			p[i].render();

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

bool moveCartasParaPilha(Baralho* b, PilhaInteligente* p, int qnt) {
	Carta c;
	for (int i = 0; i < qnt; i++) {
		if (!b->getCard(c))
			return false;
		p->push(c);
	}
	p->organize();
	return true;
}
