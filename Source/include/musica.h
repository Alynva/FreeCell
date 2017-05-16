#ifndef MUSICA
#define MUSICA

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

class musica{
	private:
		
		bool quit;
		SDL_Event event;
		Mix_Music *music = NULL;	
		Mix_Chunk *sample = NULL;
		Mix_Chunk *scratch = NULL;
		Mix_Chunk *high = NULL;
		Mix_Chunk *med = NULL;
		Mix_Chunk *low = NULL;
		
	 public:
	
	musica(){
		this-> quit = false;
		* this-> music = NULL;	
		* this-> sample = NULL;
		* this-> scratch = NULL;
		* this-> high = NULL;
		* this-> med = NULL;
		* this-> low = NULL;
	}	
		
	addMusic(){
		music = Mix_LoadMUS( "beat.wav" );									
		scratch = Mix_LoadWAV( "scratch.wav" );								
		high = Mix_LoadWAV( "high.wav" );
		med = Mix_LoadWAV( "medium.wav" );
		low = Mix_LoadWAV( "low.wav" );
		sample = Mix_LoadWAV("../musics/fgi.wav");
	}
	
	init(){
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
	}
	
	play(){
		Mix_PlayChannel(-1, sample, -1);
	}
		
	~musica(){
		Mix_Quit();	
	}
			
};

#endif
