#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

static sf::Color Orange(255,127,0);
static sf::Color Purple(128,0,128);

class Actor {
public:
    Actor();
    enum Type { Player, Mob, Rock };
    Actor(Type type, sf::Vector2f size, sf::Vector2f pos);
    void draw(sf::RenderWindow *window);
    sf::FloatRect getGlobalBounds();
private:
    Type m_type;
    sf::RectangleShape m_rect;
    sf::Texture m_texture;
};

#endif
