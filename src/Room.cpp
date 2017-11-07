#include "Room.hpp"
#include <SFML/Graphics.hpp>

Room::Room(int x, int y){
  xBounds = x;
  yBounds = y;

  sf::RectangleShape topWall(sf::Vector2f(800,32));
  sf::RectangleShape botWall(sf::Vector2f(800,32));
  sf::RectangleShape leftWall(sf::Vector2f(32,600));
  sf::RectangleShape rightWall(sf::Vector2f(32,600));
  topWall.setPosition(0,0);
  botWall.setPosition(0,568);
  leftWall.setPosition(0,0);
  rightWall.setPosition(768,0);
}
