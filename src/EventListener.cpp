/*
 * Event listener.
 */

#include "EventListener.hpp"

/* Set function. */
void EventListener::setFunction(std::function<void(const EventInterface&)> function) {
    this -> m_function = function;
}


/* Set id. */
void EventListener::setId(float id) {
    this -> m_id = id;
}

/* Get id. */
float EventListener::getId() const {
    return m_id;
}

/* Call function. */
void EventListener::callFunction(const EventInterface &event) {
    this -> m_function(event);
}

