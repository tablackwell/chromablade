#ifndef STATICACTOR_HPP
#define STATICACTOR_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <tuple>

class StaticActor {
    public:
        enum Type { Rock };
        StaticActor(Type type, sf::Vector2f size, sf::Vector2f pos);
        void draw(sf::RenderWindow &window);

    private:
        Type m_type;
        sf::RectangleShape m_rect;
        sf::Texture m_texture;
};

#endif
