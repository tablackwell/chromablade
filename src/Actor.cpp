#include "Actor.hpp"

/* Base class for dynamic actor */
Actor::Actor() {
}


Actor::Actor(Actor::Type type, sf::Vector2f size, sf::Vector2f pos) {
    if (type == Actor::Rock) {
        m_rect.setSize(size);
        m_rect.setPosition(pos);
        m_rect.setTextureRect(sf::IntRect(64,1120,32,32));
        m_type = Actor::Rock;
    }
    m_type = type;
}


/* Call the window to draw the m_rect */
void Actor::draw(sf::RenderWindow *window) {
    window->draw(m_rect);
}


/* Return global bounds for m_rect */
sf::FloatRect Actor::getGlobalBounds() {
    return m_rect.getGlobalBounds();
}


/* Set the texture for m_rect */
void Actor::setTexture(sf::Texture &texture) {
    m_rect.setTexture(&texture);
}
