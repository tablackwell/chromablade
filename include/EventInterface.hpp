/*
 * Event interface used for event management.
 */

#ifndef EVENT_INTERFACE
#define EVENT_INTERFACE

class EventInterface {
public:
    virtual const EventType& getEventType(void) const =0;
    virtual float getTimeStamp(void) const = 0;
}

#endif
