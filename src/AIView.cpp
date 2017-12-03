#include "AIView.hpp"
#include "SpawnPositionsEvent.hpp"

AIView::AIView(DynamicActor *actor, std::vector<Actor*> *rocks, 
                                    std::vector<DynamicActor*> *mobs) {
    m_actor = actor;
    m_rocks = rocks;
    m_mobs = mobs;
}

void AIView::move(const sf::Vector2f& target) {
    //printf("moving to %f %f\n", target.x, target.y);

    sf::Vector2f pos = m_actor->getPosition();
    m_actor->setPosition(sf::Vector2f(pos.x - 1, pos.y));
}
