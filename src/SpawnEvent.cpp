#include "SpawnEvent.hpp"

SpawnEvent::SpawnEvent(Actor::Type type, int count, sf::Vector2f size, sf::Vector2f center) {
    m_type = spawnEvent;
    m_actorType = type;
    m_count = count;
    m_size = size;
    m_center = center;
}

const Actor::Type SpawnEvent::getActorType() const {
    return m_actorType;
}

const int SpawnEvent::getCount() const {
    return m_count;
}

const sf::Vector2f SpawnEvent::getSize() const {
    return m_size;
}

const sf::Vector2f SpawnEvent::getCenter() const {
    return m_center;
}


