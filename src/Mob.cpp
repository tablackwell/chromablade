#include "Mob.hpp"

Mob::Mob(Color color, float hp, float dmg, sf::Vector2f pos, int speed)
    : DynamicActor(color, hp, dmg, pos, speed) {

    m_type = Type::Mob;
}

void Mob::atack(DynamicActor target) {

}
