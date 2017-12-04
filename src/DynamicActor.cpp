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
    this->m_animatedSprite.setPosition(startPos);
}


/* Changes active color. */
void DynamicActor::changeColor(sf::Color color) {
    this->m_activeColor = color;
}


sf::Color DynamicActor::getColor() {
    return m_activeColor;
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
    m_animatedSprite.setPosition(position);
}


/* Returns the actor position */
sf::Vector2f DynamicActor::getPosition() {
    return m_position;
}


/* Returns the actor's attack damage */
float DynamicActor::getDamage() {
    return m_damage;
}


void DynamicActor::draw(sf::RenderWindow *window) {
    window->draw(m_animatedSprite);
}


void DynamicActor::setAnimation(Animation &leftAnimation, Animation &rightAnimation, Animation &upAnimation, Animation &downAnimation) {
    m_animatedSprite.play(downAnimation);
    m_MobWalkingDown = downAnimation;
    m_MobWalkingUp = upAnimation;
    m_MobWalkingRight = rightAnimation;
    m_MobWalkingLeft = leftAnimation;
}

sf::FloatRect DynamicActor::getGlobalBounds() {
    return m_animatedSprite.getGlobalBounds();
}
