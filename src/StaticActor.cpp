#include "StaticActor.hpp"

StaticActor::StaticActor(StaticActor::Type type, sf::Vector2f size, sf::Vector2f pos) {
//    if (type == StaticActor::Rock) {
//        if(!m_texture.loadFromFile("../res/.png")) {
//            // ERROR
//        }
//    }
//	m_character.setTexture(m_charTexture);
//	m_character.setPosition(sf::Vector2f(180, 210));

    m_type = type;
    m_rect.setSize(pos);
    m_rect.setOrigin(pos.x/2, pos.y/2);
    m_rect.setPosition(200, 200);
    m_rect.setFillColor(sf::Color::Red);
}

void StaticActor::draw(sf::RenderWindow &window) {
    window.draw(m_rect);
}

