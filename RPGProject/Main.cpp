#include "SDL_mixer.h"

#include "Window.h"
#include "Font.h"
#include "Bg.h"
#include "Sprite.h"
#include "Sound.h"

int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		fprintf(stderr, "SDL could not initialize ERR : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		fprintf(stdout,"Warning: Linear texture filtering not enable\n");
	}

	// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)){
		fprintf(stderr,"SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return EXIT_FAILURE;
	}

	// Initialize SDL_ttf
	if (TTF_Init() == -1){
		fprintf(stderr,"SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return EXIT_FAILURE;
	}

	// Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		fprintf(stderr,"SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return EXIT_FAILURE;
	}

	Window window;
	Font font;
	Bg bg;
	Sprite sp;

	window.createWindow("No.1");
	bg.loadBG(window.getRenderer(), "bar.bmp");

	font.loadFont("SmileBASIC.ttf");
	font.setColor(0xff, 0xff, 0xff, 0xff);
	
	sp.loadSprite(window.getRenderer());
	sp.setSprite();

	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;

	Sound sound;
	sound.loadSound();

	Mix_VolumeChunk(sound.getSe(),30);
	Mix_VolumeMusic(30);

	font.setText(window.getRenderer(),"BGM : PROGRESS");
	font.render(window.getRenderer(), (SCREEN_WIDTH - font.getWidth()) / 2, (SCREEN_HEIGHT - font.getHeight()) / 2);

	font.setText(window.getRenderer(), "SE : SELECTION");
	font.render(window.getRenderer(), (SCREEN_WIDTH - font.getWidth()) / 2, (SCREEN_HEIGHT - font.getHeight()) / 2 + 20);

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			sp.handleEvent(e);
		}
		sp.move();
		bg.render(window.getRenderer());
		sp.render(window.getRenderer(), 0);
		SDL_RenderPresent(window.getRenderer());
	}

	window.free();

	return EXIT_SUCCESS;

}
