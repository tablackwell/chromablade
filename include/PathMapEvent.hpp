#ifndef PATHMAPEVENT_HPP
#define PATHMAPEVEN_HPP

#include <SFML/Graphics.hpp>
#include "EventInterface.hpp"
#include "EventType.hpp"

class PathMapEvent : public EventInterface {
public:
    PathMapEvent(sf::Vector2f size, sf::Vector2f center);
    const sf::Vector2f getSize() const;
    const sf::Vector2f getCenter() const;
private:
    sf::Vector2f m_size;
    sf::Vector2f m_center;
};

#endif
