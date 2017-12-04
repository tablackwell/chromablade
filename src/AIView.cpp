#include "AIView.hpp"
#include "Macros.hpp"
#include "AStar.hpp"

AIView::AIView(DynamicActor *actor, GameLogic *gameLogic) {
    m_actor = actor;
    m_gameLogic = gameLogic;
    m_prevEnd.x = m_prevEnd.y = 0;
    m_route = "";
}

void AIView::move(const sf::Vector2f& target) {
    char **pathMap = m_gameLogic->getPathMap();
    sf::Vector2i numNodes = m_gameLogic->getNumNodes();

    sf::Vector2f pos = m_actor->getPosition();
    sf::Vector2i start((int) pos.x % WIDTH / TILE_DIM, (int) pos.y % HEIGHT / TILE_DIM);
    sf::Vector2i end((int) target.x % WIDTH / TILE_DIM, (int) target.y % HEIGHT / TILE_DIM);

    if (end != m_prevEnd) {
        m_route = AStar::pathFind(start.x, start.y, end.x, end.y,
                                            pathMap, numNodes.x, numNodes.y);
        printf("new route: %s\n", m_route.c_str());
        m_prevEnd = end;
    }

    sf::Vector2i d(m_route[0] - '0', m_route[0] - '0');
    m_actor->setPosition(sf::Vector2f(pos.x + 0.8 * dx[d.x], pos.y + 0.8 * dy[d.y]));
}
