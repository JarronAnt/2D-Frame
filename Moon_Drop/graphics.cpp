//includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <graphics.h>
#include <globals.h>
#include <cam.h>


//constructor
Graphics::Graphics()
{
  SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH,globals::SCREEN_HEIGHT,SDL_WINDOW_RESIZABLE, &this->_window,&this->_renderer);
  SDL_SetWindowTitle( this->_window,"Skygrade Chronicles: Genesis- PreAlpha 0.01");

  SDL_RenderSetLogicalSize(this->_renderer,1280,720);


}

//deconstructor
Graphics::~Graphics()
{
  SDL_DestroyWindow(this->_window);
  SDL_DestroyRenderer(this->_renderer);
}


SDL_Surface* Graphics::loadImage(const std::string &filePath)
{
  if(this->_spriteSheets.count(filePath) == 0)
  {
    this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
  }

  return this->_spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destinationRect)
{
  //update the dest rect based on camera
  destinationRect->x -= cam::getX();
  destinationRect->y -= cam::getY();
  //render the surface
  SDL_RenderCopy(this->_renderer,texture,sourceRect,destinationRect);
}

void Graphics::flip()
{
  //flip the buffers nd draw
  SDL_RenderPresent(this->_renderer);
}

void Graphics::clear()
{
  //clear all buffers
  SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const
{
  return this->_renderer;
}
