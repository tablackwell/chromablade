/*
 * CollisionEvent implements EventInterface.
 */

#ifndef COLLISION_EVENT
#define COLLISION_EVENT

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
