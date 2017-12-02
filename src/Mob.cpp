#include "Mob.hpp"

Mob::Mob(sf::Color color, float hp, float dmg, sf::Vector2f pos, int speed) : DynamicActor(color, hp, dmg, pos, speed) {
    m_type = Actor::Mob;
    m_rect.setFillColor(color);
    m_rect.setSize(sf::Vector2f(32,32));
    m_rect.setPosition(pos);
}

void Mob::attack(DynamicActor &target) {
    float health = target.getHealth();
    health -= getDamage();
    target.setHealth(health);
}
