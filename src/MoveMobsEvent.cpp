#include "MoveMobsEvent.hpp"

MoveMobsEvent::MoveMobsEvent(sf::Vector2f target) {
    m_type = moveMobsEvent;
    m_target = target;
}

const EventType& MoveMobsEvent::getEventType(void) const {
    return m_type;
}

const sf::Vector2f MoveMobsEvent::getTarget() const {
    return m_target;
}

