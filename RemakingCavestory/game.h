#ifndef GAME_H
#define GAME_H

/* Game class
 * This class holds all information for our main game loop
 */

#include "input.h"
#include "level.h"
#include "hud.h"
#include "audio.h"
#include "guns.h"
#include "shoot.h"
#include "camera.h"

#include <algorithm>

class Game
{
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	Player player;

	Level level;

	HUD hud;

	Graphics graphics;

	Guns guns;

	Shoot shoot;
};

#endif 