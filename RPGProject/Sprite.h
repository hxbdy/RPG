#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include <string>
#include <cmath>

#include "Window.h"
#include "Bg.h"

#ifndef SPRITE_H_
#define SPRITE_H_

#define SPRITE_WIDTH  48
#define SPRITE_HEIGHT 48

enum {
	SPRITE_FRONT,
	SPRITE_SIDE,
	SPRITE_BACK,
	SPRITE_FRAMES
};

class Sprite {
public:
	Sprite();
	void render(SDL_Renderer* renderer, int spriteNum, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void loadSprite(SDL_Renderer* renderer);
	void setSprite(void);
	void move(void);
	void handleEvent(SDL_Event& e);
	void setPos(int x, int y);
	bool checkCollision(bool* wall);
private:
	int mWidth,mHeight;
	int mPosX, mPosY;
	int mVelX, mVelY;
	bool isAnim;
	SDL_Rect mSpClips[SPRITE_FRAMES];
	SDL_Texture* mTexture;
};

#endif // !SPRITE_H_