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
	    const EventType& getEventType(void) const;
	    void setDirection(Direction direction);
	    Direction getDirection();
	private:
	private:
	    static const EventType m_eventType;
	    // event data
	    Direction dir;
};

#endif
