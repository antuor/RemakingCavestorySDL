#ifndef TILE_H
#define TILE_H

#include "graphics.h"

class Tile
{
public:
	Tile();
	Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position);
	~Tile();

	void update(int elapsedTime);
	void draw(Graphics &graphics);
protected:
	SDL_Texture* tileset;
	Vector2 size;
	Vector2 tilesetPosition;
	Vector2 position;
};

#endif