#include "CollisionMap.hpp"
#include <iostream>
#include <string>
#include <fstream>


bool CollisionMap::loadFromText(std::string fileName, sf::Vector2u tileSize, unsigned int width, unsigned int height){
  std::ifstream inputFile;
  inputFile.open(fileName, std::ifstream::in);
}

bool CollisionMap::checkCollision(int actorX, int actorY){

}
