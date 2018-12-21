#ifndef SHOOT_H
#define SHOOT_H

#include "animatedsprite.h"
#include "player.h"
#include "enemy.h"

class Shoot : public AnimatedSprite
{
public:
	Shoot();
	Shoot(Graphics &graphics, Player &player);

	void handleEnemyCollisions(std::vector<std::shared_ptr<Enemy>> &others);

	void update(int elapsedTime);
	void draw(Graphics &graphics);

	void animationDone(std::string currentAnimation);
	void setupAnimations();

private:
	Direction direction;

	bool lookingUp;

	int damage;
	int startingX, startingY;
};

#endif