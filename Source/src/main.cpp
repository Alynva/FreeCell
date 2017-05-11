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

int main(int argv, char** args) {
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
	if (gWindow == NULL) {
		cout << "Window could not be created. SDL Error: " << SDL_GetError() << endl;
	} else {
		// Coloca a janela em full screen
//		SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);

		// Cria o renderizador
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer == NULL) {
			cout << "Renderer could not be created. SDL Error: " << SDL_GetError() << endl;
		} else {
			// Inicializa a cor do renderizador
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			// Inicializa o carregamento de PNG
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				cout << "SDL could not initialize image. SDL Error: " << IMG_GetError() << endl;
			}

			// Inicializa o background
			gBackground = SDL_CreateTextureFromSurface(gRenderer, IMG_Load("../textures/backgrounds/1.png"));
		}
	}

	Baralho b(gRenderer);
	b.randomize();

	PilhaInteligente p_m; // Pilha que persegue o mouse
	p_m.setTexture(gRenderer);
	event.addStack(&p_m);

	PilhaInteligente p_u[4]; // Pilha de carta �nica
	for (int i = 0; i < 4; i++) {
		p_u[i].setPosition({130 + 90 * i, 50});
		p_u[i].setTexture(gRenderer);
		event.addStack(&p_u[i]);
	}

	PilhaDefinitiva p_d[4];
	for (int i = 0; i < 4; i++) {
		p_d[i].setPosition({560 + 90 * i, 50});
		p_d[i].setTexture(gRenderer);
		event.addStack(&p_d[i]);
	}

	PilhaIntermediaria p_i[8];
	for (int i = 0; i < 8; i++) {
		moveCartasParaPilha(&b, &p_i[i], i < 4 ? 7 : 6);
		p_i[i].setPosition({130 + 100 * i, 200});
		p_i[i].setTexture(gRenderer);
		event.addStack(&p_i[i]);
	}

	// Loop  principal
	while (!quit) {
		// Responsavel pelos eventos em espera
		event.update();

		// Limpa a tela
		SDL_RenderClear(gRenderer);

		// Renderiza o background
		SDL_RenderCopy(gRenderer, gBackground, NULL, NULL);

		// Renderiza as pilhas
		for (int i = 0; i < 4; i++) {
			p_u[i].organize();
			p_u[i].render();
		}
		for (int i = 0; i < 4; i++) {
			p_d[i].organize();
			p_d[i].render();
		}
		for (int i = 0; i < 8; i++) {
			p_i[i].organize();
			p_i[i].render();
		}
		if (p_m.getSize()) { // Exibe a pilha que persegue o mouse somente se houver cartas nela
			p_m.organize();
			p_m.render();
		}

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
