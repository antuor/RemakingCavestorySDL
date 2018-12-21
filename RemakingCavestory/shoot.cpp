#include "shoot.h"

Shoot::Shoot() {}

Shoot::Shoot(Graphics &graphics, Player &player) : 
	AnimatedSprite(graphics, "content/sprites/Bullet.png", 35, 10, 6, 6,
	(player.getX() + 9), (player.getY() + 9), 100),
	direction(player.getDirection()),
	damage(2)
{
	this->startingX = player.getX() + 9;
	this->startingY = player.getY() + 9;
	this->lookingUp = player.getLookingUp();
	this->setupAnimations();
	this->playAnimation("Shoot");
}

void Shoot::handleEnemyCollisions(std::vector<std::shared_ptr<Enemy>> &others)
{
	for (int i = 0; i < others.size(); i++)
	{
		if(this->getVisible() == true)
			others.at(i)->touchBullet();
	}
}

void Shoot::update(int elapsedTime)
{
	if (this->x > (this->startingX + 110) || this->x < (this->startingX - 110) || this->y < (this->startingY - 110))
	{
		this->setVisible(false);
	}
	else
	{
		if (this->lookingUp == false)
		{
			if (this->direction == LEFT)
				this->x -= 5;
			if (this->direction == RIGHT)
				this->x += 5;
		}
		else
			this->y -= 5;
	}
	AnimatedSprite::update(elapsedTime);
}

void Shoot::draw(Graphics &graphics)
{
	AnimatedSprite::draw(graphics, this->x, this->y);
}

void Shoot::animationDone(std::string currentAnimation)
{

}

void Shoot::setupAnimations()
{
	this->addAnimation(1, 35, 10, "Shoot", 6, 6, Vector2(0, 0));
}