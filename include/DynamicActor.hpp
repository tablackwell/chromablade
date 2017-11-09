#ifndef DYNAMICACTOR_HPP
#define DYNAMICACTOR_HPP

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include<tuple>

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
		DynamicActor(Color activeColor, float health, float damage, std::tuple<float, float> startPos, sf::Texture texture, int speed);
		float getHealth();
		virtual void attack();
		void changeColor(Color color);
		void setHealth(float health);
		void setPosition(std::tuple<float, float>);

	private:

	private:
		Color m_activeColor;
		float m_health;
		float m_damage; // Attack damage
		std::tuple<float, float> m_position;
		sf::Texture m_texture;
		int m_speed;
};


#endif
