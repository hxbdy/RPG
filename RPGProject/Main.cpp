#include "SDL_mixer.h"

#include "Window.h"
#include "Font.h"
#include "Bg.h"
#include "Sprite.h"
#include "Sound.h"
#include "Timer.h"

int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		fprintf(stderr, "SDL could not initialize ERR : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		fprintf(stdout, "Warning: Linear texture filtering not enable\n");
	}

	// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return EXIT_FAILURE;
	}

	// Initialize SDL_ttf
	if (TTF_Init() == -1) {
		fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return EXIT_FAILURE;
	}

	// Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return EXIT_FAILURE;
	}

	Window window;
	Font font;
	Bg bg;

	Sprite sp;
	Sprite npc;
	TextWindow textWindow;

	Timer fps;
	std::stringstream timeText;

	// FPS Counter
	int countedFrames = 0;

	window.createWindow("RPG | FPS : 00");
	bg.loadBG(window.getRenderer(), "convenience.bmp");

	font.loadFont("SmileBASIC.ttf");
	font.setColor(0xff, 0xff, 0xff, 0x00);
	std::string text="Listening to favorite music.";

	sp.loadSprite(window.getRenderer(), "staff.png");
	int playerLocate[] = { 0,0,48,48,48,0,48,48,96,0,48,48 };
	sp.setSprite(playerLocate);
	sp.setPos(240, 192);

	npc.loadSprite(window.getRenderer(),"staff.png");
	int npcLocate[] = {0,0,48,48,48,0,48,48,96,0,48,48};
	npc.setSprite(npcLocate);
	npc.setPos(48, 192);

	textWindow.loadSprite(window.getRenderer(), "textWindow.bmp");
	int textWindowLocate[] = { 0,0,640,100,0,0,640,100 ,0,0,640,100 };
	textWindow.setSprite(textWindowLocate);
	textWindow.setPos(0, BG_HEIGHT);

	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;

	Sound sound;
	sound.loadSound();

	Mix_VolumeChunk(sound.getSe(),30);
	Mix_VolumeMusic(30);

	fps.start();
	npc.anim();
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
				switch (e.key.keysym.sym) {
				case SDLK_UP:
					textWindow.play = true;
					break;
				case SDLK_DOWN:
					textWindow.play = false;
					break;
				}
			}
			sp.handleEvent(e);
		}

		//Calculate and correct fps
		float avgFPS = countedFrames / (fps.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}

		//Set text to be rendered
		timeText.str("");
		timeText << "RPG | FPS : " << avgFPS;
		window.setTitle(timeText.str());

		//Clear screen
		SDL_SetRenderDrawColor(window.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(window.getRenderer());

		//font.render(window.getRenderer(), (SCREEN_WIDTH - font.getWidth()) / 2, (SCREEN_HEIGHT - font.getHeight()) / 2);

		sp.move();
		textWindow.anim();

		bg.render(window.getRenderer());
		sp.render(window.getRenderer(),SDL_FLIP_HORIZONTAL);
		npc.render(window.getRenderer(), SDL_FLIP_NONE);
		textWindow.render(window.getRenderer());
		
		if (textWindow.getPosY() == 0) {
			font.setText(window.getRenderer(),text);
			font.render(window.getRenderer());
		}

		SDL_RenderPresent(window.getRenderer());

		countedFrames++;
	}

	window.free();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;

}