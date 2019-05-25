#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include <string>
#include <cmath>

#ifndef BG_H_
#define BG_H_

class Bg {
public:
	void loadBG(SDL_Renderer* renderer,std::string path);
	void render(SDL_Renderer* renderer);
	void free();
private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};

#endif // !BG_H_
