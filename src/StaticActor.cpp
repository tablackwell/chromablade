#include "StaticActor.hpp"

StaticActor::StaticActor(StaticActor::Type type, sf::Vector2f size, sf::Vector2f pos) {
    if (type == StaticActor::Rock) {
        m_rect.setSize(size);
        m_rect.setPosition(pos);
        m_rect.setFillColor(sf::Color(150,75,0));
    }
//        if(!m_texture.loadFromFile("../res/.png")) {
//            // ERROR
//        }
//    }
//	m_character.setTexture(m_charTexture);
//	m_character.setPosition(sf::Vector2f(180, 210));

    m_type = type;
}

void StaticActor::draw(sf::RenderWindow &window) {
    window.draw(m_rect);
}

