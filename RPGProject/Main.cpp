#include "Window.h"
#include "Font.h"

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

	window.createWindow("No.1");

	SDL_SetRenderDrawColor(window.getRenderer(), 0x00, 0x00, 0xff, 0x00);
	SDL_RenderClear(window.getRenderer());

	font.loadFont("SmileBASIC.ttf");
	font.setColor(0xff, 0xff, 0xff, 0xff);
	font.setText(window.getRenderer(),"RION");
	
	fprintf(stdout,"TEXT TEXTURE (WIDTH ,HEIGHT) (%02d, %02d)\n", font.getWidth(),font.getHeight());
	
	font.render(window.getRenderer(), (SCREEN_WIDTH-font.getWidth()) / 2, (SCREEN_HEIGHT-font.getHeight()) / 2);

	SDL_RenderPresent(window.getRenderer());
	SDL_Delay(5000);

	window.free();

	return EXIT_SUCCESS;

}
