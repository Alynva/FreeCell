#ifndef FREECELL
#define FREECELL

//#define SCREEN_WIDTH 1280
//#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600

#include "SDL2/SDL_mixer.h"

#include "button.h"

#include "baralho.h"
#include "eventmanager.h"
#include "pilha_auxiliar.h"
#include "pilha_definitiva.h"
#include "pilha_intermediaria.h"

#include "../include/get_fill_size.hpp"

bool moveCartasParaPilha(Baralho*, PilhaInteligente*, int);

class FreeCell {
	SDL_Window* gWindow; // Janela principal
	SDL_Renderer* gRenderer; // Renderizador principal
	SDL_Point window_size; // Tamanho da janela
	SDL_Texture* gBackground; // Plano de fundo
	bool t_fullscreen;
	Mix_Music* song;
	bool quit; // Responsavel pelo loop principal
	bool play; // Respons�vel por come�ar o jogo
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
		void toggleFullscreen();
		void menu();
		void setupItens();
		void update();
		bool start() const;
		bool finish() const;
		bool win();
		void cardRain();
		void playAgain();
};

FreeCell::FreeCell():gWindow(NULL), gRenderer(NULL), t_fullscreen(false), quit(false), play(false), event(EventManager(&this->t_fullscreen, &this->quit, &this->play, &this->window_size)) {}

FreeCell::~FreeCell() {
	// Destroi a janela
	SDL_DestroyRenderer(this->gRenderer);
	SDL_DestroyWindow(this->gWindow);
	this->gRenderer = NULL;
	this->gWindow = NULL;

	Mix_FreeMusic(this->song);
	this->song = NULL;
	Mix_Quit();

	// Sai dos subsistemas
	IMG_Quit();
	SDL_Quit();
}

bool FreeCell::init() {
	// Cria a janela
	this->gWindow = SDL_CreateWindow("FreeCell", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
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

			// Inicializa o �udio
			Mix_AllocateChannels(16);
			if(SDL_Init(SDL_INIT_AUDIO) == -1) {
			    SDL_Log("SDL_Init: %s\n", SDL_GetError());
			    return false;
			}
			if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
			    SDL_Log("Mix_OpenAudio: %s\n", Mix_GetError());
			    return false;
			}

			return true;
		}
	}
}

void FreeCell::toggleFullscreen() {
	this->t_fullscreen = false;
	if (SDL_GetWindowFlags(this->gWindow) & SDL_WINDOW_FULLSCREEN_DESKTOP)
		SDL_SetWindowFullscreen(this->gWindow, 0);
	else
		SDL_SetWindowFullscreen(this->gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void FreeCell::menu() {
	this->song = Mix_LoadMUS("musics/mp3/Stylo.mp3");
	Mix_FadeInMusic(this->song, -1, 5000);

	this->gBackground = SDL_CreateTextureFromSurface(this->gRenderer, IMG_Load("textures/backgrounds/4.png"));

	Textura logo("textures/logo/logo.png", this->gRenderer, this->window_size.x / 2 - 204, this->window_size.y / 4 - 79, 408, 158);
	this->event.addLogo(&logo);

	Button play("play", this->gRenderer);
	play.setPosition({this->window_size.x / 2 - 125, this->window_size.y / 2 - 25});
	this->event.addButton(&play);

	Button project("project", this->gRenderer);
	project.setPosition({this->window_size.x / 2 - 125, this->window_size.y / 2 + 50});
	this->event.addButton(&project);

	Button quit("quit", this->gRenderer);
	quit.setPosition({this->window_size.x / 2 - 125, this->window_size.y / 2 + 125});
	this->event.addButton(&quit);

	int iw, ih; // Vari�veis para calcular o tamanho e posi��o da imagem sem distor�o
	SDL_QueryTexture(this->gBackground, NULL, NULL, &iw, &ih); // Get the image size

	while (!this->start() && !this->finish()) {
		// Responsavel pelos eventos em espera
		this->event.update();
		if (this->t_fullscreen)
			this->toggleFullscreen();

		// Limpa a tela
		SDL_RenderClear(this->gRenderer);

		// Renderiza o background
		SDL_Rect backgroundQuad = getFillSize(iw, ih, this->window_size.x, this->window_size.y);
		SDL_RenderCopy(this->gRenderer, this->gBackground, NULL, &backgroundQuad);
//		SDL_RenderCopy(this->gRenderer, this->gBackground, NULL, NULL);

		logo.render();

		play.render();
		project.render();
		quit.render();

		// Atualiza a tela
		SDL_RenderPresent(this->gRenderer);
	}

	this->event.clearButtons();
	this->event.clearLogo();
}

void FreeCell::setupItens() {
	this->quit = false;

	Mix_FadeOutMusic(400);
	this->song = Mix_LoadMUS("musics/mp3/ClintEastwood.mp3");
	Mix_FadeInMusic(this->song, -1, 2000);

	// Inicializa o background
	this->gBackground = SDL_CreateTextureFromSurface(this->gRenderer, IMG_Load("textures/backgrounds/1.png"));

	// Inicializa o baralho
	this->b.setTexture(this->gRenderer);;
	this->b.generate();
	this->b.randomize();

	this->event.clearStacks();

	// Inicializa e adiciona a pilha do mouse ao EventManager
	this->p_m.setTexture(this->gRenderer);
	this->event.addStack(&this->p_m);

	// Inicializa e adiciona a pilha auxiliar ao EventManager
	for (int i = 0; i < 4; i++) {
		this->p_a[i].clear();
		this->p_a[i].setPosition({this->window_size.x/2 - 385 + 90 * i, 50});
		this->p_a[i].setTexture(this->gRenderer);
		this->event.addStack(&this->p_a[i]);
	}

	// Inicializa e adiciona a pilha definitiva ao EventManager
	for (int i = 0; i < 4; i++) {
		this->p_d[i].clear();
		this->p_d[i].setPosition({this->window_size.x/2 + 45 + 90 * i, 50});
		this->p_d[i].setTexture(this->gRenderer);
		this->event.addStack(&this->p_d[i]);
	}

	// Inicializa e adiciona a pilha intermedi�ria ao EventManager
	for (int i = 0; i < 8; i++) {
		this->p_i[i].clear();
		moveCartasParaPilha(&b, &p_i[i], i < 4 ? 7 : 6);
		this->p_i[i].setPosition({this->window_size.x/2 - 385 + 100 * i, 200});
		this->p_i[i].setTexture(this->gRenderer);
		this->event.addStack(&this->p_i[i]);
	}

}

void FreeCell::update() {
	// Responsavel pelos eventos em espera
	this->event.update();

	if (this->t_fullscreen)
		this->toggleFullscreen();

	// Limpa a tela
	SDL_RenderClear(this->gRenderer);

	// Renderiza o background
	int iw, ih; // Vari�veis para calcular o tamanho e posi��o da imagem sem distor�o
	SDL_QueryTexture(this->gBackground, NULL, NULL, &iw, &ih); // Get the image size
	SDL_Rect backgroundQuad = getFillSize(iw, ih, this->window_size.x, this->window_size.y);
	SDL_RenderCopy(this->gRenderer, this->gBackground, NULL, &backgroundQuad);

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

bool FreeCell::start() const {
	return this->play;
}
bool FreeCell::finish() const {
	return this->quit;
}

bool FreeCell::win() {
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

	if (win && this->quit == false) {
		this->cardRain();
		this->quit = true;
	}

	return win;
}

void FreeCell::cardRain() {
	Mix_FadeOutMusic(400);
	this->song = Mix_LoadMUS("musics/mp3/FeelGoodInc.mp3");
	Mix_FadeInMusic(this->song, -1, 2000);

	SDL_Point gravity = {0, 3};
	for (int i = 0; i < 4; i++) {
		for (int j = this->p_d[i].getSize() - 1; j >= 0 ; j--) {
			Carta c = this->p_d[i][j]->value;
			c.render();

			SDL_Point pos = this->p_d[i][j]->value.getPosition();
			SDL_Point vel = {0, 0};
			SDL_Point acc = {0, 0};

			SDL_Point force {0, 0};
			if (rand() % 2 - 1)
				force.x = rand() % 5 - 7;
			else if (rand() % 2 - 1)
				force.x = rand() % 5 + 2;
			else if (rand() % 2 - 1)
				force.x = rand() % 3 - 2;
			if (!force.x) force.x = 4;
			force.y = rand() % 25 - 30;

			acc.x += force.x; acc.y += force.y;
			while (pos.x + 69 >= 0 && pos.x <= this->window_size.x) {


				acc.x += gravity.x; acc.y += gravity.y;
				if (pos.y + 100 >= this->window_size.y && vel.y > 0)
					vel.y = -vel.y;

				vel.x += acc.x; vel.y += acc.y;
				pos.x += vel.x; pos.y += vel.y;
				acc = {0, 0};

				if (pos.y + 100 > this->window_size.y)
					pos.y = this->window_size.y - 100;

				this->event.update();
				if (this->t_fullscreen)
					this->toggleFullscreen();

				c.setPosition(pos);
				c.render();
				SDL_RenderPresent(this->gRenderer);
				SDL_Delay(30);

				if (this->finish())
					break;
			}
			if (this->finish())
				break;
		}
		if (this->finish())
			break;
	}
}

void FreeCell::playAgain() {
	Mix_Music* effect = Mix_LoadMUS("musics/scratch.wav");
	Mix_FadeInMusic(effect, 1, 1000);

	const SDL_MessageBoxButtonData buttons[] = {
        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Sair" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Jogar novamente" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };
    string message = this->win() ? "Parabens, voce venceu!! Deseja jogar novamente?" : "Que pena que voce nao conseguiu. Deseja jogar novamente?";
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        this->gWindow, /* .window */
        "Acabou!", /* .title */
        message.c_str(), /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        NULL /* .colorScheme */
    };
    int buttonid = -1;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("Error displaying message box");
    }

	if (buttonid == 0) this->quit = false;
}

bool moveCartasParaPilha(Baralho* b, PilhaInteligente* p, int qnt) {
	Carta c;
	for (int i = 0; i < qnt; i++) {
		bool ok = false;
		if (!b->getCard(c))
			return false;
		p->push(c, ok);
	}
	p->organize();
	return true;
}

#endif
