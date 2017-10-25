/*
 * SFMLEvent used for registering SFML events in Event Manager.
 */

 #include "SFMLEvent.hpp"

SFMLEvent::SFMLEvent(sf::Event event) {
  this->event = event;
  this->type = EventType::sfmlEvent;
}


const EventType& SFMLEvent::getEventType() const {
  return type;
}
