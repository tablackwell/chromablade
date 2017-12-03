#include "Actor.hpp"

Actor::Actor() {
}

Actor::Actor(Actor::Type type, sf::Vector2f size, sf::Vector2f pos) {
    if (type == Actor::Rock) {
        m_rect.setSize(size);
        m_rect.setPosition(pos);
        m_rect.setFillColor(sf::Color(150,75,0));
        m_type = Actor::Rock;
    }
    m_type = type;
}

void Actor::draw(sf::RenderWindow *window) {
    window->draw(m_rect);
}

sf::FloatRect Actor::getGlobalBounds() {
    return m_rect.getGlobalBounds();
}
