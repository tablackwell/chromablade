#include "AIView.hpp"
#include "Macros.hpp"
#include "AStar.hpp"
#include "AttackEvent.hpp"

AIView::AIView(DynamicActor *actor, GameLogic *gameLogic, ChromaBlade *game) {
    m_actor = actor;
    m_gameLogic = gameLogic;
    m_game = game;
    m_prevEnd.x = m_prevEnd.y = -1;
    m_dest.x = m_dest. y = -1;
    m_route = "";
    m_walk = 0;
}

void AIView::move(const PlayerView* pview, float &deltaTime) {
    char **pathMap = m_gameLogic->getPathMap();
    sf::Vector2i numNodes = m_gameLogic->getNumNodes();
    sf::Vector2f pos = m_actor->getPosition();
    sf::Vector2f prevPos(pos);
    sf::FloatRect gb = m_actor->getGlobalBounds();
    std::vector<DynamicActor*> mobs = m_gameLogic->getMobs();

    sf::Vector2f ppos = pview->getPosition();
    sf::FloatRect pgb = pview->getGlobalBounds();
    sf::Vector2f target(ppos.x + pgb.width / 2, ppos.y + pgb.height / 2);

    sf::Vector2i start((int) pos.x % WIDTH / TILE_DIM,
                       (int) pos.y % HEIGHT / TILE_DIM);
    sf::Vector2i end((int) target.x % WIDTH / TILE_DIM,
                     (int) target.y % HEIGHT / TILE_DIM);

    // initialize
    if (m_dest.x == -1 && m_dest.y == -1) {
        m_route = AStar::pathFind(start.x, start.y, end.x, end.y,
                                            pathMap, numNodes.x, numNodes.y);
        printf("starting route: %s\n", m_route.c_str());
        m_prevEnd = end;

        m_walk = 0;
        m_di.x = m_route[m_walk] - '0';
        m_di.y = m_route[m_walk] - '0';
        m_dest.x = ((int) pos.x / TILE_DIM + dx[m_di.x]) * TILE_DIM;
        m_dest.y = ((int) pos.y / TILE_DIM + dy[m_di.y]) * TILE_DIM;
    // already initialized
    } else {
        // if not at destination
        if (pos != m_dest) {
            // move
            sf::Vector2f newPos(pos.x + SPEED/1.7 * deltaTime * dx[m_di.x],
                                pos.y + SPEED/1.7 * deltaTime * dy[m_di.y]);
            gb.top = newPos.y;
            gb.left = newPos.x;

            // check intersection with other mobs
            bool mobIntersect = false;
            for (int i = 0; i < mobs.size(); i++) {
                sf::Vector2f mobPos = mobs[i]->getPosition();
                if (mobPos == pos) {
                    continue;
                }
                if (gb.intersects(mobs[i]->getGlobalBounds())) {
                    mobIntersect = true;
                    break;
                }
            }

            if (!mobIntersect) {
                if (!gb.intersects(pgb)) {
                    // move if no mob-mob, mob-player collisions
                    m_actor->setPosition(newPos);

                    sf::Vector2f dist;
                    dist.x = abs(newPos.x - m_dest.x);
                    dist.y = abs(newPos.y - m_dest.y);

                    // reset if went past destination
                    if (dist.x > m_prevDist.x || dist.y > m_prevDist.y) {
                        m_actor->setPosition(m_dest);
                    } else {
                        m_prevDist = dist;
                    }
                // collided with player
                } else {
                    printf("send attackEvent!\n");
                    AttackEvent *attackEvent = new AttackEvent(false, m_actor);
                    m_game->queueEvent(attackEvent);
                }
            }

        // reached destination
        } else {
            // if target has moved, get a new route
            if (end != m_prevEnd) {
                m_route = AStar::pathFind(start.x, start.y, end.x, end.y,
                                                    pathMap, numNodes.x, numNodes.y);
                printf("new route: %s\n", m_route.c_str());
                m_prevEnd = end;
                m_walk = 0;
            // else same target, update new destination
            } else {
                m_walk++;
            }
            m_di.x = m_route[m_walk] - '0';
            m_di.y = m_route[m_walk] - '0';
            m_dest.x = ((int) pos.x / TILE_DIM + dx[m_di.x]) * TILE_DIM;
            m_dest.y = ((int) pos.y / TILE_DIM + dy[m_di.y]) * TILE_DIM;
            m_prevDist.x = abs(TILE_DIM * dx[m_di.x]);
            m_prevDist.y = abs(TILE_DIM * dy[m_di.y]);
        }
    }
}
