#include "AIView.hpp"
#include "SpawnPositionsEvent.hpp"

AIView::AIView(DynamicActor *actor) {
    m_actor = actor;
}

void AIView::setSpawnPositions(std::vector<Actor*> rocks, std::vector<DynamicActor*> mobs) {
    printf("setSpawnPositions!\n");
    m_rocks = rocks;
    m_mobs = mobs;
}

