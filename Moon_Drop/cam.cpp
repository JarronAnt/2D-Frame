#include <cam.h>

//init the camera outside of class because it is static (static vars r weird )
SDL_Rect cam::camera = {0,0,globals::SCREEN_WIDTH ,globals::SCREEN_HEIGHT};
cam::cam() {

}

cam::~cam() {

}

void cam::update(float elapsedTime, Player player, Level _lvl) {

	//update the cameras x and y based on the player position 
	//formula: (player x||ypos + player width||height / 2 ) - screen width||screenheight /2
	camera.x = ( player._x +(64 / 2 ) - globals::SCREEN_WIDTH / 2);
    camera.y = ( player._y +(64 / 2 ) - globals::SCREEN_HEIGHT / 2);


    //Keep the camera in bounds.
    if( camera.x < 0 )
    {
        camera.x = 0;    
    }
    if( camera.y < 0 )
    {
        camera.y = 0;    
    }
    if( camera.x > (_lvl._size.x*globals::SPRITE_SCALE - camera.w ) )
    {
        camera.x = _lvl._size.x*globals::SPRITE_SCALE - camera.w ;    
    }
    if( camera.y > _lvl._size.y*globals::SPRITE_SCALE - camera.h  )
    {
        camera.y = _lvl._size.y*globals::SPRITE_SCALE - camera.h ;    
    }  
}

int cam::getX() {
	//return camera x pos
	return camera.x;
}

int cam::getY() {
	//return camera y pos 
	return camera.y;
}
