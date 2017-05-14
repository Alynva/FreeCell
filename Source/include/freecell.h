#ifndef FREECELL
#define FREECELL

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include "baralho.h"
#include "eventmanager.h"
#include "pilha_auxiliar.h"
#include "pilha_definitiva.h"
#include "pilha_intermediaria.h"

bool moveCartasParaPilha(Baralho*, PilhaInteligente*, int);

class FreeCell {
	SDL_Window* gWindow; // Janela principal
	SDL_Renderer* gRenderer; // Renderizador principal
	SDL_Point window_size; // Tamanho da janela
	SDL_Texture* gBackground; // Plano de fundo
	bool quit; // Responsavel pelo loop principal
	EventManager event; // Eventos
	
	Baralho b;
	PilhaIntermediaria p_m; // Pilha que persegue o mouse
	PilhaAuxiliar p_a[4];
	PilhaDefinitiva p_d[4];
	PilhaIntermediaria p_i[8];
	
	public:
		FreeCell();
		~FreeCell();
		bool init();
		void setupItens();
		void update();
		bool finish() const;
		bool win() const;
};

FreeCell::FreeCell():gWindow(NULL), gRenderer(NULL), quit(false), event(EventManager(&this->quit)) {}

FreeCell::~FreeCell() {
	// Destroi a janela
	SDL_DestroyRenderer(this->gRenderer);
	SDL_DestroyWindow(this->gWindow);
	this->gRenderer = NULL;
	this->gWindow = NULL;

	// Sai dos subsistemas
	IMG_Quit();
	SDL_Quit();
}

bool FreeCell::init() {
	// Cria a janela
	this->gWindow = SDL_CreateWindow("Freecell", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (this->gWindow == NULL) {
		SDL_Log("Window could not be created. SDL Error: %s", SDL_GetError());
		return false;
	} else {
		// Coloca a janela em full screen
//		SDL_SetWindowFullscreen(this->gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);

		// Pega o tamanho da janela
		SDL_GetWindowSize(this->gWindow, &this->window_size.x, &this->window_size.y);

		// Cria o renderizador
		this->gRenderer = SDL_CreateRenderer(this->gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (this->gRenderer == NULL) {
			SDL_Log("Renderer could not be created. SDL Error: %s", SDL_GetError());
			return false;
		} else {
			
			// Inicializa a cor do renderizador
			SDL_SetRenderDrawColor(this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			// Inicializa o carregamento de PNG
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				SDL_Log("SDL could not initialize image. SDL Error: %s", IMG_GetError());
				return false;
			}

			// Inicializa o background
			this->gBackground = SDL_CreateTextureFromSurface(this->gRenderer, IMG_Load("../textures/backgrounds/1.png"));
			
			return true;
		}
	}
}

void FreeCell::setupItens() {
	this->b.setTexture(this->gRenderer);;
	this->b.generate();
	this->b.randomize();

	this->event.addStack(&this->p_m);

	this->p_m.setTexture(this->gRenderer);
		
	for (int i = 0; i < 4; i++) {
		this->p_a[i].setPosition({this->window_size.x/2 - 385 + 90 * i, 50});
		this->p_a[i].setTexture(this->gRenderer);
		this->event.addStack(&this->p_a[i]);
	}

	for (int i = 0; i < 4; i++) {
		this->p_d[i].setPosition({this->window_size.x/2 + 45 + 90 * i, 50});
		this->p_d[i].setTexture(this->gRenderer);
		this->event.addStack(&this->p_d[i]);
	}

	for (int i = 0; i < 8; i++) {
		moveCartasParaPilha(&b, &p_i[i], i < 4 ? 7 : 6);
		this->p_i[i].setPosition({this->window_size.x/2 - 385 + 100 * i, 200});
		this->p_i[i].setTexture(this->gRenderer);
		this->event.addStack(&this->p_i[i]);
	}
	
	SDL_Log("\n\n\tInsersoes do setup finalizadas\n\n");
}

void FreeCell::update() {
	// Responsavel pelos eventos em espera
	this->event.update();

	// Limpa a tela
	SDL_RenderClear(this->gRenderer);

	// Renderiza o background
	SDL_RenderCopy(this->gRenderer, this->gBackground, NULL, NULL);

	// Renderiza as pilhas
	for (int i = 0; i < 4; i++) {
		this->p_a[i].organize();
		this->p_a[i].render();
	}
	for (int i = 0; i < 4; i++) {
		this->p_d[i].organize();
		this->p_d[i].render();
	}
	for (int i = 0; i < 8; i++) {
		this->p_i[i].organize();
		this->p_i[i].render();
	}
	if (this->p_m.getSize()) { // Exibe a pilha que persegue o mouse somente se houver cartas nela
		this->p_m.organize();
		this->p_m.render();
	}

	// Atualiza a tela
	SDL_RenderPresent(this->gRenderer);
}

bool FreeCell::finish() const {
	return this->quit;
}

bool FreeCell::win() const {
	bool win = true;
	
	if (this->p_m.getSize())
		win = false;
	for (int i = 0; i < 4; i++)
		if (this->p_a[i].getSize())
			win = false;
	for (int i = 0; i < 4; i++)
		if (this->p_d[i].getSize() != 13)
			win = false;
	for (int i = 0; i < 8; i++)
		if (this->p_i[i].getSize())
			win = false;
			
	return true;
}

bool moveCartasParaPilha(Baralho* b, PilhaInteligente* p, int qnt) {
	Carta c;
	for (int i = 0; i < qnt; i++) {
		bool ok = false;
		if (!b->getCard(c))
			return false;
//		SDL_Log("Carta %i%c movida", c.getValue(), c.getSuit());
		p->push(c, ok);
	}
	p->organize();
	return true;
}

#endif
