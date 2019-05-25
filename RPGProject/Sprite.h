#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include <string>
#include <cmath>

#ifndef SPRITE_H_

enum {
	SPRITE_FRONT,
	SPRITE_SIDE,
	SPRITE_BACK,
	SPRITE_FRAMES
};

class Sprite {
public:
	void render(SDL_Renderer* renderer, int spriteNum, int x, int y);
	void loadSprite(SDL_Renderer* renderer);
	void setSprite(void);
private:
	int mWidth;
	int mHeight;
	SDL_Rect mSpClips[SPRITE_FRAMES];
	SDL_Texture* mTexture;
};

#define SPRITE_H_
#endif // !SPRITE_H_