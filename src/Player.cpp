/*
 * Implementation of PlayerView class, instance of DynamicActor class used for player's
 * character.
 */

#include "Player.hpp"
#include "DynamicActor.hpp"

#include <iostream>

Player::Player() {
    // Initialize hashmap. Start with red by default.
    colorsAvail[AvailableColors::RED] = true;
    activeColor = AvailableColors::RED;
}

/* Change active color of player's sword to given color. */
void Player::changeSwordColor(AvailableColors color) {
    DynamicActor::changeColor(color);
}

/* Unlock color. */
void Player::unlockColor(AvailableColors color) {
    
}
