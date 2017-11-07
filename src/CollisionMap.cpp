#include "CollisionMap.hpp"
#include <iostream>
#include <string>
#include <fstream>


bool CollisionMap::loadFromText(std::string fileName, sf::Vector2u tileSize, unsigned int width, unsigned int height){
  std::ifstream inputFile;
  inputFile.open(fileName, std::ifstream::in);

  this->width = width;
  this->height = height;
  // The following is one of the dumbest things I've ever written. Beware.
  std::vector<int>numbers;

  int number;
  while(inputFile >> number){ //until document ends
     if(inputFile.peek() == ','){ // skip commas
       inputFile.ignore();
     }
     numbers.push_back(number); //add the number
  }

  // for(int x = 0; x < height; x++){
  //   collisionMap.push_back(std::vector <int>());
  //   for(int y = 0; y < width; y++){
  //     collisionMap[x].push_back(numbers[x + y]);
  //   }
  // }

}

bool CollisionMap::checkCollision(int actorX, int actorY){

}
