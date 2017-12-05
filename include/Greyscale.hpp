#ifndef GREYSCALE_HPP
#define GREYSCALE_HPP

#include "DynamicActor.hpp"

class Greyscale : public DynamicActor {


public:
  Greyscale(sf::Color color, float hp, float dmg, sf::Vector2f pos, int speed);
  void attack(DynamicActor &target);
private:
  sf::Color m_activeColor;
  float m_health;
  float m_damage; // Attack damage
  sf::Vector2f m_position;
  int m_speed;


};
#endif
