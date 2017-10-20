#ifndef DYNAMIC_ACTOR
#define DYNAMIC_ACTOR

#include <stdio.h>
#include <SFML/Graphics.hpp>

/* List of all possible colors */
enum AvailableColors{
    RED, BLUE, YELLOW, GREEN, ORANGE, PURPLE
};


/*
 * Dynamic actor class. All dynamic actors inherit from the dynamic actor class.
 */
class DynamicActor {
	public:
		DynamicActor();
		DynamicActor(AvailableColors activeColor, float health, float damage, std::tuple<int, int> startPos, sf::Texture sprite, int speed);
		float checkHealth();
		virtual void attack();
		void changeColor(AvailableColors color);

	private:

	private:
		AvailableColors activeColor;
		float health;
		float damage; // Attack damage
		std::tuple<int, int> position;
		sf::Texture sprite;
		int speed;
};


#endif
