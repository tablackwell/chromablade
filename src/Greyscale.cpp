#include "Greyscale.hpp"

Greyscale::Greyscale(sf::Color color, float hp, float dmg, sf::Vector2f pos, int speed): DynamicActor(color, hp, dmg, pos, speed) {
    m_type = Actor::Greyscale;
}

void Greyscale::attack(DynamicActor &target) {
    float health = target.getHealth();
    health -= getDamage();
    target.setHealth(health);
}
