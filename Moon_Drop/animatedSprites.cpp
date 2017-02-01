#include <animatedSprites.h>
#include <graphics.h>
#include <sprite.h>

AnimatedSprites::AnimatedSprites(){}

//init list of sprite and init the Sprite parent class
AnimatedSprites::AnimatedSprites(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
float posX,float posY, float timeToUpdate):
Sprite(graphics,filePath,sourceX,sourceY,width,height,posX,posY),
_frameIndex(0),
_timeToUpdate(timeToUpdate),
_visible(true),
_currentAnimationOnce(false),
_currentAnimation("")
{}

//add anim to the map of anims
void AnimatedSprites::addAnim(int frames, int x ,int y, std::string name, int width , int height, Vector2 offset)
{
  //create a rect for each animation
  std::vector<SDL_Rect> rects;

  //loopthorugh the frames of the animation and add to the vector
  for(int i =0 ; i < frames ; i++)
  {
    SDL_Rect newRect = { (i+x)*width,y,width,height };
    rects.push_back(newRect);
  }
  //add the animation vector to a map 
  this->_animations.insert(std::pair<std::string,std::vector<SDL_Rect> > (name,rects));
  this->_offsets.insert(std::pair<std::string, Vector2> (name, offset));

}

void AnimatedSprites::resetAnim()
{
  //clear all anims and offsets
  this->_animations.clear();
  this->_offsets.clear();
}


void AnimatedSprites::playAnim(std::string animation, bool once)
{
  //check if the animation played
  this->_currentAnimationOnce = once;
  //set the current anim to the one the frame is on
  if(this->_currentAnimation != animation)
  {
    this->_currentAnimation = animation;
    this->_frameIndex = 0;
  }
}

//change animation visiblity
void AnimatedSprites::setVisible(bool visible)
{
  this->_visible = visible;
}

//stop the animation
void AnimatedSprites::stopAnim()
{
  this->_frameIndex = 0;
  animDone(this->_currentAnimation);
}

//update the animated sprites
void AnimatedSprites::update(float elapsedTime)
{
  Sprite::update();


  this->_timeElapsed += elapsedTime;
  if(_timeElapsed > _timeToUpdate)
  {
    this->_timeElapsed -= this->_timeToUpdate;
    //if frame index samller then all frames of the anim increment
    if(this->_frameIndex < this->_animations[this->_currentAnimation].size() -1)
    {
      this->_frameIndex++;
    }
    else
    {
      if(this->_currentAnimationOnce == true)
      {
        this->_visible= false;
      }
      this->stopAnim();
    }
  }
}

//draw the sprite
void AnimatedSprites::draw(Graphics &graphics, int x, int y)
{
  //create an sdl rect of a particular anim frame and draw it 
  if(_visible)
  {
    SDL_Rect destRect;
    destRect.x = x + _offsets[this->_currentAnimation].x;
    destRect.y = y + _offsets[this->_currentAnimation].y;
    destRect.w = _sourceRect.w * globals::SPRITE_SCALE;
    destRect.h = _sourceRect.h * globals::SPRITE_SCALE;

    SDL_Rect sourceRect= this->_animations[this->_currentAnimation][this->_frameIndex];
    graphics.blitSurface(this->_spriteSheet,&sourceRect, &destRect);

  }
}

/*
void AnimatedSprites::setupAnim()
{
  this->addAnim(3,  0 , 32, "WalkLeft", 32, 32, Vector2(0,0));
  this->addAnim(3,  0 , 64, "WalkRight", 32, 32, Vector2(0,0));
  this->addAnim(3,  0 , 32, "WalkUp", 32, 32, Vector2(0,0));
  this->addAnim(3,  0 , 96, "WalkDown", 32, 32, Vector2(0,0));
}
*/
