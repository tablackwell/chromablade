#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Actor {
public:
    Actor();
    enum Type { Player, RedMob, BlueMob, YellowMob, Rock };
    Actor(Type type, sf::Vector2f size, sf::Vector2f pos);
    void draw(sf::RenderWindow *window);
private:
    Type m_type;
    sf::RectangleShape m_rect;
    sf::Texture m_texture;
};

#endif
