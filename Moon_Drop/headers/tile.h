#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include <globals.h>
#include <graphics.h>



struct SDL_Texture;
class graphics; 

class tile
{
public:
	tile();
	tile(SDL_Texture *tileset,Vector2 tileSize,Vector2 tileSetPos,Vector2 pos);

	void update(float timeElapsed);
	void draw(Graphics &g);
private:
	SDL_Texture *_tileset;
	Vector2 _tileSize; 
	Vector2 _tileSetPos; 
	Vector2 _pos;
};

#endif