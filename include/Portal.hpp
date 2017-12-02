#ifndef PORTAL
#define PORTAL

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Portal{
public:
  Portal(std::string name, sf::Vector2f rectDim, int posX, int posY);
  sf::RectangleShape getRectangle();
  std::string getName();
private:
  std::string m_name = "undefined portal";
  sf::RectangleShape m_rectangle;
};
#endif
