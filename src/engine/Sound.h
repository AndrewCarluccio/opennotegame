#ifndef SOUND_H
#define SOUND_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>

class Sound {

public:
	Sound();
	~Sound();

	void playSFX();
	void playMusic();
	Mix_Music* backgroundMusic = NULL;
	Mix_Chunk* bombSFX = NULL;
	Mix_Chunk* coinSFX = NULL;


private:


};

#endif