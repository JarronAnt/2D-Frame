#ifndef GLOBALS_H
#define GLOBALS_H
#include <SDL2/SDL.h>


 

namespace globals
{
  //screen width and heights constants
  const int SCREEN_WIDTH   = 1280;
  const int SCREEN_HEIGHT  = 720;

  //sprite size multiplier
  const float SPRITE_SCALE = 1.75f;

}

namespace sides {

  enum Side {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    NONE
  };

  inline Side getOtherSide(Side side) {
    return
          side==TOP ? BOTTOM:
          side==BOTTOM ? TOP:
          side==LEFT ? RIGHT:
          side==RIGHT ? LEFT:
          NONE;
  }
}


enum direction
{
  LEFT,
  RIGHT,
  UP,
  DOWN
};



//a 2d vectors (holds x and y components)
struct Vector2
{
  int x,y;
  Vector2():x(0),y(0){}

  Vector2(int x, int y):x(x),y(y){}

  Vector2 zero()
  {
    return Vector2(0,0);
  }

};

#endif
