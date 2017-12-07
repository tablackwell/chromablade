/*
 * Implementation of DynamicActor class.
 */

#include "DynamicActor.hpp"
#include <iostream>
#include <cmath>


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
    m_knockback = false;
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

void DynamicActor::setKnockback(bool b) {
    m_knockback = b;
}

bool DynamicActor::getKnockback() {
    return m_knockback;
}

void DynamicActor::move(int x, int y, float deltaTime) {
    Direction dir;
    if (x == 1) {
        m_animatedSprite.play(m_MobWalkingRight);
    }
    else if (x == -1) {
        m_animatedSprite.play(m_MobWalkingLeft);
    }
    else if (y == -1) {
        m_animatedSprite.play(m_MobWalkingUp);
    }
    else {
        m_animatedSprite.play(m_MobWalkingDown);
    }
    sf::Vector2i v((int) (x * deltaTime * m_speed), (int) (y * deltaTime * m_speed));

    v.x = (v.x > 4) ? 4 : v.x;
    v.x = (v.x < -4) ? -4 : v.x;
    v.y = (v.y > 4) ? 4 : v.y;
    v.y = (v.y < -4) ? -4 : v.y;
    if (v.x == 3) v.x = 4;
    if (v.x == -3) v.x = -4;
    if (v.y == 3) v.y = 4;
    if (v.y == -3) v.y = -4;

    printf("%d %d\n", v.x, v.y);

    m_animatedSprite.move(v.x, v.y);
    this->m_position.x += v.x;
    this->m_position.y += v.y;
//    m_animatedSprite.move(x, y);
//    this->m_position.x += x;
//    this->m_position.y += y;
    m_animatedSprite.update(sf::seconds(deltaTime));
}

int DynamicActor::getSpeed() {
    return m_speed;
}
