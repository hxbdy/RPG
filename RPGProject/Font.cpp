#include "Font.h"

Font::Font() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mDisplayLength = 1;
	mPosX = 10;
	mPosY = 15;
}

void Font::loadFont(std::string path) {

	mFont=TTF_OpenFont(path.c_str(),10);

	if (mFont == NULL) {
		fprintf(stderr,"Failed to load font ERR : %s\n", TTF_GetError());
		return;
	}
}

void Font::setText(SDL_Renderer* renderer, std::string text) {
	free();

	std::string renderText;
	int len = text.length();

	if (len<=mDisplayLength) {
		renderText = text;
	}
	else {
		renderText=text.substr(0, mDisplayLength);
		mDisplayLength++;
	}

	SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, renderText.c_str(), mTextColor);

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

void Font::render(SDL_Renderer* renderer) {

	SDL_Rect renderQuad = { mPosX, mPosY, mWidth, mHeight };

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