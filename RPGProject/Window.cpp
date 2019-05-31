#include "Window.h"

void Window::createWindow(std::string title) {
	
	mWindow=SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	
	if (mWindow == NULL) {
		fprintf(stderr,"Window cloud not be created ERR : %s\n",SDL_GetError());
		return;
	}
	
	mRenderer = SDL_CreateRenderer(mWindow, - 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (mRenderer == NULL) {
		fprintf(stderr, "Renderer cloud not be created ERR : %s\n", SDL_GetError());
		SDL_DestroyWindow(mWindow);
		return;
	}

}

void Window::free() {
	if (mWindow != NULL) {
		SDL_DestroyWindow(mWindow);
	}
	mWidth = 0;
	mHeight = 0;
}

void Window::clear() {
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);
	//SDL_RenderPresent(mRenderer);
}

SDL_Renderer* Window::getRenderer() {
	return mRenderer;
}

void Window::setTitle(std::string title) {
	SDL_SetWindowTitle(mWindow, title.c_str());
	return;
}