/*
 * Player inherits from the DynamicActor class. It is used to implement all of player's character
 * functionality.
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <stdio.h>
#include <map>

#include "DynamicActor.hpp"

class Player: public DynamicActor{
    public:
        Player();
        void changeSwordColor(Color color);
        void unlockColor(Color color);
        void attack();
    private:

    private:
        std::map<Color, bool> colorsAvail; // Hash map of available colors.
        //int colorTimer;
};

#endif
