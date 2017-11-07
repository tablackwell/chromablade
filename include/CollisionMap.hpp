
#ifndef COLLISIONMAP
#define COLLISIONMAP

/*
 This is not entirely my original code! This is adapted from:
 https://www.sfml-dev.org/tutorials/2.4/graphics-vertex-array.php
 - Thomas

 See TileMap.cpp for more details.
*/

#include <SFML/Graphics.hpp>
class CollisionMap{
public:
    bool loadFromText(std::string fileName, sf::Vector2u tileSize, unsigned int width, unsigned int height);
    bool checkCollision(int actorX, int actorY);
private:
    std::vector<std::vector<int>>collisionMap;
    int width;
    int height;
};

#endif
