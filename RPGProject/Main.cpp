#include "Window.h"
#include "Font.h"
#include "Bg.h"
#include "Sprite.h"

int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL could not initialize ERR : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	Window window;
	Font font;
	Bg bg;
	Sprite sp;

	window.createWindow("No.1");
	bg.loadBG(window.getRenderer(), "bar.bmp");

	font.loadFont("SmileBASIC.ttf");
	font.setColor(0xff, 0xff, 0xff, 0xff);
	
	font.setText(window.getRenderer(),"RION");
	
	sp.loadSprite(window.getRenderer());
	sp.setSprite();

	int spNum = 0;
	while (true) {
		bg.render(window.getRenderer());
		sp.render(window.getRenderer(), spNum, 16, 16);
		//font.render(window.getRenderer(), (SCREEN_WIDTH - font.getWidth()) / 2, (SCREEN_HEIGHT - font.getHeight()) / 2);
		SDL_RenderPresent(window.getRenderer());
		spNum++;
		if (spNum > SPRITE_FRAMES) {
			spNum = 0;
		}
	}

	window.free();

	return EXIT_SUCCESS;

}
