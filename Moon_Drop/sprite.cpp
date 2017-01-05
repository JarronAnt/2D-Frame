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

}

Sprite::~Sprite(){}

//draw the rect
void Sprite::draw(Graphics &graphics, int x ,int y)
{
  SDL_Rect destRect = { x, y, this->_sourceRect.w* globals::SPRITE_SCALE,this->_sourceRect.h * globals::SPRITE_SCALE };
  graphics.blitSurface(this->_spriteSheet,&this->_sourceRect, &destRect);
}

void Sprite::update(){}
