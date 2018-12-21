#include "player.h"
#include "audio.h"

namespace player_constants
{
	const float WALK_SPEED = 0.2f;
	const float JUMP_SPEED = 0.7f;

	const float GRAVITY = 0.002f;
	const float GRAVITY_CAP = 0.8f;
}

Player::Player() {}

Player::Player(Graphics &graphics, Vector2 spawnPoint) :
	AnimatedSprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100),
	dx(0), dy(0), facing(RIGHT), grounded(false), lookingDown(false), lookingUp(false), maxHealth(3), currentHealth(3)
{
	//graphics.loadImage("content/sprites/MyChar.png");
	this->setupAnimations();
	this->playAnimation("RunRight");
}

//Player::~Player() {}

void Player::setupAnimations()
{
	this->addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 3, 0, "IdleLeftUp", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 3, 16, "IdleRightUp", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 3, 0, "RunLeftUp", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 3, 16, "RunRightUp", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 6, 0, "LookDownLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 6, 16, "LookDownRight", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 7, 0, "LookBackwardsLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 7, 16, "LookBackwardsRight", 16, 16, Vector2(0, 0));
}

void Player::animationDone(std::string currentAnimation) {}

const float Player::getX() const
{
	return this->x;
}

const float Player::getY() const
{
	return this->y;
}

void Player::moveLeft()
{
	if (this->lookingDown == true && this->grounded == true)
		return;
	this->dx = -player_constants::WALK_SPEED;
	if (this->lookingUp == false)
		this->playAnimation("RunLeft");
	this->facing = LEFT;
}

void Player::moveRight()
{
	if (this->lookingDown == true && this->grounded == true)
		return;
	this->dx = player_constants::WALK_SPEED;
	if (this->lookingUp == false)
		this->playAnimation("RunRight");
	this->facing = RIGHT;
}

void Player::stopMoving()
{
	this->dx = 0.0f;
	if(this->lookingUp == false && this->lookingDown == false)
		this->playAnimation(this->facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::lookUp()
{
	this->lookingUp = true;
	if (this->dx == 0)
		this->playAnimation(this->facing == RIGHT ? "IdleRightUp" : "IdleLeftUp");
	else
		this->playAnimation(this->facing == RIGHT ? "RunRightUp" : "RunLeftUp");
}

void Player::stopLookingUp()
{
	this->lookingUp = false;
}

void Player::lookDown()
{
	this->lookingDown = true;
	if (this->grounded == true)
	{
		//We need to interact (turn backwards)
		this->playAnimation(this->facing == RIGHT ? "LookBackwardsRight" : "LookBackwardsLeft");
	}
	else
		this->playAnimation(this->facing == RIGHT ? "LookDownRight" : "LookDownLeft");
}

void Player::stopLookingDown()
{
	this->lookingDown = false;
}

void Player::jump()
{
	if (this->grounded)
	{
		playSound("content/sounds/Bass03.wav", SDL_MIX_MAXVOLUME);
		this->dy = 0;
		this->dy -= player_constants::JUMP_SPEED;
		this->grounded = false;
	}
}

/* void handleTileCollisions
 * Handles collisions with ALL tiles the player is colliding with
 */
void Player::handleTileCollisions(std::vector<Rectangle> &others)
{
	//Figure out what side the collision happened on and move the player accordingly
	for (int i = 0; i < others.size(); i++)
	{
		sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
		if (collisionSide != sides::NONE)
		{
			switch (collisionSide)
			{
			case sides::TOP:
				this->dy = 0;
				this->y = others.at(i).getBottom() + 1;
				if (this->grounded)
				{
					this->dx = 0;
					this->x -= this->facing == RIGHT ? 1.0f : -1.0f;
				}
				break;
			case sides::BOTTOM:
				this->y = others.at(i).getTop() - this->boundingBox.getHeight() - 1;
				this->dy = 0;
				this->grounded = true;
				break;
			case sides::LEFT:
				this->x = others.at(i).getRight() + 1;
				break;
			case sides::RIGHT:
				this->x = others.at(i).getLeft() - this->boundingBox.getWidth() - 1;
				break;
			}
			if (collisionSide == sides::NONE)
				this->grounded = false;
		}
	}
}

/* void handleSlopeCollisions
 * Handles collisions with ALL slopes the player is colliding with
 */
void Player::handleSlopeCollisions(std::vector<Slope> &others)
{
	for(int i = 0; i < others.size(); i++)
	{
		//Calculate where on the slope the player's bottom center is touching
		//and use y = mx + b to figure out the y position to place him at
		//First calculate "b" (slope intercept) using one of the points (b = y - mx)
		int b = (others.at(i).getP1().y - (others.at(i).getSlope() * fabs(others.at(i).getP1().x)));

		//Now get player's center x
		int centerX = this->boundingBox.getCenterX();

		//Now pass that X into the equation y = mx + b (using our newly found b and x) to get the new y position
		int newY = (others.at(i).getSlope() * centerX) + b - 8; //8 is temporary fix a problem

		//Re-position the player to the correct "y"
		if (this->grounded)
		{
			this->y = newY - this->boundingBox.getHeight();
			this->grounded = true;
		}
	}
}

void Player::handleDoorCollision(std::vector<Door> &others, Level &level, Graphics &graphics)
{
	//Check if the player is grounded and holding the down arrow
	//If so, go through the door
	//If not, do nothing
	for (int i = 0; i < others.size(); i++)
	{
		if (this->grounded == true && this->lookingDown == true)
		{
			level = Level(others.at(i).getDestination(), graphics);
			this->x = level.getPlayerSpawnPoint().x;
			this->y = level.getPlayerSpawnPoint().y;
		}
	}
}

void Player::handleEnemyCollisions(std::vector<std::shared_ptr<Enemy>> &others)
{
	for (int i = 0; i < others.size(); i++)
	{
		others.at(i)->touchPlayer(this);
	}
}

void Player::gainHealth(int amount)
{
	if ((this->currentHealth + amount) >= this->maxHealth)
		this->currentHealth = this->maxHealth;
	else
		this->currentHealth += amount;
}

void Player::update(float elapsedTime)
{
	//Apply gravity
	if (this->dy <= player_constants::GRAVITY_CAP)
		this->dy += player_constants::GRAVITY * elapsedTime;
	//Move by dx
	this->x += this->dx * elapsedTime;
	//Move by dy
	this->y += this->dy * elapsedTime;

	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics)
{
	AnimatedSprite::draw(graphics, this->x, this->y);
}