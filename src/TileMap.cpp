
/*
 At the moment this is not entirely my original code! This is adapted from:
 https://www.sfml-dev.org/tutorials/2.4/graphics-vertex-array.php
 - Thomas

Example Usage:
TileMap m_map
m_map.loadFromText("../res/tileset.png", "../res/level/testlevel.txt", sf::Vector2u(32, 32), 16, 8);
m_map.loadFromText("../res/tilesets/lightworld.png","../res/level/testbaselayer.txt",sf::Vector2u(16,16),50,38);
m_map.loadFromText("../res/tilesets/dungeon.png","../res/level/sampledungeon.txt",sf::Vector2u(16,16),50,38);
m_map.load("../res/tileset.png", sf::Vector2u(32, 32), level, 16, 8);

Overlay Example:
m_map.loadFromText("../res/tilesets/lightworld.png","../res/level/base.txt", sf::Vector2u(16, 16), 50, 38);
m_overlay.loadFromText("../res/tilesets/lightworld.png","../res/level/overlay.txt", sf::Vector2u(16, 16), 50, 38);
render them in their respective order

*/


#include "TileMap.hpp"
#include <iostream>
#include <string>
#include <fstream>

bool TileMap::loadFromText(const std::string& tileset, std::string fileName, sf::Vector2u tileSize, unsigned int width, unsigned int height){
  std::ifstream inputFile;
  inputFile.open(fileName, std::ifstream::in);
  std::vector<int>numbers;
  int number;
  while(inputFile >> number){
    numbers.push_back(number);
  }

  const int *newArray = &numbers[0];
  inputFile.close();

  load(tileset,tileSize,newArray,width,height);
  return true;
}


bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[i + j * width];

                // find its position in the tileset texture
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

        return true;
    }

void TileMap::init(){
  sf::VertexArray m_vertices;
  sf::Texture m_tileset;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }
