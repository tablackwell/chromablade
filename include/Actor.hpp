#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class Actor {
public:
    Actor();
    enum Type { Player, Mob, Rock, Greyscale };
    Actor(Type type, sf::Vector2f size, sf::Vector2f pos);
    virtual void draw(sf::RenderWindow *window);
    virtual sf::FloatRect getGlobalBounds();
    void setTexture(sf::Texture &texture);
    sf::RectangleShape m_rect;

protected:
    Type m_type;

private:
};

#endif
