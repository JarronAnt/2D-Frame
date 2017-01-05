#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<animatedSprites.h>
#include <globals.h>

class Graphics;

class Player : public AnimatedSprites
{
public:
Player();
Player(Graphics &graphics,float x, float y);
void draw(Graphics &graphics);
void update(float elapsedTime);

virtual void animDone(std::string currentAnim);

virtual void setupAnim();

void moveLeft();
void moveRight();
void moveUp();
void moveDown();
void stopMoving();

private:
  float _dx, _dy;

  direction _facing;


};


#endif
