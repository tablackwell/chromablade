/*
 * Event listener.
 */

#include <iostream>
#include "EventListener.hpp"

EventListener::EventListener(std::function<void(const EventInterface&)> function) {
	setFunction(function);
}


EventListener::EventListener(std::function<void(const EventInterface&)> function, float id) {
	setFunction(function);
	setId(id);
}


/* Set function. */
void EventListener::setFunction(std::function<void(const EventInterface&)> function) {
    this->m_function = function;
}


/* Set id. */
void EventListener::setId(float id) {
    this->m_id = id;
}

/* Get id. */
float EventListener::getId() const {
    return m_id;
}

/* Call function. */
void EventListener::callFunction(const EventInterface &event) {
    this->m_function(event);
}

