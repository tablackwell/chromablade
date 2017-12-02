#include "Player.hpp"
#include "DynamicActor.hpp"

#include <iostream>


/*
 * Implementation of Player class, instance of DynamicActor class used for player's
 * character.
 */
Player::Player() : DynamicActor(sf::Color::Red, 100, 20, sf::Vector2f(196, 255), 200.f) {
    m_colorsAvail.push_back(sf::Color::Red); // Start with red by default.
}


/* Change active color of player's sword to given color. */
void Player::changeSwordColor(sf::Color color) {
    for(int i = 0; i < m_colorsAvail.size(); i++){
        if (m_colorsAvail[i] == color) { // if color is available
            changeColor(color);
        }
    }
}


/* Unlock a new color. */
void Player::unlockColor(sf::Color color) {
	 m_colorsAvail.push_back(color);
}


/* Causes damage to the enemy */
void Player::attack(DynamicActor &enemy) {
    enemy.setHealth(enemy.getHealth() - getDamage());
}


/* Returns whether the player has a certain color */
bool Player::hasColor(sf::Color color) {
    for(int i = 0; i < m_colorsAvail.size(); i++){
        if (m_colorsAvail[i] == color) { // if color is available
            changeColor(color);
            return true;
        }
    }
    return false;
}
