#include "PathMapEvent.hpp"

PathMapEvent::PathMapEvent(sf::Vector2f size, sf::Vector2f center) {
    m_type = pathMapEvent;
    m_size = size;
    m_center = center;
}

const sf::Vector2f PathMapEvent::getSize() const {
    return m_size;
}

const sf::Vector2f PathMapEvent::getCenter() const {
    return m_center;
}



