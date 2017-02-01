#include <tile.h>

tile::tile() {

}

tile::tile(SDL_Texture *tileset,Vector2 tileSize,Vector2 tileSetPos,Vector2 pos):
_tileset(tileset),_tileSize(tileSize),_tileSetPos(tileSetPos),
_pos(Vector2(pos.x * globals::SPRITE_SCALE, pos.y * globals::SPRITE_SCALE)) {

}

void tile::update(float timeElapsed) {

}

void tile::draw(Graphics &g) {
	//dest rect is the place we want to draw the tile 
	SDL_Rect destRect = {this->_pos.x,this->_pos.y, this->_tileSize.x * globals::SPRITE_SCALE, this->_tileSize.y * globals::SPRITE_SCALE};
	
	//source rect is where on the tile set we are getting a particular tile
	SDL_Rect sourceRect; 

  	sourceRect.x = _tileSetPos.x;
  	sourceRect.y = _tileSetPos.y;
  	sourceRect.w = _tileSize.x;
  	sourceRect.h = _tileSize.y;

  	//take in tile set as texture extract a tile based on source rect
  	//place on dest rect
  	g.blitSurface(this->_tileset,&sourceRect,&destRect);
}