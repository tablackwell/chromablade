#ifndef SPAWNEVENT_HPP
#define SPAWNEVENT_HPP

#include <SFML/Graphics.hpp>
#include "EventInterface.hpp"
#include "EventType.hpp"
#include "Actor.hpp"

class SpawnEvent : public EventInterface {
public:
    SpawnEvent(Actor::Type type, int count, sf::Vector2f size, sf::Vector2f center);
    const EventType& getEventType(void) const;
    const Actor::Type getActorType() const;
    const int getCount() const;
    const sf::Vector2f getSize() const;
    const sf::Vector2f getCenter() const;
private:
    EventType m_type;
    Actor::Type m_actorType;
    int m_count;
    sf::Vector2f m_size;
    sf::Vector2f m_center;
};
#endif
