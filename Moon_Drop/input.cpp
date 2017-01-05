//includes 
#include <input.h>


//clear all key press at new frame start
void Input::beginNewFrame()
{
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
}

//record when a key was pressed
void Input::keyDownEvent(const SDL_Event& event)
{
	this->_pressedKeys[event.key.keysym.scancode] = true;
	this->_heldKeys[event.key.keysym.scancode] = true;
}

//record when key was released
void Input::keyUpEvent(const SDL_Event& event)
{
	this->_releasedKeys[event.key.keysym.scancode] = true;
	this->_heldKeys[event.key.keysym.scancode] = false;
}

//check if certain key was pressed
bool Input::wasKeyPressed(SDL_Scancode key)
{
	return this->_pressedKeys[key];
}

//check if certain key was let go
bool Input::wasKeyReleased(SDL_Scancode key)
{
	return this->_releasedKeys[key];
}

//check if certain key is held
bool Input::isKeyHeld(SDL_Scancode key)
{
	return this->_heldKeys[key];
}
