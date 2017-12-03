#ifndef DYNAMICACTOR_HPP
#define DYNAMICACTOR_HPP

#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "Actor.hpp"
#include "AnimatedSprite.hpp"

/*
 * Dynamic actor class. All dynamic actors inherit from the dynamic actor class.
 */
class DynamicActor : public Actor {
	public:
		DynamicActor();
		DynamicActor(sf::Color activeColor, float health, float damage, sf::Vector2f startPos, int speed);
		float getHealth();
		virtual void attack(DynamicActor &enemy) {};
		void changeColor(sf::Color color);
		sf::Color getColor();
		void setHealth(float health);
		void setPosition(sf::Vector2f pos);
		sf::Vector2f getPosition();
		float getDamage();
		void draw(sf::RenderWindow *window);
		void setCurrAnimation(Animation animation);
		sf::FloatRect getGlobalBounds();

	protected:
        AnimatedSprite m_animatedSprite;

	private:
        sf::Color m_activeColor;
		float m_health;
		float m_damage; // Attack damage
		sf::Vector2f m_position;
		int m_speed;

};


#endif
