#ifndef PLAYER_H
#define PLAYER_H

#include "animatedsprite.h"
#include "globals.h"
#include "level.h"
#include "enemy.h"

class Player : public AnimatedSprite
{
public:
	Player();
	Player(Graphics &graphics, Vector2 spawnPoint);
	//virtual ~Player();
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	/* void moveLeft
	 * Moves the player left by -dx
	 */
	void moveLeft();

	/* void moveRight
	 * Moves the player right by dx
	 */
	void moveRight();

	/* void stop moving
	 * Stop moving the player
	 */
	void stopMoving();

	/* void lookUp
	 * The player looks up
	 */
	void lookUp();

	/* void stopLookingUp
	 * The player stops looking up
	 */
	void stopLookingUp();

	/* void lookDown
	 * The player looks down OR interacts (turns around)
	 */
	void lookDown();

	/* void stopLookingDown
	 * The player stops looking down or interacting
	 */
	void stopLookingDown();

	/* void jump
	 * Starts jumping
	 */
	void jump();

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();

	void handleTileCollisions(std::vector<Rectangle> &others);
	void handleSlopeCollisions(std::vector<Slope> &others);
	void handleDoorCollision(std::vector<Door> &others, Level &level, Graphics &graphics);
	void handleEnemyCollisions(std::vector<std::shared_ptr<Enemy>> &others);

	const float getX() const;
	const float getY() const;

	const inline int getMaxHealth() const { return this->maxHealth; }
	const inline int getCurrentHealth() const { return this->currentHealth; }
	const inline Direction getDirection() const { return this->facing; }
	const inline bool getLookingUp() const { return this->lookingUp; }

	void gainHealth(int amount);

private:
	float dx, dy;

	Direction facing;

	bool grounded;

	bool lookingUp;
	bool lookingDown;

	int maxHealth;
	int currentHealth;
};

#endif