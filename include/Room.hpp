#ifndef ROOM
#define ROOM

#include <vector>
#include <SFML/Graphics.hpp>

class Room{
public:
  Room(int x, int y);
private:
  int m_yBounds;
  int m_xBounds;
  sf::RectangleShape m_topWall;
  sf::RectangleShape m_botWall;
  sf::RectangleShape m_leftWall;
  sf::RectangleShape m_rightWall;
};
#endif
