#include "Player.hpp"
#include "DynamicActor.hpp"

#include <iostream>


/*
 * Implementation of Player class, instance of DynamicActor class used for player's
 * character.
 */
Player::Player() {
    // Initialize hash map. Start with red by default.
    m_colorsAvail[Color::RED] = true;
    changeColor(Color::RED);
    setPosition(std::make_tuple(196, 255)); // Initialize player position as a tuple
}


/* Change active color of player's sword to given color. */
void Player::changeSwordColor(Color color) {
    changeColor(color);
}


/* Unlock color. */
void Player::unlockColor(Color color) {
	 m_colorsAvail[color] = true;
}


void Player::attack() {

}
