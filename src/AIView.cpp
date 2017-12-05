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
    m_init = true;
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
    sf::Vector2f target(ppos.x + pgb.width / 2, ppos.y + pgb.height * 0.75);

    sf::Vector2i start((int) pos.x % WIDTH / TILE_DIM,
                       (int) pos.y % HEIGHT / TILE_DIM);
    sf::Vector2i end((int) target.x % WIDTH / TILE_DIM,
                     (int) target.y % HEIGHT / TILE_DIM);

    // initialize
    if (m_init) {
        m_route = AStar::pathFind(start.x, start.y, end.x, end.y,
                                            pathMap, numNodes.x, numNodes.y);
        printf("starting route: %s\n", m_route.c_str());
        m_prevEnd = end;

        m_walk = 0;
        m_di = m_route[m_walk] - '0';
        m_dest.x = ((int) pos.x / TILE_DIM + dx[m_di]) * TILE_DIM;
        m_dest.y = ((int) pos.y / TILE_DIM + dy[m_di]) * TILE_DIM;
        m_init = false;
    // already initialized
    } else {
        // if not at destination
        if (pos != m_dest) {
            // if was knockbacked, reset
            if (m_actor->getKnockback()) {
                m_actor->setKnockback(false);
                m_init = true;
                printf("processed knockback!\n");
                return;
            }

            // If movement is more than 1 pixel, bad things will happen...
//            sf::Vector2f newPos(pos.x + (int) (SPEED/2 * deltaTime * dx[m_di]),
//                                pos.y + (int) (SPEED/2 * deltaTime * dy[m_di]));
            sf::Vector2f newPos(pos.x + dx[m_di],
                                pos.y + dy[m_di]);

            // check intersection with other mobs
            gb.top = newPos.y;
            gb.left = newPos.x;
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
                    m_actor->move(dx[m_di], dy[m_di], deltaTime);

                    sf::Vector2f dist;
                    dist.x = abs(newPos.x - m_dest.x);
                    dist.y = abs(newPos.y - m_dest.y);

                    // reset if went past destination
//                    if (dist.x > m_prevDist.x || dist.y > m_prevDist.y) {
//                        m_actor->setPosition(m_dest);
//                        printf("resetting!\n");
//                    } else {
//                        m_prevDist = dist;
//                    }
                // collided with player
                } else {
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
            m_di = m_route[m_walk] - '0';
            m_dest.x = ((int) pos.x / TILE_DIM + dx[m_di]) * TILE_DIM;
            m_dest.y = ((int) pos.y / TILE_DIM + dy[m_di]) * TILE_DIM;
            m_prevDist.x = abs(TILE_DIM * dx[m_di]);
            m_prevDist.y = abs(TILE_DIM * dy[m_di]);
        }
    }
}
