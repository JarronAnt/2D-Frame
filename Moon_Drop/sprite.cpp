//includes
#include <sprite.h>
#include <graphics.h>
#include <stdio.h>
#include <globals.h>

Sprite::Sprite()
{}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX,
  int sourceY, int width, int height, float posX, float posY) :_x(posX),_y(posY)
{
  //get the source rect
  this->_sourceRect.x = sourceX;
  this->_sourceRect.y = sourceY;
  this->_sourceRect.w = width;
  this->_sourceRect.h = height;

//create the sprite sheet
  this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));

//check if spritesheet was loaded
  if(this->_spriteSheet == NULL)
  {
    printf("\n ERROR: Unable To Load image...bitch\n" );
  }

  this->_boundingBox = Rectangle(this->_x, this->_y, width * globals::SPRITE_SCALE, height * globals::SPRITE_SCALE);
}

Sprite::~Sprite(){}

//draw the rect
void Sprite::draw(Graphics &graphics, int x ,int y)
{
  SDL_Rect destRect = { x, y, this->_sourceRect.w* globals::SPRITE_SCALE,this->_sourceRect.h * globals::SPRITE_SCALE };
  graphics.blitSurface(this->_spriteSheet,&this->_sourceRect, &destRect);
}

void Sprite::update(){
  this->_boundingBox = Rectangle(this->_x,this->_y,this->_sourceRect.w * globals::SPRITE_SCALE, this->_sourceRect.h * globals::SPRITE_SCALE);
}

const Rectangle Sprite::getBoundingBox() const {
  return this->_boundingBox; 
}


const sides::Side Sprite::getCollisionSide(Rectangle &other) const {
  int amtR,amtL,amtT,amtB;

  amtR = this->getBoundingBox().getRight() - other.getLeft();
  amtL = other.getRight() - this->getBoundingBox().getLeft();
  amtT = other.getBottom() - this->getBoundingBox().getTop();
  amtB = this->getBoundingBox().getBottom() - other.getTop();

  int vals[4] = { abs(amtR), abs(amtL), abs(amtT), abs(amtB)};
  int lowest = vals[0];

  for (int i = 0 ; i < 4 ; i++) {
    if(vals[i] < lowest) {
      lowest = vals[i];
    }
  }

  return  
        lowest == abs(amtR) ? sides::RIGHT:
        lowest == abs(amtL) ? sides::LEFT:
        lowest == abs(amtT) ? sides::TOP:
        lowest == abs(amtB) ? sides::BOTTOM:
        sides::NONE;
}