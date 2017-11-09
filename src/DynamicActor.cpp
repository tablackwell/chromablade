/*
 * Implementation of DynamicActor class.
 */

#include "DynamicActor.hpp"
#include <iostream>
#include <tuple>


DynamicActor::DynamicActor() {

}


DynamicActor::DynamicActor(Color color, float health, float damage, std::tuple<float, float> startPos, sf::Texture texture, int speed) {
    this->m_activeColor = color;
    this->m_health = health;
    this->m_damage = damage;
    this->m_position = startPos;
    this->m_texture = texture;
    this->m_speed = speed;
}

/* Change color. */
void DynamicActor::changeColor(Color color) {
    this->m_activeColor = color;
}

/* Return current health of actor. */
float DynamicActor::getHealth() {
    return m_health;
}

void DynamicActor::attack() {
}

void DynamicActor::setPosition(std::tuple<float, float> position) {
    this->m_position = position;
}
