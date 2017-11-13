#ifndef MOVEEVENT_HPP
#define MOVEEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"


enum Direction { Up, Down, Left, Right };


/*
 * A MoveEvent is generated when the player presses keys associated with character movement.
 */
class MoveEvent : public EventInterface {
    public:
        MoveEvent(Direction direction) { m_dir = direction; m_type = moveEvent; }
        Direction getDirection() const { return m_dir; }
        const EventType& getEventType(void) const { return m_type; }

    private:
    
    private: // event data
        Direction m_dir;
        EventType m_type;
};

#endif
