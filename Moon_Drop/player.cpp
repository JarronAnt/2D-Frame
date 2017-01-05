#include <player.h>
#include <graphics.h>

namespace playerConsts
{
  const float WALK_SPEED = 0.2f;
}

Player::Player()
{}

//init the player sprite and the animated sprites class, setup anim and play idle down
Player::Player(Graphics &graphics,float x, float y):  AnimatedSprites
(graphics, "assets/player sprites/actor_10.png",0,32,32,32,x,y,100)
{
  graphics.loadImage("assets/player sprites/actor_10.png");
  this->setupAnim();
  this->playAnim("IdleDown");
}

//player animations
void Player::setupAnim()
{
  //walk anims
  this->addAnim(3,  0 , 32, "WalkLeft", 32, 32, Vector2(0,0));
  this->addAnim(3,  0 , 64, "WalkRight", 32, 32, Vector2(0,0));
  this->addAnim(3,  0 , 96, "WalkUp", 32, 32, Vector2(0,0));
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
  this->_dy = 0;
  this->_dx = -playerConsts::WALK_SPEED;
  this->playAnim("WalkLeft");
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
  this->_dy =0.0f;
  this->_dx =0.0f;

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


void Player::animDone(std::string currentAnim)
{}

//update nd draw
void Player::update(float elapsedTime)
{
  //set x value to movespeed 
  this->_x += _dx*elapsedTime;
  this->_y += _dy*elapsedTime;
  AnimatedSprites::update(elapsedTime);
}

void Player::draw(Graphics &graphics)
{
  AnimatedSprites::draw(graphics,this->_x,this->_y);
}
