#ifndef DYNAMIC_ACTOR
#define DYNAMIC_ACTOR

#include <stdio.h>
#include <SFML/Graphics.hpp>

/* List of all possible colors */
enum Color{
    RED, BLUE, YELLOW, GREEN, ORANGE, PURPLE
};


/*
 * Dynamic actor class. All dynamic actors inherit from the dynamic actor class.
 */
class DynamicActor {
	public:
		DynamicActor();
		DynamicActor(Color activeColor, float health, float damage, std::tuple<int, int> startPos, sf::Texture texture, int speed);
		float getHealth();
		virtual void attack();
		void changeColor(Color color);
		void setHealth(float health);

	private:

	private:
		Color activeColor;
		float health;
		float damage; // Attack damage
		std::tuple<int, int> position;
		sf::Texture texture;
		int speed;
};


#endif
