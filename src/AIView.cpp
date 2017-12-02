#include "AIView.hpp"
#include "SpawnPositionsEvent.hpp"

AIView::AIView(DynamicActor *actor, std::vector<Actor*>*rocks, 
                                    std::vector<DynamicActor*> *mobs) {
    m_actor = actor;
    m_rocks = rocks;
    m_mobs = mobs;
}
