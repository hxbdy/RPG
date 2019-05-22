#pragma once

#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>

#include <string>

#ifndef WINDOW_H_
#define WINDOW_H_

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

class Window {
public:
	void createWindow(std::string title);
	void free();
	void render();
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	int mWidth=SCREEN_WIDTH;
	int mHeight=SCREEN_HEIGHT;
};

#endif // !WINDOW_H_