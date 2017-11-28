#include "Player.hpp"
#include "DynamicActor.hpp"

#include <iostream>


/*
 * Implementation of Player class, instance of DynamicActor class used for player's
 * character.
 */
Player::Player() : DynamicActor(Color::RED, 100, 20, sf::Vector2f(196, 255), 200.f) {
    // Initialize hash map. Start with red by default.
    m_colorsAvail[Color::RED] = true;
}


/* Change active color of player's sword to given color. */
void Player::changeSwordColor(Color color) {
    changeColor(color);
}


/* Unlock a new color. */
void Player::unlockColor(Color color) {
	 m_colorsAvail[color] = true;
}


/* Causes damage to the enemy */
void Player::attack(DynamicActor enemy) {
    float health = enemy.getHealth();
    health -= getDamage();
}
