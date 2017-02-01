#include <Level.h>
#include <graphics.h>
#include <SDL2/SDL.h>
#include <globals.h>


//loading and parsing xml 
#include <tinyxml2.h>
#include <sstream>

//includes for physics stuff
#include <algorithm> 
#include <cmath>

using namespace tinyxml2; 

Level::Level()
{}

Level::Level(std::string mapName,Vector2 spawnPoint,Graphics &graphics):
_mapName(mapName),
_spawnPoint(spawnPoint),
_size(Vector2(0,0))
{
  this->loadMap(mapName, graphics);
}

Level::~Level()
{}


/*
All map loading algorithims and xml parsing courtesy of limeoats 
*/
void Level::loadMap(std::string mapName, Graphics &graphics)
{
  //open up the doc
  //--------------------------------------------------------------------
  XMLDocument doc;
  std::stringstream ss; 
  //stream in the map 
  ss << "assets/maps/" << mapName << ".tmx";
  //load the map to the xml after converting to string then c-string
  doc.LoadFile(ss.str().c_str());
  //--------------------------------------------------------------------
  //parse the map 
  XMLElement* mapNode = doc.FirstChildElement("map"); 

  //store width and height in _size 
  int width, height;
  //from the element map in xml file find the int attrib titled width and height and store it 
  mapNode->QueryIntAttribute("width",&width);
  mapNode->QueryIntAttribute("height",&height);

  //note i may have to multiply by tile size to get camera to work 
  this->_size = Vector2(width*32,height*32);

  //get tile width and height 
    int twidth, theight;
  //from the element map in xml file find the int attrib titled width and height and store it 
  mapNode->QueryIntAttribute("tilewidth",&twidth);
  mapNode->QueryIntAttribute("tileheight",&theight);

  this->_tileSize = Vector2(twidth,theight);


  //load tilesets 
  XMLElement *eTileSet = mapNode->FirstChildElement("tileset");
  //if multiple tile sets load them all
  if(eTileSet != nullptr) {
    while(eTileSet) {
      //temp var
      int fg; 
      //get tile set path from xml file
      const char* source = eTileSet->FirstChildElement("image")->Attribute("source");
      char* path; 
      std::stringstream ss;
      //stream file path
      ss <<  "assets/tilesets/" << source; 
      //get first gid of tileset from xml file and store in fg
      eTileSet->QueryIntAttribute("firstgid", &fg);
      //load the image and create a texutre with it 
      SDL_Texture *text = SDL_CreateTextureFromSurface(graphics.getRenderer(),graphics.loadImage(ss.str()));
      this->_tilesets.push_back(Tileset(text,fg));
      eTileSet = eTileSet->NextSiblingElement("tileset");
    }
  }

  //load layers
  XMLElement *eLayer = mapNode->FirstChildElement("layer");

  if(eLayer != nullptr) {
    while(eLayer) {

      //load data
      XMLElement *eData = eLayer->FirstChildElement("data");
      if(eData != nullptr) {
        while(eData) {

          //load tiles
          XMLElement *eTile = eData->FirstChildElement("tile");
          if(eTile != nullptr) {
            int tileCount = 0;
            while(eTile) {
              //build tile, NOTE: gid = 0 means no tile drawn

              if(eTile->IntAttribute("gid") == 0 ) {
                tileCount++;

                if(eTile->NextSiblingElement("tile")) {
                  eTile = eTile->NextSiblingElement("tile");
                  continue;
                }
                else
                {
                  break;
                }

              }

              //get tile set for this specific tile/gid 


              int gid = eTile->IntAttribute("gid");
              Tileset ts; 
              for (int i = 0; i < this-> _tilesets.size(); i++ ) {
                if(this->_tilesets[i].firstGid <= gid) {
                  //found tile set needed
                  ts = _tilesets.at(i);
                  break; 
                }
              }

              if(ts.firstGid == -1) {
                tileCount++;
                if(eTile->NextSiblingElement("tile")) {
                  eTile = eTile->NextSiblingElement("tile");
                  continue;
                }
                else {
                  break;
                }
              }

              //get pos of tiles in the level
              int pX = 0;
              int pY = 0; 

              pX = tileCount % width;
              pX *= twidth; 
              pY += theight * (tileCount / width);

              Vector2 finalTilePos = Vector2(pX,pY);

              //calc tile in the tile set (FML )
              int tileSetWidth,tileSetHeight;
              SDL_QueryTexture(ts.tex,nullptr,nullptr,&tileSetWidth,&tileSetHeight);
              int tsx = gid % (tileSetWidth / twidth)-1;
              tsx *= twidth;
              int tsy = 0;
              int inc = (gid/(tileSetWidth / twidth));
              tsy = theight * inc;
              Vector2 finalTilesetPos = Vector2(tsx,tsy);

              //add tile to tile list 
              tile myTile(ts.tex,Vector2(twidth,theight),finalTilesetPos,finalTilePos);

              this->_tileList.push_back(myTile);
              tileCount++;

              eTile = eTile->NextSiblingElement("tile");
            }
          }


          eData = eData->NextSiblingElement("data");
        }
      }





      eLayer = eLayer->NextSiblingElement("layer");
    }
  }
  //parse collisions
  XMLElement *eObjectGroup = mapNode->FirstChildElement("objectgroup");
  if(eObjectGroup != nullptr) {
    while(eObjectGroup) {
      const char* name = eObjectGroup->Attribute("name");
      std::stringstream ss;
      ss << name;
      if(ss.str() == "collisions") {
        XMLElement *eObject = eObjectGroup->FirstChildElement("object");
        if(eObject != nullptr) {
          while(eObject) {
            float x,y,w,h;
            x = eObject->FloatAttribute("x");
            y = eObject->FloatAttribute("y");
            w = eObject->FloatAttribute("width");
            h = eObject->FloatAttribute("height");
            this->_collisionRects.push_back(Rectangle(
              std::floor(x) * globals::SPRITE_SCALE,
              std::floor(y) * globals::SPRITE_SCALE,
              std::floor(w) * globals::SPRITE_SCALE,
              std::floor(h) * globals::SPRITE_SCALE));


            eObject = eObject->NextSiblingElement("object");
          }
        }

      }
      //rest of object groups go here
      else if(ss.str() == "spawn points") {
        XMLElement *eObject = eObjectGroup->FirstChildElement("object");
        if(eObject != nullptr){
          while(eObject) {
            float x = eObject->FloatAttribute("x");
            float y = eObject->FloatAttribute("y");
            const char* name = eObject->Attribute("name");
            std::stringstream ss;
            ss << name;
            if(ss.str() == "player") {
              this->_spawnPoint = Vector2(std::ceil(x)*globals::SPRITE_SCALE, std::ceil(y)*globals::SPRITE_SCALE);
            }

            eObject = eObject->NextSiblingElement("object");
          }
        }
      }
      //rest go here





      eObjectGroup = eObjectGroup->NextSiblingElement("objectgroup");
    }
  }

}

void Level::update(float elapsedTime)
{

}

void Level::draw(Graphics &graphics)
{
  for(int i = 0 ; i < this->_tileList.size(); i++ ) {
    this->_tileList.at(i).draw(graphics);
  }

}

//function to check the tile collisions 
std::vector<Rectangle> Level::checkTileCollisions(const Rectangle &other){
  std::vector<Rectangle> others;

  for(int i = 0; i < _collisionRects.size(); i++){
    if(_collisionRects.at(i).collidesWith(other)){
      others.push_back(_collisionRects.at(i));
    }
  }

  return others;
}

const Vector2 Level::getPlayerSpawnPoint() const {
  return this->_spawnPoint; 
}