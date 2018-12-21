#ifndef HUD_H
#define HUD_H

#include "player.h"

class HUD
{
public:
	HUD();
	HUD(Graphics &graphics, Player &player);

	void update(int elapsedTime, Player &player);
	void draw(Graphics &graphics);

private:
	Player player;

	//Health sprites
	Sprite healthBarSprite;
	Sprite healthNumber1;
	Sprite currentHealthBar;

	//Exp sprites
	Sprite lvWorld;
	Sprite lvNumber;
	Sprite expBar;

	//Weapon info
	Sprite slash;
	Sprite dashes;
};

#endif 