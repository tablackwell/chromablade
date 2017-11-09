#include "Room.hpp"
#include <SFML/Graphics.hpp>

Room::Room(int x, int y){
  m_xBounds = x;
  m_yBounds = y;

  m_topWall.setSize(sf::Vector2f(800,32));
  m_botWall.setSize(sf::Vector2f(800,32));
  m_leftWall.setSize(sf::Vector2f(32,600));
  m_rightWall.setSize(sf::Vector2f(32,600));
  m_topWall.setPosition(0,0);
  m_botWall.setPosition(0,568);
  m_leftWall.setPosition(0,0);
  m_rightWall.setPosition(768,0);
}
