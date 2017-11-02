/*
 * Implementation of Player class, instance of DynamicActor class used for player's
 * character.
 */

#include "Player.hpp"
#include "DynamicActor.hpp"

#include <iostream>

Player::Player() {
    // Initialize hash map. Start with red by default.
    colorsAvail[Color::RED] = true;
    changeColor(Color::RED);
    setPosition(std::make_tuple(0, 0)); // Initialize player position as a tuple
}

/* Change active color of player's sword to given color. */
void Player::changeSwordColor(Color color) {
    changeColor(color);
}

/* Unlock color. */
void Player::unlockColor(Color color) {
	 colorsAvail[color] = true;
}

void Player::attack() {

}
