#pragma once

#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>

#include <string>

#ifndef WINDOW_H_
#define WINDOW_H_

#define SCREEN_WIDTH  288
#define SCREEN_HEIGHT 336

class Window {
public:
	void createWindow(std::string title);
	void free();
	void clear();
	void setTitle(std::string title);
	SDL_Renderer* getRenderer();
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	int mWidth=SCREEN_WIDTH;
	int mHeight=SCREEN_HEIGHT;
};

#endif // !WINDOW_H_