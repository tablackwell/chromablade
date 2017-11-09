/*
 * Implementation of DynamicActor class.
 */

#include "DynamicActor.hpp"


DynamicActor::DynamicActor() {

}


DynamicActor::DynamicActor(Color color, float health, float damage, std::tuple<int, int> startPos, sf::Texture texture, int speed) {
    this->activeColor = color;
    this->health = health;
    this->damage = damage;
    this->position = startPos;
    this->texture = texture;
    this->speed = speed;
}

/* Change color. */
void DynamicActor::changeColor(Color color) {
    this->activeColor = color;
}

/* Return current health of actor. */
float DynamicActor::getHealth() {
    return health;
}

void DynamicActor::attack() {
    
}
