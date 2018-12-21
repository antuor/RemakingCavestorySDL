#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "globals.h"
#include "animatedsprite.h"

class Enemy : public AnimatedSprite
{
public:
	Enemy();
	Enemy(Graphics &graphics, std::string filePath, int sourceX,
		int sourceY, int width, int height, Vector2 spawnPoint, int timeToUpdate);

	virtual void update(int elapsedTime, Player &player);
	virtual void draw(Graphics &graphics);
	virtual void touchPlayer(Player* player) = 0;
	virtual void touchBullet() = 0;
	
	const inline int getMaxHealth() const { return this->maxHealth; }
	const inline int getCurrentHealth() const { return this->currentHealth; }
protected:
	Direction direction;

	int maxHealth, currentHealth, count, damage;
};

class Bat : public Enemy
{
public:
	Bat();
	Bat(Graphics &graphics, Vector2 spawnPoint);

	void update(int elapsedTime, Player &player);
	void draw(Graphics &graphics);
	void touchPlayer(Player* player);
	void touchBullet();

	void animationDone(std::string CurrentAnimation);
	void setupAnimations();
private:
	float startingX, startingY;
	bool shouldMoveUp;
};

#endif