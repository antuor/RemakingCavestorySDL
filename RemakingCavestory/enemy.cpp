#include "enemy.h"

//Base enemy class
Enemy::Enemy() {}


Enemy::Enemy(Graphics &graphics, std::string filePath, int sourceX, int sourceY,
	int width, int height, Vector2 spawnPoint, int timeToUpdate) :
	AnimatedSprite(graphics, filePath, sourceX, sourceY, width, height,
		spawnPoint.x, spawnPoint.y, timeToUpdate),
	direction(LEFT),
	maxHealth(0),
	currentHealth(0),
	count(0)
{}

void Enemy::update(int elapsedTime, Player &player)
{
	AnimatedSprite::update(elapsedTime);
}

void Enemy::draw(Graphics &graphics)
{
	AnimatedSprite::draw(graphics, this->x, this->y);
}

//Bat class
Bat::Bat() {}

Bat::Bat(Graphics &graphics, Vector2 spawnPoint) :
	Enemy(graphics, "content/sprites/NpcCemet.png", 32, 32, 16, 16, spawnPoint, 140),
	startingX(spawnPoint.x),
	startingY(spawnPoint.y),
	shouldMoveUp(false)
{
	this->damage = -1;
	this->currentHealth = 3;
	this->setupAnimations();
	this->playAnimation("FlyLeft");
}

void Bat::update(int elapsedTime, Player &player)
{
	this->direction = player.getX() > this->x ? RIGHT : LEFT;
	this->playAnimation(this->direction == RIGHT ? "FlyRight" : "FlyLeft");

	//Move up or down
	this->y += this->shouldMoveUp ? -.5 : .5;
	if (this->y > (this->startingY + 30) || this->y < (this->startingY - 30))
	{
		this->shouldMoveUp = !this->shouldMoveUp;
	}

	if (this->currentHealth < 0)
	{
		this->damage = 0;
		this->setVisible(false);
	}

	Enemy::update(elapsedTime, player);
}

void Bat::draw(Graphics &graphics)
{
	Enemy::draw(graphics);
}

void Bat::touchPlayer(Player* player)
{
	if (this->count == 0)
	{
		player->gainHealth(this->damage);
		this->count++;
	}	
	else {
		this->count++;
		if (this->count > 20)
			this->count = 0;
	}
}

void Bat::touchBullet()
{
	this->currentHealth -= 2;
}

void Bat::animationDone(std::string currentAnimation)
{

}

void Bat::setupAnimations()
{
	this->addAnimation(3, 2, 32, "FlyLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 2, 48, "FlyRight", 16, 16, Vector2(0, 0));
}