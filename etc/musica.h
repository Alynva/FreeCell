#ifndef MUSICA
#define MUSICA

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

class Musica {

	Mix_Chunk* song;
//	Mix_Music* song;

	public:
		Musica();	
		~Musica();
		
		friend void musicFinished(int);
		
		bool init();
		void addMusic(const char*);
		void play();
		void pause();
		void resume();
		void stop();
		void next();
		void previous();
		void setVolume(int);

};

#endif
