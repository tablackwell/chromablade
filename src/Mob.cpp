#include "Mob.hpp"

Mob::Mob(sf::Color color, float hp, float dmg, sf::Vector2f pos, int speed) : DynamicActor(color, hp, dmg, pos, speed) {
    m_type = Actor::Mob;
}

void Mob::attack(DynamicActor &target) {
    float health = target.getHealth();
    health -= getDamage();
    target.setHealth(health);
}
