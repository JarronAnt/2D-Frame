#include <Level.h>
#include <graphics.h>
#include <SDL2/SDL.h>

Level::Level()
{}

Level::Level(std::string mapName,Vector2 spawnPoint,Graphics &graphics):
_mapName(mapName),
_spawnPoint(spawnPoint),
_size(Vector2(0,0))
{
  this->loadMap(mapName, graphics);
}

Level::~Level()
{}

void Level::loadMap(std::string mapName, Graphics &graphics)
{
  //temp code for background
  //will be replaced with map parsing code eventually

  this->_background = SDL_CreateTextureFromSurface(graphics.getRenderer(),graphics.loadImage("assets/backgrounds/grassTile.png"));

  this->_size= Vector2(1280,960);

}

void Level::update(float elapsedTime)
{

}

void Level::draw(Graphics &graphics)
{
  SDL_Rect sourceRect = {0,0,32,32 };
  SDL_Rect destRect;
  destRect.w = 32;
  destRect.h = 32;

  for(int x = 0; x < this->_size.x/32 ; x++)
  {
    for(int y = 0; y < this->_size.y/32 ; y++)
    {
      destRect.x = x*32;
      destRect.y = y*32;
      graphics.blitSurface(this->_background, &sourceRect,&destRect);

    }
  }

}
