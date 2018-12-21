#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "sprite.h"
#include <vector>

/* AnimatedSprite class
 * Holds logic for animating sprites
 */

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();
	AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourseX, int sourseY, int width, int height,
		float posX, float posY, float timeToUpdate);
	~AnimatedSprite();

	/* void playAnimation
	 * Plays the animation provided if it's not already playing
	 */
	void playAnimation(std::string animation, bool once = false);

	/* void update
	 * Updates the animated sprite (timer)
	 */
	void update(int elapsedTime);

	/* void draw
	 * Draws the sprite to the screen
	 */
	void draw(Graphics &graphics, int x, int y);

	const inline bool getVisible() const { return this->visible; }
protected:
	double timeToUpdate;
	bool currentAnimationOnce;// stars = false;
	std::string currentAnimation;

	/* void addAnimation
	 * Adds an animatoins to the map of animations for the sprite
	 */
	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

	/* void addAnimation
	 * Adds an animation to the map of animations for the sprite
	 */
	void resetAnimations();

	/* void stopAnimation
	 * Stops the current animation
	 */
	void stopAnimation();

	/* void setVisible
	 * Changes the visibility of the animated sprite
	*/
	void setVisible(bool visible);

	/* void animationDone
	 * Logic that happens when an animation ends
	 */
	virtual void animationDone(std::string currentAnimation) = 0;

	/* void setupAnimation
	 * A reqired function that sets up all animations for a sprite
	 */
	virtual void setupAnimations() = 0;

private:
	std::map<std::string, std::vector<SDL_Rect>> animations;
	std::map<std::string, Vector2> offsets;

	int frameTndex; //starscounter = 0;
	double timeElapsed;
	bool visible;
};

#endif