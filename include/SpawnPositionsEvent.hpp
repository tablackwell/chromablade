#ifndef SPAWNPOSITIONSEVENT_HPP
#define SPAWNPOSITIONSEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include "Actor.hpp"
#include "DynamicActor.hpp"
#include <vector>

class SpawnPositionsEvent : public EventInterface {
public:
    SpawnPositionsEvent(const std::vector<Actor*>& rocks,
                        const std::vector<DynamicActor*> &mobs);
    const std::vector<Actor*> getRocks();
    const std::vector<DynamicActor*> getMobs();
private:
    std::vector<Actor*> m_rocks;
    std::vector<DynamicActor*> m_mobs;
};

#endif
