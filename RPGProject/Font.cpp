#include "Font.h"

void Font::loadFont(std::string path) {

	mFont=TTF_OpenFont(path.c_str(),20);

	if (mFont == NULL) {
		fprintf(stderr,"Failed to load font ERR : %s\n", TTF_GetError());
		return;
	}
}

void Font::setText(SDL_Renderer* renderer, std::string text) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, text.c_str(), mTextColor);

	if (textSurface == NULL) {
		fprintf(stderr, "Unable to render text surface ERR : %s\n", TTF_GetError());
		return;
	}

	mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	if (mTexture == NULL) {
		fprintf(stderr, "Unable to create texture from rendered text ERR : %s\n", TTF_GetError());
		return;
	}

	mWidth = textSurface->w;
	mHeight = textSurface->h;

	SDL_FreeSurface(textSurface);

}

void Font::render(SDL_Renderer* renderer,int x, int y) {

	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	SDL_RenderCopy(renderer, mTexture,NULL,&renderQuad);
	//SDL_RenderCopyEx(renderer, mTexture,NULL,&renderQuad,NULL,NULL,SDL_FLIP_NONE);
}

void Font::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
	mTextColor.r = red;
	mTextColor.g = green;
	mTextColor.b = blue;
	mTextColor.a = alpha;
}

void Font::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

int Font::getWidth() {
	return mWidth;
}

int Font::getHeight() {
	return mHeight;
}