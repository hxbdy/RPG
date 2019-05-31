#include "Bg.h"

void Bg::loadBG(SDL_Renderer* renderer,std::string path) {
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL) {
		fprintf(stderr,"Unable to load image ERR : %s\n", SDL_GetError() );
		return;
	}
	mTexture=SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (mTexture == NULL) {
		fprintf(stderr, "Unable to create texture from rendered text ERR : %s\n", TTF_GetError());
		return;
	}
	
	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	SDL_FreeSurface(loadedSurface);
}

void Bg::render(SDL_Renderer* renderer) {
	SDL_Rect renderQuad = { 0, 0, mWidth, mHeight };

	SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
	//SDL_RenderCopyEx(renderer, mTexture,NULL,&renderQuad,NULL,NULL,SDL_FLIP_NONE);
}

void Bg::setWall(bool* wall) {
	mWall = wall;
}

bool Bg::isWall(int x, int y) {
	return mWall[x + 6 * y];
}