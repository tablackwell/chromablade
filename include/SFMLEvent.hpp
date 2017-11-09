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
	const sf::Event getSFMLEvent() const;
private:
	sf::Event m_event;
    EventType m_type;
private:
};

#endif
