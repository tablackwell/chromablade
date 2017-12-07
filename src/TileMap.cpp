
/*
 Please note: this code is adapted from the SFMl tutorial. It is modified, but
 is mostly just the tutorial so don't treat this as 100% my own code.
 https://www.sfml-dev.org/tutorials/2.4/graphics-vertex-array.php
 - Thomas

Example Usage:
TileMap m_map
m_map.loadFromText("../res/tileset.png", "../res/level/testlevel.txt", sf::Vector2u(32, 32), 16, 8);
m_map.loadFromText("../res/tilesets/lightworld.png","../res/level/testbaselayer.txt",sf::Vector2u(16,16),50,38);
m_map.loadFromText("../res/tilesets/dungeon.png","../res/level/sampledungeon.txt",sf::Vector2u(16,16),50,38);
m_map.load("../res/tileset.png", sf::Vector2u(32, 32), level, 16, 8);

Overlay Example:
m_map.loadFromText("../res/tilesets/lightworld.png","../res/level/demolevel_base.csv", sf::Vector2u(16, 16), 50, 38);
m_overlay.loadFromText("../res/tilesets/lightworld.png","../res/level/demolevel_overlay.csv", sf::Vector2u(16, 16), 50, 38);
render them in their respective order

*/


#include "TileMap.hpp"
#include <iostream>
#include <string>
#include <fstream>

/*
Creates a TileMap object from a .csv file.
Arguments: tileset = tileset texture file (a png)
           textFileName = the .csv file to read from
           tileSize = Vector2u containing dimension of image tiles (ex: 16x16)
           width and height = how many tiles to actually place
*/
bool TileMap::loadFromText(const std::string& tileset, std::string textFileName, sf::Vector2u tileSize, unsigned int width, unsigned int height){
  m_height = height;
  m_width = width;
  std::ifstream inputFile;
  // load the tileset texture
  if (!m_tileset.loadFromFile(tileset)){
    return false;
  }

  // load the csv file
  inputFile.open(textFileName, std::ifstream::in);

  std::vector<int>numbers;
  int number;
  while(inputFile >> number){ //until document ends
     if(inputFile.peek() == ','){ // skip commas
       inputFile.ignore();
     }
     numbers.push_back(number); //add the number
  }

  // Convert int array to vector
  const int *tileArray = &numbers[0];
  inputFile.close();

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // file vertex array with quads for each tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = tileArray[i + j * width];

                // choose the particular tile from the tileset
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }
        fprintf(stderr, "loadFromText!\n");
        return true;
}

/* Returns the height of a particular tilemap*/
int TileMap::getHeight(){
  return m_height;
}

/* Returns the tile width of a particular tilemap*/
int TileMap::getWidth(){
  return m_width;
}


/*
Renders a given tilemap (don't call this if you're using a tilemap to store
collisions or doors)
*/
void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();
        // apply the tileset texture
        states.texture = &m_tileset;
        // draw the vertex array
        target.draw(m_vertices, states);
}

/*
Returns the value associated with a given tile on a tilemap.
Converts integer player coordinates to tile coordinates.
Tiles stored in a linearized 2D array.
*/
int TileMap::checkCollision(int actorX, int actorY){
  int tileX = actorX / 16;
  int tileY = actorY / 16;
  std::cout << "Coords:" << "\n";
  std::cout << tileX << "\n";
  std::cout << tileY << "\n";
  std::cout << "Tile Value:" << "\n";
  int tileVal;
  try{
    tileVal = m_tileNumbers.at(tileX + tileY * m_width);
    std::cout << tileVal << "\n";
  }
  catch(const std::exception& e) {
     std::cout << "Out of bounds!" << "\n";
  }
  return tileVal;
}

/*
Debug method for indicating where collisions should be
by drawing them on the window.
*/
void TileMap::drawBoxes(sf::RenderWindow* target){
  for(int i = 0; i < m_boxes.size(); i++){
    target->draw(m_boxes.at(i));
  }
}

/*
Loads collision mapping from a .csv file

tileset: the location of the tileset image
textFileName: the location of the .csv to parse
tileSize: the size of tiles in terms of pixels (ex: (16,16))
width and height: the width and height of the tilemap to be produced from the csv
*/
bool TileMap::loadCollisionsFromText(const std::string& tileset, std::string textFileName, sf::Vector2u tileSize, unsigned int width, unsigned int height){
  std::ifstream inputFile;
  m_height = height;
  m_width = width;
  // load the tileset texture
  if (!m_tileset.loadFromFile(tileset)){
    return false;
  }

  // load the csv file
  inputFile.open(textFileName, std::ifstream::in);

  int number;
  while(inputFile >> number){ //until document ends
     if(inputFile.peek() == ','){ // skip commas
       inputFile.ignore();
     }
     m_tileNumbers.push_back(number); //add the number
  }

  inputFile.close();

  // This is hacky and I probably dont need to do it
  const int *tileArray = &m_tileNumbers[0];
  inputFile.close();

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // file vertex array with quads for each tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = tileArray[i + j * width];

                if(tileNumber == 1){
                  sf::RectangleShape rect(sf::Vector2f(16,16));
                  rect.setFillColor(sf::Color(150, 50, 250, 125));
                  rect.setPosition(sf::Vector2f(i * tileSize.x, j * tileSize.y));
                  m_boxes.push_back(rect);
                }
            }
        return true;
}

/*
Loads door locations from a .csv file

tileset: the location of the tileset image
textFileName: the location of the .csv to parse
tileSize: the size of tiles in terms of pixels (ex: (16,16))
width and height: the width and height of the tilemap to be produced from the csv
*/
bool TileMap::loadDoorsFromText(const std::string& tileset, std::string textFileName, sf::Vector2u tileSize, unsigned int width, unsigned int height){
    std::ifstream inputFile;
    m_height = height;
    m_width = width;
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset)){
      return false;
    }

    // load the csv file
    inputFile.open(textFileName, std::ifstream::in);

    int number;
    while(inputFile >> number){ //until document ends
       if(inputFile.peek() == ','){ // skip commas
         inputFile.ignore();
       }
       m_tileNumbers.push_back(number); //add the number
    }

    inputFile.close();

    // This is hacky and I probably dont need to do it
    const int *tileArray = &m_tileNumbers[0];
    inputFile.close();

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // file vertex array with quads for each tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tileArray[i + j * width];

            if(tileNumber == 3){
              sf::RectangleShape rect(sf::Vector2f(16,16));
              rect.setFillColor(sf::Color(255, 0, 0, 125));
              rect.setPosition(sf::Vector2f(i * tileSize.x, j * tileSize.y));
              m_boxes.push_back(rect);
            }
        }
    return true;
}

/*
Clears a tilemap so a new one can be generated
*/
void TileMap::clear() {
    m_boxes.clear();
    m_tileNumbers.clear();
    m_vertices.clear();
    m_width = 0;
    m_height = 0;

}

/* Returns a pointer to the tilset*/
sf::Texture* TileMap::getTileSet() {
    return &m_tileset;
}
