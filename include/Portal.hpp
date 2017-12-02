#ifndef PORTAL
#define PORTAL

#include <vector>
#include <string>
#include "Actor.hpp"
#include <SFML/Graphics.hpp>

class Portal : public Actor {
  public:
    Portal();
    sf::RectangleShape getRectangle();
    std::string getName();
  private:
    std::string m_name = "undefined portal";
    sf::RectangleShape m_rectangle;
};
#endif
