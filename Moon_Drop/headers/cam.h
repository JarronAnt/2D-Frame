#ifndef CAM_H
#define CAM_H

#include <SDL2/SDL.h>
#include <player.h>
#include <globals.h>
#include <Level.h>

class cam
{
public:
	cam();
	~cam();
	static SDL_Rect camera; 
	static void update(float elapsedTime,Player player,Level _lvl);
	static int getX();
	static int getY();
	
};

#endif