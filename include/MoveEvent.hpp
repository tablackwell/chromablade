/*
 * MoveEvent implements EventInterface.
 */

#ifndef MOVEEVENT_HPP
#define MOVEEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"

enum Direction { Up, Down, Left, Right };


class MoveEvent : public EventInterface {
	public:
        MoveEvent(Direction direction);
	    virtual const EventType& getEventType(void) const;
	    void setDirection(Direction direction);
	    Direction getDirection();
        static const EventType eventType = EventType::moveEvent;
	private:
    
	private:
	    // event data
	    Direction m_dir;
};

#endif
