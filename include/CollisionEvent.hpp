/*
 * CollisionEvent implements EventInterface.
 */

#ifndef COLLISIONEVENT_HPP
#define COLLISIONEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"

class CollisionEvent : public EventInterface {
	public:
	private:
	    const GameEventsType& getEventType(void) const { return eventType;};
	private:
	    static const GameEventsType eventType;
};

#endif
