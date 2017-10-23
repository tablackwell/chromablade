/*
 * Event interface used for event management.
 */

#ifndef EVENTINTERFACE_HPP
#define EVENTINTERFACE_HPP

#include "EventType.hpp"

class EventInterface {
	public:
	    virtual const EventType& getEventType(void) const = 0;
	private:
	private:
};

#endif
