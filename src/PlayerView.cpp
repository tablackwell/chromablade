/*
 * Implementation of PlayerView class, instance of DynamicActor class used for player's
 * character.
 */

#include "PlayerView.hpp"
#include "DynamicActor.hpp"

#include <iostream>

PlayerView::PlayerView() {
    // Initialize hashmap. Start with red by default.
    colorsAvail[AvailableColors::RED] = true;
}

/* Change active color of player's sword to given color. */
void PlayerView::changeSwordColor(AvailableColors color) {
    DynamicActor::changeColor(color);
}

/* Unlock color. */
void PlayerView::unlockColor(AvailableColors color) {
    
}
