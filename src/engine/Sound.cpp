#include "sound.h"

Mix_Music* backgroundMusic = NULL;
Mix_Chunk* coinSFX = NULL;
Mix_Chunk* bombSFX = NULL;

// https://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php

Sound::Sound() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        //success = false;
    }

    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        //success = false;
    }


    // coinSFX = Mix_LoadWAV( "./resources/Sounds.coin_flip.wav" );
    bombSFX = Mix_LoadWAV("./resources/Sounds.bomb_x.wav");
    backgroundMusic = Mix_LoadMUS("./resources/Sounds/Soft-piano-music.wav");
}

void Sound::playSFX() {
    Mix_PlayChannel(-1, bombSFX, 0);
}

void Sound::playMusic() {
    Mix_PlayMusic(backgroundMusic, -1);
}