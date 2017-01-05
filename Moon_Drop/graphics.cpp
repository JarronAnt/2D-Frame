//includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <graphics.h>
#include <globals.h>


//constructor
Graphics::Graphics()
{
  SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH,globals::SCREEN_HEIGHT,SDL_WINDOW_RESIZABLE, &this->_window,&this->_renderer);
  SDL_SetWindowTitle( this->_window,"Dreams: A New Dawn");
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
  SDL_RenderCopy(this->_renderer,texture,sourceRect,destinationRect);
}

void Graphics::flip()
{
  SDL_RenderPresent(this->_renderer);
}

void Graphics::clear()
{
  SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const
{
  return this->_renderer;
}
