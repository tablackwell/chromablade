#ifndef ROOM
#define ROOM

#include <vector>
#include <SFML/Graphics.hpp>

class Room{
public:
  Room(int x, int y);
private:
  int yBounds;
  int xBounds;
  sf::RectangleShape topWall;
  sf::RectangleShape botWall;
  sf::RectangleShape leftWall;
  sf::RectangleShape rightWall;
};
#endif
