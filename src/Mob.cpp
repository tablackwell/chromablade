#include "Mob.hpp"

Mob::Mob(sf::Color color, float hp, float dmg, sf::Vector2f pos, int speed)
    : DynamicActor(color, hp, dmg, pos, speed) {}

void Mob::attack(DynamicActor target) {}
