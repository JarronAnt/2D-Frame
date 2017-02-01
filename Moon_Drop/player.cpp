#include <player.h>
#include <graphics.h>
#include <game.h>



namespace playerConsts
{
  const float WALK_SPEED = 0.2f;
}

Player::Player()
{}

//init the player sprite and the animated sprites class, setup anim and play idle down
Player::Player(Graphics &graphics,Vector2 spawnPoint):  AnimatedSprites
(graphics, "assets/player sprites/actor_10.png",0,0,32,32,spawnPoint.x,spawnPoint.y,100),_dy(0),_dx(0),_facing(DOWN)
{

  graphics.loadImage("assets/player sprites/actor_10.png");
  this->setupAnim();
  this->playAnim("IdleDown");
  COLLIDED = false;
}

//player animations
void Player::setupAnim()
{
  //walk anims
  this->addAnim(3,  0 , 32, "WalkLeft", 32, 32, Vector2(0,0));
  this->addAnim(3,  0 , 64,"WalkRight", 32, 32, Vector2(0,0));
  this->addAnim(3,  0 , 96,"WalkUp", 32, 32, Vector2(0,0));
  this->addAnim(3,  0 , 0, "WalkDown", 32, 32, Vector2(0,0));

  //idle anims
  this->addAnim(1,  0,  0,"IdleDown", 32,32,Vector2(0,0));
  this->addAnim(1,  0, 96,"IdleUp", 32,32,Vector2(0,0));
  this->addAnim(1,  0, 32,"IdleLeft", 32,32,Vector2(0,0));
  this->addAnim(1,  0, 64,"IdleRight", 32,32,Vector2(0,0));
}

//player movements
void Player::moveLeft()
{
  //stop vert movement
  this->_dy = 0;
  //move based on a const speed factor 
  this->_dx = -playerConsts::WALK_SPEED;
  //play an anim
  this->playAnim("WalkLeft");
  //set the enum to LEFT
  this->_facing = LEFT;
}
void Player::moveRight()
{
  this->_dy = 0;
  this->_dx = playerConsts::WALK_SPEED;
  this->playAnim("WalkRight");
  this->_facing = RIGHT;
}
void Player::moveUp()
{
  this->_dx = 0;
  this->_dy = -playerConsts::WALK_SPEED;
  this->playAnim("WalkUp");
  this->_facing = UP;
}
void Player::moveDown()
{
  this->_dx = 0;
  this->_dy = playerConsts::WALK_SPEED;
  this->playAnim("WalkDown");
  this->_facing = DOWN;
}
//stop the movement
void Player::stopMoving()
{
  //stop all velocity
  this->_dy = 0.0f;
  this->_dx = 0.0f;

  //pick which anim to play based on the enums 
  switch(_facing)
  {
    case LEFT:
      {
        this->playAnim("IdleLeft");
      }break;
    case RIGHT:
      {
        this->playAnim("IdleRight");
      }break;
    case UP:
      {
          this->playAnim("IdleUp");
      }break;
    case DOWN:
      {
        this->playAnim("IdleDown");
      }break;

      default:
      {
        this->playAnim("IdleDown");
      }
    }
}


void Player::handleTileCollisions(std::vector<Rectangle> &others) {
    for (int i = 0 ; i < others.size() ; i++) {
      sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
      if(collisionSide != sides::NONE) {
        switch(collisionSide) {
          case sides::TOP:
              this->_y = others.at(i).getBottom();
              this->_dy = 0;
              COLLIDED = true;
              break;
          case sides::BOTTOM:
              this->_y = others.at(i).getTop() - this->_boundingBox.getHeight();
              this->_dy = 0;
              COLLIDED = true;
              break;
          case sides::LEFT:
              this->_x = others.at(i).getRight() ;
              this->_dx = 0;
              COLLIDED = true;
              break;
          case sides::RIGHT:
              this->_x = others.at(i).getLeft() - this->_boundingBox.getWidth();
              this->_dx = 0;
              COLLIDED = true;
              break;
        }
      }
    }
}


void Player::animDone(std::string currentAnim)
{}

const float Player::getX() const {
  return this->_x;

}

const float Player::getY() const {
  return this->_y;

}
//update nd draw
void Player::update(float elapsedTime)
{
  //set x & yvalue to movespeed 
  this->_x += _dx*elapsedTime;
  this->_y += _dy*elapsedTime;
  AnimatedSprites::update(elapsedTime);


}

void Player::draw(Graphics &graphics)
{
  //call parent draw class
  AnimatedSprites::draw(graphics,this->_x,this->_y);
}

