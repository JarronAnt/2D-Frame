//includes
#include <SDL2/SDL.h>
#include <game.h>
#include <graphics.h>
#include <input.h>
#include <algorithm>


//SDL_Rect camera = { 0, 0, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT };


//namespace to hold fps lock stuff
namespace
{
  const int FPS = 60;
  const int MAX_FRAME_TIME = 1000 / FPS;
}

//constructor
Game::Game()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  this->gameLoop();
}

//destructor
Game::~Game()
{

}

//gameloop
void Game::gameLoop()
{
  //create objects
  Graphics graphics;
  Input input;
  SDL_Event event;
  this->_level = Level("test" , Vector2(100,100), graphics);
  this->_player = Player(graphics,this->_level.getPlayerSpawnPoint());
  
  //this->_player.setupAnim();
//  this->_player.playAnim("WalkLeft");

//get last update time
int LAST_UPDATE_TIME = SDL_GetTicks();
//start loop
  while(true)
  {
    //clear inputs
    input.beginNewFrame();

    //poll the events
    if(SDL_PollEvent(&event))
    {
        if(event.type==SDL_KEYDOWN)
        {
          if(event.key.repeat == 0)
          {
            input.keyDownEvent(event);
          }
        }
        else if(event.type==SDL_KEYUP)
        {
          if(event.key.repeat == 0)
          {
            input.keyUpEvent(event);
          }
        }
        else if(event.type == SDL_QUIT)
        {
          return;
        }
        //mouse events when pressed
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
          if(event.button.button == SDL_BUTTON_LEFT)
          {
            return;
          }
        }
        //mouse events when mouse wheel not pressed
        else if(event.type == SDL_MOUSEWHEEL)
        {
         if(event.wheel.y > 0)
          {
            //TODO: scroll thorugh items

            //reset the wheel to 0
            event.wheel.y = 0;

          }
          else if(event.wheel.y < 0 )
          {
            //TODO: scroll thorugh items in other direction

            //reset the wheel to 0
            event.wheel.y = 0;
          }
        }

    }

      //this is where the actions taken after key presses occur
      //if escape is pressed  leave the game loop (end game)
      if(input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true)
      {return;}

      
      else if(input.isKeyHeld(SDL_SCANCODE_W) == true)
      {
        this->_player.moveUp();
      }
      else if(input.isKeyHeld(SDL_SCANCODE_A) == true)
      {
        this->_player.moveLeft();
      }
      else if(input.isKeyHeld(SDL_SCANCODE_S) == true)
      {
        this->_player.moveDown();
      }
      else if(input.isKeyHeld(SDL_SCANCODE_D) == true)
      {
        this->_player.moveRight();
      }
      else if(!input.isKeyHeld(SDL_SCANCODE_W) && !input.isKeyHeld(SDL_SCANCODE_A) && !input.isKeyHeld(SDL_SCANCODE_S) && !input.isKeyHeld(SDL_SCANCODE_D))
      {
        this->_player.stopMoving();
      }



      //fps limit & anim timing stuff
      const int CURRENT_TIME_MS = SDL_GetTicks();
      int ELASPED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
      if(MAX_FRAME_TIME > ELASPED_TIME_MS)
      {
        SDL_Delay(MAX_FRAME_TIME-(SDL_GetTicks()-LAST_UPDATE_TIME));
      }
      this->update(ELASPED_TIME_MS);

      LAST_UPDATE_TIME = CURRENT_TIME_MS;

      this->draw(graphics);

      
  }

}

//draw stuff
void Game::draw(Graphics &graphics)
{
  //clear screen
  graphics.clear();
  //draw the stuff 
  this->_level.draw(graphics);
  this->_player.draw(graphics);
  //render the stuff 
  graphics.flip();
}

//update stuff
void Game::update(float timeElapsed)
{
  this->_level.update(timeElapsed);
  this->_player.update(timeElapsed);

  //keep collision above camera else 
  //the "vibrating screen" bug occurs 
  std::vector<Rectangle> others;
  if((others = this->_level.checkTileCollisions(this->_player.getBoundingBox())).size() > 0) {
    this->_player.handleTileCollisions(others);
  }
 
  cam::update(timeElapsed,_player, _level);


}
