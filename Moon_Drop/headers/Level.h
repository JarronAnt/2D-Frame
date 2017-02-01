#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <globals.h>
#include <tile.h>
#include <vector>
#include <Rectangle.h>

class graphics;
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;

class Level
{
public:
  Level();
  Level(std::string mapName,Vector2 spawnPoint,Graphics &graphics);
  ~Level();
  Vector2 getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight);
  void update(float elapsedTime);
  void draw(Graphics &graphics);

  std::vector<Rectangle> checkTileCollisions(const Rectangle &other);

 const Vector2 getPlayerSpawnPoint() const;

  Vector2 _size;

  
private:
  std::string _mapName;
  Vector2 _spawnPoint;
  Vector2 _tileSize;

  SDL_Texture* _background;

  std::vector<tile> _tileList;
  std::vector<Tileset> _tilesets;
  std::vector<Rectangle> _collisionRects;

  

  void loadMap(std::string mapName,Graphics &graphics);
};

struct Tileset {
  //tileset image
  SDL_Texture *tex;
  //the starting tile 
  int firstGid;

  Tileset() {
    this->firstGid = -1;
  }
  
  Tileset(SDL_Texture *texture, int FirstGid) {
    this->tex = texture;
    this->firstGid = FirstGid;
  }

};

#endif
