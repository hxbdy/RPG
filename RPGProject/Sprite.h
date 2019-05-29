#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include <string>
#include <cmath>

#include "Window.h"

#ifndef SPRITE_H_

enum {
	SPRITE_FRONT,
	SPRITE_SIDE,
	SPRITE_BACK,
	SPRITE_FRAMES
};

class Sprite {
public:
	Sprite();
	void render(SDL_Renderer* renderer, int spriteNum);
	void loadSprite(SDL_Renderer* renderer);
	void setSprite(void);
	void move(void);
	void handleEvent(SDL_Event& e);
private:
	int mWidth,mHeight;
	int mPosX, mPosY;
	int mVelX, mVelY;
	SDL_Rect mSpClips[SPRITE_FRAMES];
	SDL_Texture* mTexture;
};

#define SPRITE_H_
#endif // !SPRITE_H_