/*
 * CollisionEvent implements EventInterface.
 */

#ifndef COLLISIONEVENT_HPP
#define COLLISIONEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"

class CollisionEvent : public EventInterface {
	public:
	    static const EventType eventType;
};

const EventType CollisionEvent::eventType = EventType(&CollisionEvent::eventType);
#endif
