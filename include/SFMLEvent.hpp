/*
 * SFML events. Used for registering SFML events.
 */

 #ifndef SFMLEVENT_HPP
 #define SFMLEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include <SFML/Window.hpp>

class SFMLEvent : public EventInterface{
public:
  SFMLEvent(sf::Event event);
  virtual const EventType& getEventType(void) const;
private:
  sf::Event event;
  EventType type;
private:
};

#endif
