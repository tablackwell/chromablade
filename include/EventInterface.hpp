/*
 * Event interface used for event management.
 */

#ifndef EVENTINTERFACE_HPP
#define EVENTINTERFACE_HPP

#include "EventType.hpp"

class EventInterface {
	public:
	    virtual const GameEventsType& getEventType(void);
	private:
	private:
};

#endif
