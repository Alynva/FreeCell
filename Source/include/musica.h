#ifndef MUSICA
#define MUSICA

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

class Musica {

	SDL_Event event;
	Mix_Music* song;

	public:
	
		Musica() {
			this->song = NULL;
		};
			
		~Musica() {
			Mix_FreeMusic(this->song);
			this->song = NULL;
			Mix_Quit();	
		};
		
		bool init() {
//			Mix_AllocateChannels(16);
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
			
		void addMusic(const char* path) {
			this->song = Mix_LoadMUS(path);
		};
		
		void play() {
			Mix_FadeInMusic(this->song, -1, 5000);
		};
		
		void pause() {
			Mix_PauseMusic();
		}
		
		void resume() {
			Mix_ResumeMusic();
		}
		
		void setVolume(int vol) {
			Mix_VolumeMusic(vol);
		};

};

#endif
