#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include <string>
#include <cmath>

#include "Sprite.h"

#ifndef BG_H_
#define BG_H_

#define BG_WIDTH  288
#define BG_HEIGHT 336

class Bg {
public:
	void loadBG(SDL_Renderer* renderer,std::string path);
	void render(SDL_Renderer* renderer);
	void setWall(bool* wall);
	bool isWall(int x, int y);
	void free();
private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
	bool* mWall;
};

#endif // !BG_H_
