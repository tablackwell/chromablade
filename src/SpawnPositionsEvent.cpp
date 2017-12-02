#include "SpawnPosiionsEvent.hpp"

SpawnPositionsEvent::SpawnPositionsEvent(const std::vector& rocks, const std::vector &mobs) {
    m_type = spawnPositionsEvent;
    m_rocks = rocks;
    m_mobs = mobs;
}

const EventType& SpawnPositionsEvent::getEventType(void) const {
    return m_type;
}
    
const std::vector SpawnPositionsEvent::getRocks() {
    return m_rocks;
}

const std::vector SpawnPositionsEvent::getMobs() {
    return m_mobs;
}

