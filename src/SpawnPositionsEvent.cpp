#include "SpawnPositionsEvent.hpp"

SpawnPositionsEvent::SpawnPositionsEvent(const std::vector<Actor*>& rocks,
                                         const std::vector<DynamicActor*> &mobs) {
    m_type = spawnPositionsEvent;
    m_rocks = rocks;
    m_mobs = mobs;
}

const std::vector<Actor*> SpawnPositionsEvent::getRocks() const {
    return m_rocks;
}

const std::vector<DynamicActor*> SpawnPositionsEvent::getMobs() const {
    return m_mobs;
}

