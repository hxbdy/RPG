#include "Window.h"
#include "Font.h"

int main(int argc, char* argv[]) {
	SDL_Renderer* gRenderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL could not initialize ERR : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	Window window;
	Font font;

	window.createWindow("No.1");
	SDL_Delay(5000);
	window.free();
	return EXIT_SUCCESS;

}
