#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <animatedSprites.h>
#include <globals.h>
#include <Level.h>

class Graphics;
class Sprite;

class Player : public AnimatedSprites
{
public:
Player();
Player(Graphics &graphics,Vector2 spawnPoint);
void draw(Graphics &graphics);
void update(float elapsedTime);

virtual void animDone(std::string currentAnim);

virtual void setupAnim();

const float getX() const;
const float getY() const;

void handleTileCollisions(std::vector<Rectangle> &others);

void moveLeft();
void moveRight();
void moveUp();
void moveDown();
void stopMoving();

bool COLLIDED;

private:
  float _dx, _dy;

  direction _facing;


};


#endif
