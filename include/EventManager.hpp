/*
 * Event manager used for processing events.
 */

#ifndef EVENT_MANAGER
#define EVENT_MANAGER

class EventManager {
public:
    virtual const EventType& getEventType(void) const =0;
    virtual float getTimeStamp(void) const = 0;
}

#endif
