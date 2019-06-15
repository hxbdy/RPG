#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include <string>

#include "SDL_mixer.h"

#ifndef SOUND_H_
#define SOUND_H_

class Sound {
public:
	void puase();
	void play();
	void halt();
	void resume();
	void loadSound();
	Mix_Music* getMusic();
	Mix_Chunk* getSe();
private:
	Mix_Music* mMusic;
	Mix_Chunk* mSe;
};

#endif // SOUND_H_