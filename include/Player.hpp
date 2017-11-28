/*
 * Player inherits from the DynamicActor class. It is used to implement all of player's character
 * functionality.
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <stdio.h>
#include <vector>

#include "DynamicActor.hpp"

class Player: public DynamicActor{
    public:
        Player();
        void changeSwordColor(sf::Color color);
        void unlockColor(sf::Color color);
        void attack(DynamicActor enemy);
    private:

    private:
        std::vector<sf::Color> m_colorsAvail; // Hash map of available colors.
};

#endif
