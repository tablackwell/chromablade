/*
 * Event interface used for event management.
 */

#ifndef EVENTINTERFACE_HPP
#define EVENTINTERFACE_HPP

#include "EventType.hpp"
#include <SFML/Window.hpp>

class EventInterface {
public:
    virtual const EventType& getEventType(void) const = 0;
    const float getDeltaTime(void) const { return m_deltaTime; }
    void setDeltaTime(float deltaTime) {this->m_deltaTime = deltaTime; }
private:
private:
    EventType m_type;
    float m_deltaTime;
};

#endif
