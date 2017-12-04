#ifndef MOB_HPP
#define MOB_HPP

#include "DynamicActor.hpp"

class Mob : public DynamicActor {


public:
    Mob(sf::Color color, float hp, float dmg, sf::Vector2f pos, int speed);
    void attack(DynamicActor &target);
};

#endif
