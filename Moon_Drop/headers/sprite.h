#ifndef SPRITE_H
#define SPRITE_H

//includes
#include <string>
#include <SDL2/SDL.h>

class Graphics;

class Sprite
{
public:
  //constructors
  Sprite();
  Sprite(Graphics &graphics, const std::string &filePath,
    int sourceX, int sourceY, int width, int height, float posX, float posY);

  //virtual destructor used when polymorphic class (i.e overridden constructor)
  virtual ~Sprite();
  //overidable update
  virtual void update();
  void draw(Graphics &graphics, int x ,int y);

protected:
  //source rect
  SDL_Rect _sourceRect;
  //sprite sheet for particular sprite
  SDL_Texture* _spriteSheet;
  //position of sprite
  float _x, _y;
private:

};
#endif
