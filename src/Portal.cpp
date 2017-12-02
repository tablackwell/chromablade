#include "Portal.hpp"

Portal::Portal(){
}

std::string Portal::getName(){
  return m_name;
}

sf::RectangleShape Portal::getRectangle(){
  return m_rectangle;
}
