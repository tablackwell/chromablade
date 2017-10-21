/*
 * Event interface used for event management.
 */

#ifndef EVENT_INTERFACE
#define EVENT_INTERFACE

#include "EventType.hpp"

class EventInterface {
	public:
	    virtual const GameEventsType &getEventType(void);
	private:
	private:
};

#endif
