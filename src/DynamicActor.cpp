/*
 * Implementation of DynamicActor class.
 */

#include "DynamicActor.hpp"
#include <iostream>
#include <tuple>


DynamicActor::DynamicActor() {

}


DynamicActor::DynamicActor(Color color, float health, float damage, std::tuple<float, float> startPos, sf::Texture texture, int speed) {
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

void DynamicActor::setPosition(std::tuple<float, float> position) {
    this->position = position;
}
