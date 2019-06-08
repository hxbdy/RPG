#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_thread.h>
#include <stdio.h>

#include <string>
#include <cmath>

#include "Timer.h"
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
	virtual void render(SDL_Renderer* renderer,SDL_RendererFlip flip = SDL_FLIP_NONE);
	void loadSprite(SDL_Renderer* renderer, std::string path);
	void setSprite(int* locate);
	void move();
	void handleEvent(SDL_Event& e);
	void setPos(int x, int y);
	virtual void anim();
protected:
	int mWidth,mHeight;
	int mPosX, mPosY;
	int mVelX, mVelY;
	int mSpan;
	int mSpNum;
	bool mIsAnimating;
	SDL_Rect mSpClips[SPRITE_FRAMES];
	SDL_Texture* mTexture;
	static int animate(void* frames);
};

class TextWindow : public Sprite {
public:
	TextWindow();
	void render(SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void anim();
	bool play;
};

#endif // !SPRITE_H_