#include <SDL.h> //usaremos funcoes da SDL

#define SCREEN_W 640 //tamanho da janela que sera criada
#define SCREEN_H 480

int main(int argc, char** argv) //funcao de entrada
{
    SDL_Surface* screen; //superficie que representa a tela do computador
    SDL_Event event; //um evento enviado pela SDL
    int quit = 0; //devemos encerrar o programa?

    SDL_Init(SDL_INIT_VIDEO); //inicializar a SDL
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_SWSURFACE); //criar uma janela 640x480x16bits

    while(!quit) //rodar enquanto nao for para encerrar :)
    {
        while(SDL_PollEvent(&event)) //checar eventos
        {
            if(event.type == SDL_QUIT) //fechar a janela?
            {
                quit = 1; //sair do loop principal
            }
        }

        SDL_Flip(screen); //atualizar a tela
    }

    SDL_Quit(); //encerrar a SDL

    return 0;
}
