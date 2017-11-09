/*
 * SFMLEvent used for registering SFML events in Event Manager.
 */

 #include "SFMLEvent.hpp"

SFMLEvent::SFMLEvent(sf::Event event) {
    this->m_event = event;
    this->m_type = EventType::sfmlEvent;
}

/* Return SFML Event of sf::Event type. */
const sf::Event SFMLEvent::getSFMLEvent() const {
	return m_event;
}


/* Return event type. */
const EventType& SFMLEvent::getEventType() const {
  return m_type;
}
