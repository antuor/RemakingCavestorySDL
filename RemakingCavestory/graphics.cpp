#include "graphics.h"

Graphics::Graphics()
{
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &this->window, &this->renderer);
	SDL_SetWindowTitle(this->window, "Cave story");
}


Graphics::~Graphics()
{
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath)
{
	if (this->spriteSheets.count(filePath) == 0)
	{
		this->spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return this->spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectungle, SDL_Rect* destinationRectandle) 
{
	SDL_RenderCopy(this->renderer, texture, sourceRectungle, destinationRectandle);
}

void Graphics::flip() 
{
	SDL_RenderPresent(this->renderer);
}

void Graphics::clear() 
{
	SDL_RenderClear(this->renderer);
}

SDL_Renderer* Graphics::getRenderer() const 
{
	return this->renderer;
}