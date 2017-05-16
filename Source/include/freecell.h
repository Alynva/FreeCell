#ifndef FREECELL
#define FREECELL

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include "button.h"

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
	bool play; // Respons�vel por come�ar o jogo
	EventManager event; // Eventos

	Baralho b;
	PilhaIntermediaria p_m; // Pilha que persegue o mouse
	PilhaAuxiliar p_a[4];
	PilhaDefinitiva p_d[4];
	PilhaIntermediaria p_i[8];
	
	PilhaInteligente p_r; // Pilha da chuva de cartas

	public:
		FreeCell();
		~FreeCell();
		bool init();
		void menu();
		void setupItens();
		void update();
		bool start() const;
		bool finish() const;
		bool win();
		void cardRain();
		void playAgain();
};

FreeCell::FreeCell():gWindow(NULL), gRenderer(NULL), quit(false), play(false), event(EventManager(&this->quit, &this->play, &this->window_size)) {}

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
	this->gWindow = SDL_CreateWindow("FreeCell", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
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

			return true;
		}
	}
}

void FreeCell::menu() {
	// Inicializa o background
	this->gBackground = SDL_CreateTextureFromSurface(this->gRenderer, IMG_Load("../textures/backgrounds/0.png"));
	
	Textura logo("../textures/logo/logo.png", this->gRenderer, this->window_size.x / 2 - 204, this->window_size.y / 4 - 79, 408, 158);
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

	while (!this->start() && !this->finish()) {
		// Responsavel pelos eventos em espera
		this->event.update();
		
		// Limpa a tela
		SDL_RenderClear(this->gRenderer);
	
		// Renderiza o background
//		int x = 0, y = 0, w = 0, h = 0;
//		SDL_QueryTexture(this->gBackground, NULL, NULL, &w, &h);
//		SDL_Rect backgroundQuad = {x, y, w, h};
//		SDL_RenderCopy(this->gRenderer, this->gBackground, NULL, &backgroundQuad);
		SDL_RenderCopy(this->gRenderer, this->gBackground, NULL, NULL);
		
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
	
	// Inicializa o background
	this->gBackground = SDL_CreateTextureFromSurface(this->gRenderer, IMG_Load("../textures/backgrounds/1.png"));
	
	// Inicializa o baralho
	this->b.setTexture(this->gRenderer);;
	this->b.generate();
	this->b.randomize();
	
	this->event.clearStacks();

	// Inicializa e adiciona a pilha do mouse ao EventManager
	this->p_m.setTexture(this->gRenderer);
	this->event.addStack(&this->p_m);
	
	// Inicializa a pilha de cuhva de cartas
//	this->p_r.setTexture(this->gRenderer);
//	this->p_r.setPosition({-50, -50});

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

	SDL_Log("\n\n\tInsercoes do setup finalizadas\n\n");
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
	if (this->p_r.getSize())
		this->p_r.render();

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
	bool ok;
	SDL_Point gravity = {0, 3};
	for (int i = 0; i < 4; i++) {
		for (int j = this->p_d[i].getSize() - 1; j >= 0 ; j--) {
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
				Carta c = this->p_d[i][j]->value;
				
				acc.x += gravity.x; acc.y += gravity.y;
				if (pos.y + 100 >= this->window_size.y && vel.y > 0)
					vel.y = -vel.y;
				
				vel.x += acc.x; vel.y += acc.y;
				pos.x += vel.x; pos.y += vel.y;
				acc = {0, 0};
				
				if (pos.y + 100 > this->window_size.y)
					pos.y = this->window_size.y - 100;
					
				this->event.update();
				c.setPosition(pos);
				c.render();
				SDL_RenderPresent(this->gRenderer);
//				p_r.push(c, ok);
//				this->update();
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
    string message = this->win() ? "Parab�ns, voc� venceu!! Deseja jogar novamente?" : "Que pena que voc� n�o conseguiu. Deseja jogar novamente?";
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        this->gWindow, /* .window */
        "Acabou!", /* .title */
        message.c_str(), /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
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
//		SDL_Log("Carta %i%c movida", c.getValue(), c.getSuit());
		p->push(c, ok);
	}
	p->organize();
	return true;
}

#endif