#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>

#include <string>
#include <cmath>

#ifndef FONT_H_
#define FONT_H_

class Font {
public:
	Font();
	void render(SDL_Renderer* renderer,int x,int y);
	void loadFont(std::string path);
	void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
	void setText(SDL_Renderer* renderer,std::string text);
	void free();
	int getWidth();
	int getHeight();
private:
	SDL_Texture* mTexture;
	SDL_Color mTextColor;
	TTF_Font* mFont;
	int mWidth;
	int mHeight;
};

#endif // !FONT_H_