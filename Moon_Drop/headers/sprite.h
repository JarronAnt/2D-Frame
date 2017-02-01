#ifndef SPRITE_H
#define SPRITE_H

//includes
#include <string>
#include <SDL2/SDL.h>
#include <globals.h>
#include <Rectangle.h>

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

  //position of sprite
  float _x, _y;

  const Rectangle getBoundingBox() const;
  const sides::Side getCollisionSide(Rectangle &other) const;


protected:
  //source rect
  SDL_Rect _sourceRect;
  //sprite sheet for particular sprite
  SDL_Texture* _spriteSheet;

  Rectangle _boundingBox; 
  


private:

};
#endif
