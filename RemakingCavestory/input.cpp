#include "input.h"

//This function gets called at the beginning of each new frame
//to reset the keys that are no longer relevant
void Input::beginNewFrame() 
{
	this->pressedKeys.clear();
	this->releasedKeys.clear();
}

//This gets called when a key has been pressed
void Input::KeyDownEvent(const SDL_Event& event) 
{
	this->pressedKeys[event.key.keysym.scancode] = true;
	this->heldKeys[event.key.keysym.scancode] = true;
}

//This gets called when a key is released
void Input::KeyUpEvent(const SDL_Event& event) 
{
	this->releasedKeys[event.key.keysym.scancode] = true;
	this->heldKeys[event.key.keysym.scancode] = false;
}

//Check if a certain key was pressed during the current frame
bool Input::wasKeyPressed(SDL_Scancode key) 
{
	return this->pressedKeys[key];
}

//Check if a certain key was released during the current frame
bool Input::wasKeyReleased(SDL_Scancode key) 
{
	return this->releasedKeys[key];
}

//Check if a certain key is currently being held
bool Input::isKeyHeld(SDL_Scancode key) 
{
	return this->heldKeys[key];
}