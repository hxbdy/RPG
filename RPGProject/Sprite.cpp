#include "Sprite.h"

Sprite::Sprite() {
	mTexture = NULL;
	mIsAnimating = false;
	mSpan = 0;
	mSpNum = 0;
	mPosX = 0;
	mPosY = 0;
	mVelX = 0;
	mVelY = 0;
}

void Sprite::loadSprite(SDL_Renderer* renderer, std::string path) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
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
	mWidth = loadedSurface->w / 3;
	mHeight = loadedSurface->h;
	SDL_FreeSurface(loadedSurface);
}

void Sprite::setSprite(int* locate) {

	for (int i = 0; i < SPRITE_FRAMES; i++) {
		mSpClips[i].x = locate[i * 4 + 0];
		mSpClips[i].y = locate[i * 4 + 1];
		mSpClips[i].w = locate[i * 4 + 2];
		mSpClips[i].h = locate[i * 4 + 3];
	}
}

void Sprite::render(SDL_Renderer* renderer, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { mPosX, mPosY, mSpClips[mSpNum].w, mSpClips[mSpNum].h };

	//SDL_RenderCopy(renderer, mTexture, &mSpClips[spriteNum],&renderQuad);
	SDL_RenderCopyEx(renderer, mTexture, &mSpClips[mSpNum], &renderQuad, NULL, NULL, flip);
}

void Sprite::move() {
	int spx, spy;
	mPosX += mVelX;
	//getSPPos(mPosX, mPosY, &spx, &spy);
	if (mPosX < 0) {
		mPosX = 0;
	}
	else if ((mPosX + mWidth > SCREEN_WIDTH) || checkCollision(mPosX,mPosY)) {
		mPosX -= mVelX;
	}
	mPosY += mVelY;
	//getSPPos(mPosX, mPosY, &spx, &spy);
	if (mPosY < 0) {
		mPosY = 0;
	}
	else if ((mPosY + mHeight > SCREEN_HEIGHT) || checkCollision(mPosX, mPosY)) {
		mPosY -= mVelY;
	}
	//fprintf(stdout, "(%03d,%03d) (%02d,%02d)\n", mPosX, mPosY,spx,spy);
}

bool checkCollisionRect(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

bool Sprite::checkCollision(int x, int y) {
	SDL_Rect sp;
	SDL_Rect wall;
	sp.x = x;
	sp.y = y;
	sp.w = SPRITE_WIDTH;
	sp.h = SPRITE_HEIGHT;
	for (int posY = 0; posY < 7; posY++) {
		for (int posX = 0; posX < 6; posX++) {
			if (mWall[posX + 6 * posY]) {
				wall.x = posX*SPRITE_WIDTH;
				wall.y = posY*SPRITE_HEIGHT;
				wall.w = SPRITE_WIDTH;
				wall.h = SPRITE_HEIGHT;
				if (checkCollisionRect(sp, wall)) {
					return true;
				}
			}
		}
	}
	return false;
}

void Sprite::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP:
			mVelY -= mHeight / 16;
			mSpNum = SPRITE_BACK;
			break;
		case SDLK_DOWN:
			mVelY += mHeight / 16;
			mSpNum = SPRITE_FRONT;
			break;
		case SDLK_LEFT:
			mVelX -= mWidth / 16;
			mSpNum = SPRITE_SIDE;
			break;
		case SDLK_RIGHT:
			mVelX += mWidth / 16;
			mSpNum = SPRITE_SIDE;
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP:
			mVelY += mHeight / 16;
			break;
		case SDLK_DOWN:
			mVelY -= mHeight / 16;
			break;
		case SDLK_LEFT:
			mVelX += mWidth / 16;
			break;
		case SDLK_RIGHT:
			mVelX -= mWidth / 16;
			break;
		}
	}
}

void Sprite::setPos(int x, int y) {
	mPosX = x;
	mPosY = y;
}

int Sprite::animate(void* spNum) {
	while (true) {
		for (int i = SPRITE_FRONT; i < SPRITE_FRAMES; i++) {
			*(int*)spNum = i;
			SDL_Delay(1000);
		}
	}
	return EXIT_SUCCESS;
}

void Sprite::anim() {
	SDL_Thread* thread = SDL_CreateThread(Sprite::animate, "animation", &mSpNum);
}

int Sprite::getPosX(void) {
	return mPosX;
}

int Sprite::getPosY(void) {
	return mPosY;
}

void Sprite::getSPPos(int px, int py, int* sx, int* sy) {
	*sx = px / SPRITE_WIDTH;
	*sy = py / SPRITE_HEIGHT;
}

TextWindow::TextWindow() {
	mPosY = BG_HEIGHT;
	play = false;
}

void TextWindow::anim() {
	if (!play) {
		return;
	}
	mPosY -= 50;
	if (mPosY < 0) {
		mPosY = 0;
	}
}

void TextWindow::render(SDL_Renderer* renderer, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { mPosX, mPosY, BG_WIDTH-mPosX, mHeight };
	SDL_RenderCopyEx(renderer, mTexture, &mSpClips[mSpNum], &renderQuad, NULL, NULL, flip);
}
