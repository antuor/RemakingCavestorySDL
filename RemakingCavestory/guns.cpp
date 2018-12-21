#include "guns.h"

Guns::Guns() {}

Guns::Guns(Graphics &graphics, Player &player) :
	AnimatedSprite(graphics, "content/sprites/Arms.png", 2, 11, 25, 3,
		player.getX(), player.getY(), 100),
	direction(player.getDirection()),
	damage(2)
{
	this->setupAnimations();
	this->playAnimation("GunLeft");
}

void Guns::update(int elapsedTime, Player &player)
{
	this->x = player.getX();
	this->y = player.getY();

	AnimatedSprite::update(elapsedTime);
}

void Guns::draw(Graphics &graphics)
{
	AnimatedSprite::draw(graphics, this->x, this->y);
}

void Guns::animationDone(std::string currentAnimation) {}

void Guns::setupAnimations()
{
	addAnimation(1, 2, 11, "GunLeft", 25, 3, Vector2(0, 0));
}