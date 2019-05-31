
#include "Sound.h"

void Sound::loadSound() {
	mMusic = Mix_LoadMUS("progress.mp3");
	if (mMusic == NULL) {
		fprintf(stderr, "Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return;
	}
	mSe = Mix_LoadWAV("selection.mp3");
	if (mSe == NULL) {
		fprintf(stderr, "Failed to load se! SDL_mixer Error: %s\n", Mix_GetError());
		return;
	}
}

Mix_Music* Sound::getMusic() {
	return mMusic;
}

Mix_Chunk* Sound::getSe() {
	return mSe;
}