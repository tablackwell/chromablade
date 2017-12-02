#include "Portal.hpp"

Portal::Portal(std::string name, sf::Vector2f rectDim, int posX, int posY){
  sf::RectangleShape m_rectangle(rectDim);
  m_rectangle.setPosition(posX, posY);
  m_name = name;
}

std::string Portal::getName(){
  return m_name;
}

sf::RectangleShape Portal::getRectangle(){
  return m_rectangle;
}
