#ifndef DOOREVENT_HPP
#define DOOREVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include "Level.hpp"

class DoorEvent : public EventInterface {
public:
    DoorEvent(Level level) { m_level = level; m_room = 0; m_type = doorEvent; }
    const EventType& getEventType(void) const { return m_type; };
private:
    Level m_level;
    int m_room;
    EventType m_type;
};
#endif
