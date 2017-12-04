#ifndef MOVEMOBSEVENT_HPP
#define MOVEMOBSEVENT_hpp

#include "EventInterface.hpp"
#include "EventType.hpp"

class MoveMobsEvent : public EventInterface {
public:
    MoveMobsEvent(sf::Vector2f target);
    const sf::Vector2f getTarget() const;
private:
    sf::Vector2f m_target;
};

#endif
