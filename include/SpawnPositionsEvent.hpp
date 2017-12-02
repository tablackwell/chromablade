#ifndef SPAWNPOSITIONSEVENT_HPP
#define SPAWNPOSITIONSEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"

class SpawnPositionsEvent : public EventInterface {
public:
    SpawnPositionsEvent(const std::vector& rocks, const std::vector &mobs);
    const EventType& getEventType(void) const;
private:
    EventType m_type;
    const std::vector m_rocks;
    const std::vector m_mobs;
};

#endif
