/*
 * Implementation of DynamicActor class.
 */

#include "DynamicActor.hpp"
#include <iostream>


DynamicActor::DynamicActor() {

}


DynamicActor::DynamicActor(sf::Color color, float health, float damage, sf::Vector2f startPos, int speed) {
    this->m_activeColor = color;
    this->m_health = health;
    this->m_damage = damage;
    this->m_position.x = startPos.x;
    this->m_position.y = startPos.y;
    this->m_speed = speed;
}


/* Changes active color. */
void DynamicActor::changeColor(sf::Color color) {
    this->m_activeColor = color;
}


/* Returns current health of actor. */
float DynamicActor::getHealth() {
    return m_health;
}


/* Sets current health of actor. */
void DynamicActor::setHealth(float health) {
    m_health = health;
}


/* Sets the actor position */
void DynamicActor::setPosition(sf::Vector2f position) {
    this->m_position = position;
    m_rect.setPosition(position);
}


/* Returns the actor position */
sf::Vector2f DynamicActor::getPosition() {
    return m_position;
}


/* Returns the actor's attack damage */
float DynamicActor::getDamage() {
    return m_damage;
}
