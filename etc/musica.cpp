#include "../include/musica.h"

Musica::Musica() {
	this->song = NULL;
};
	
Musica::~Musica() {
	Mix_FreeChunk(this->song);
//	Mix_FreeMusic(this->song);
	this->song = NULL;
	Mix_Quit();	
};

		
void musicFinished(int channel) {
//	back_music.play();
//	this->next();
	SDL_Log("finished %i", channel);
}

bool Musica::init() {
//	Mix_AllocateChannels(16);
	if(SDL_Init(SDL_INIT_AUDIO)==-1) {									
	    SDL_Log("SDL_Init: %s\n", SDL_GetError());
	    return false;
	}
	   
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
	    SDL_Log("Mix_OpenAudio: %s\n", Mix_GetError());
	    return false;
	}
	
	Mix_ChannelFinished(musicFinished);
//	Mix_HookMusicFinished(musicFinished);
	
	return true;
};
	
void Musica::addMusic(const char* path) {
	this->song = Mix_LoadWAV(path);
//	this->song = Mix_LoadMUS(path);
};

void Musica::play() {
	Mix_FadeInChannel(-1, this->song, 1, 5000);
//	Mix_FadeInMusic(this->song, -1, 5000);
};

void Musica::pause() {
	Mix_Pause(-1);
//	Mix_PauseMusic();
}

void Musica::resume() {
	Mix_Resume(-1);
//	Mix_ResumeMusic();
}

void Musica::stop() {
	Mix_HaltChannel(-1);
}

void Musica::next() {
	
}

void Musica::previous() {
	
}

void Musica::setVolume(int vol) {
	Mix_Volume(-1, vol);
//	Mix_VolumeMusic(vol);
};
