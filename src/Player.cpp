#include "Player.hpp"
#include "DynamicActor.hpp"

#include <iostream>


/*
 * Implementation of Player class, instance of DynamicActor class used for player's
 * character.
 */
Player::Player() : DynamicActor(sf::Color::Red, 100, 20, sf::Vector2f(196, 255), 200.f) {
    // Initialize hash map. Start with red by default.
    m_colorsAvail.push_back(sf::Color::Red);
    m_colorsAvail.push_back(sf::Color::Yellow); // allow all colors for testings
    m_colorsAvail.push_back(sf::Color::Blue);
}


/* Change active color of player's sword to given color. */
void Player::changeSwordColor(sf::Color color) {
    changeColor(color);
}


/* Unlock a new color. */
void Player::unlockColor(sf::Color color) {
	 m_colorsAvail.push_back(color);
}


/* Causes damage to the enemy */
void Player::attack(DynamicActor enemy) {
    float health = enemy.getHealth();
    health -= getDamage();
}
