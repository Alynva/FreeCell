#ifndef MUSICA
#define MUSICA

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

class Musica {
		
	bool quit;
	SDL_Event event;
//	Mix_Music *music;
	Mix_Chunk *sample;
//	Mix_Chunk *scratch;
//	Mix_Chunk *high;
//	Mix_Chunk *med;
//	Mix_Chunk *low;

	public:
	
		Musica() {
			this->quit = false;
//			*this->music = NULL;	
			this->sample = NULL;
//			*this->scratch = NULL;
//			*this->high = NULL;
//			*this->med = NULL;
//			*this->low = NULL;
		};
		
		bool init() {
			Mix_AllocateChannels(16);
			if(SDL_Init(SDL_INIT_AUDIO)==-1) {									
			    printf("SDL_Init: %s\n", SDL_GetError());
			    return false;
			}
			   
			if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
			    printf("Mix_OpenAudio: %s\n", Mix_GetError());
			    return false;
			}
			
			return true;
		};
			
		void addMusic() {
//			this->music = Mix_LoadMUS( "beat.wav" );									
//			this->scratch = Mix_LoadWAV( "scratch.wav" );								
//			this->high = Mix_LoadWAV( "high.wav" );
//			this->med = Mix_LoadWAV( "medium.wav" );
//			this->low = Mix_LoadWAV( "low.wav" );
			this->sample = Mix_LoadWAV("../musics/fgi.wav");
		};
		
		void play() {
			Mix_PlayChannel(-1, sample, -1);
		};
			
		~Musica() {
			Mix_Quit();	
		};
			
};

#endif
