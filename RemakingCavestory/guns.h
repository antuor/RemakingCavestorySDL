#pragma once

#include "animatedsprite.h"
#include "player.h"

class Guns : public AnimatedSprite
{
public:
	Guns();
	Guns(Graphics &graphics, Player &player);

	void update(int elapsedTime, Player &player);
	void draw(Graphics &graphics);
	
	void animationDone(std::string currentAnimation);
	void setupAnimations();
	
private:
	Direction direction;

	int damage;
};

