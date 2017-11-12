#ifndef EVENTINTERFACE_HPP
#define EVENTINTERFACE_HPP

#include "EventType.hpp"
#include <SFML/Window.hpp>


/*
 * Event interface used for event management.
 */
class EventInterface {
public:
    const EventType& getEventType(void) const { return m_type; };
    const float getDeltaTime(void) const { return m_deltaTime; }
    void setDeltaTime(float deltaTime) {this->m_deltaTime = deltaTime; }
private:
private:
    EventType m_type;
    float m_deltaTime;
};

#endif
