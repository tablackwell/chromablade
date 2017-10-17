/*
 * Implementation of DynamicActor class.
 */

#include "DynamicActor.hpp"

DynamicActor::DynamicActor() {
}

DynamicActor::DynamicActor(AvailableColors color, float health, float damage, std::tuple<int, int> startPos, sf::Texture sprite, int speed) {
    this -> activeColor = color;
    this -> health = health;
    this -> damage = damage;
    this -> position = startPos;
    this -> sprite = sprite;
    this -> speed = speed;
}

/* Change color. */
void DynamicActor::changeColor(AvailableColors color) {
    this -> activeColor = color;
}

/* Return current health of actor. */
float DynamicActor::checkHealth() {
    return health;
}
