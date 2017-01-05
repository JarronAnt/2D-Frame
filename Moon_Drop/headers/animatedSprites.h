#ifndef ANIMATED_SPRITES_H
#define ANIMATED_SPRITES_H

#include <sprite.h>
#include <string>
#include <map>
#include <globals.h>
#include <vector>

class Graphics;


class AnimatedSprites: public Sprite
{
public:
AnimatedSprites();
AnimatedSprites(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
float posX,float posY, float timeToUpdate);

//play the animation
void playAnim(std::string animation, bool once = false);

void update(float elapsedTime);

void draw(Graphics &graphics, int x, int y);

//setup all the animations in the map


protected:
  double _timeToUpdate;
  bool _currentAnimationOnce;
  std::string  _currentAnimation;

//add anim to map
  void addAnim(int frames, int x ,int y, std::string name, int width , int height, Vector2 offset);
  //clear map of anims
  void resetAnim();

  void stopAnim() ;

  void setVisible(bool visible);

  virtual void animDone(std::string currentAnim) =0;

  virtual void setupAnim()=0;

private:
  //map of anims
  std::map<std::string,std::vector<SDL_Rect> >_animations;
  //map of offsets
  std::map<std::string,Vector2 >_offsets;

int _frameIndex;
double _timeElapsed;
bool _visible;

};

#endif
