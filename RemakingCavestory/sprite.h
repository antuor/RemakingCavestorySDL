#ifndef SPRITE_H
#define SPRITE_H

/* Sprite class
 * Holds all information for individual sprites
 */

#include "graphics.h"
#include <iostream>
#include "globals.h"
#include "rectangle.h"

class Sprite
{
public:
	Sprite();
	Sprite(Graphics &graphics, const std::string &filePath, int sourseX, int sourseY, int width, int height, 
		float posX, float posY);
	virtual ~Sprite();
	virtual void update();
	void draw(Graphics &graphics, int x, int y);

	const Rectangle getBoundingBox() const;
	const sides::Side getCollisionSide(Rectangle &other) const;

	const inline float getX() const { return this->x; }
	const inline float getY() const { return this->y; }

	void setSourceRectX(int value);
	void setSourceRectY(int value);
	void setSourceRectW(int value);
	void setSourceRectH(int value);

protected:
	SDL_Rect sourceRect;
	SDL_Texture* spriteSheet;

	Rectangle boundingBox;

	float x, y;
private:
	
};

#endif