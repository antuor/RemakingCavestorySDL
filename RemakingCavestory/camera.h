#ifndef CAMERA_H
#define CAMERA_H

#include "graphics.h"
#include "player.h"

class Camera
{
public:
	static void Init();
	static SDL_Rect GetRect();
	static void Update(float elapsedTime, Player &player);
};

#endif 