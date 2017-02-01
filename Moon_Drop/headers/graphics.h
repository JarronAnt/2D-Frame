//header guards
#ifndef GRAPHICS_H
#define GRAPHICS_H

//includs 
#include <SDL2/SDL.h>
#include <map>
#include <string>

/* Graphics class
 * Holds all information dealing with graphics for the game
*/

//includes
struct SDL_Window;
struct SDL_Renderer;

//Graphics class
class Graphics {
public:
	Graphics();
	~Graphics();

//load spritesheet to map
SDL_Surface* loadImage(const std::string &filePath);
//get the renderer
SDL_Renderer* getRenderer() const;

//load image into the renderer
void blitSurface(SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destinationRect);
//render the image
void flip();
//clear the screen
void clear();



private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

  std::map<std::string, SDL_Surface*> _spriteSheets;

};

#endif
