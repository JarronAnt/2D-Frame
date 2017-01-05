#ifndef GAME_H
#define GAME_H

//inclueds
#include <player.h>
#include <Level.h>
//forward declare graphics class
class Graphics;

//game info handling class
class Game
{
public:
  Game();
  ~Game();
private:
  void gameLoop();
  void draw(Graphics &graphics);
  void update(float timeElapsed);

  Player _player;
  Level _level;

};


#endif
