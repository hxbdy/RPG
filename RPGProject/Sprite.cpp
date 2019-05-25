#include "Sprite.h"

void Sprite::loadSprite(SDL_Renderer* renderer) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load("staff.png");
	if (loadedSurface == NULL) {
		fprintf(stderr, "Unable to load image ERR : %s\n", IMG_GetError());
		return;
	}
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGBA(loadedSurface->format, 0xff, 0xff, 0xff, 0xff));
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (newTexture == NULL) {
		fprintf(stderr, "Unable to create texture from SDL ERR : %s\n", SDL_GetError());
		return;
	}
	mTexture = newTexture;
	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;
	SDL_FreeSurface(loadedSurface);
}

void Sprite::setSprite() {
	mSpClips[SPRITE_FRONT].x = 0;
	mSpClips[SPRITE_FRONT].y = 0;
	mSpClips[SPRITE_FRONT].w = 96;
	mSpClips[SPRITE_FRONT].h = 96;

	mSpClips[SPRITE_SIDE].x = 96;
	mSpClips[SPRITE_SIDE].y = 0;
	mSpClips[SPRITE_SIDE].w = 96;
	mSpClips[SPRITE_SIDE].h = 96;

	mSpClips[SPRITE_BACK].x = 192;
	mSpClips[SPRITE_BACK].y = 0;
	mSpClips[SPRITE_BACK].w = 96;
	mSpClips[SPRITE_BACK].h = 96;
}

void Sprite::render(SDL_Renderer* renderer,int spriteNum,int x,int y) {
	SDL_Rect renderQuad = { x, y, mSpClips[spriteNum].w, mSpClips[spriteNum].h };

	SDL_RenderCopy(renderer, mTexture, &mSpClips[spriteNum],&renderQuad);
	//SDL_RenderCopyEx(renderer, mTexture,NULL,&renderQuad,NULL,NULL,SDL_FLIP_NONE);
}