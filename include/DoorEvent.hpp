#ifndef DOOREVENT_HPP
#define DOOREVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include "Room.hpp"

class DoorEvent : public EventInterface {
public:
    DoorEvent(Room room) { m_room = room; m_type = doorEvent; }
    const EventType& getEventType(void) const { return m_type; };
private:
    Room m_room;
    EventType m_type;
};
#endif
