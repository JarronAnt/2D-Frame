#ifndef GLOBALS_H
#define GLOBALS_H


namespace globals
{
  //screen width and heights constants
  const int SCREEN_WIDTH   = 640;
  const int SCREEN_HEIGHT  = 480;

  //sprite size multiplier
  const float SPRITE_SCALE = 1.5f;
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
