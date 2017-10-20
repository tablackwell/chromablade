/*
 * Player View inherits from the View class. It is used to implement all of player's character
 * functionality.
 */

#ifndef PlayerView_hpp
#define PlayerView_hpp

#include <stdio.h>
#include <map>

#include "DynamicActor.hpp"

class PlayerView: public DynamicActor{
	public:
    	PlayerView();
    	void changeSwordColor(AvailableColors color);
    	void unlockColor(AvailableColors color);
	private:
    
	private:
    	std::map<AvailableColors, bool> colorsAvail; // Hashmap of available colors.
    	//int colorTimer;
};
#endif
