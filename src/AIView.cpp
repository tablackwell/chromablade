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

    sf::FloatRect pgb = pview->getGlobalBounds();
    sf::Vector2f target(pgb.left + pgb.width * 0, pgb.top + pgb.height * 0);

    sf::Vector2i start((int) pos.x % WIDTH / MINI_TILE_DIM,
                       (int) pos.y % HEIGHT / MINI_TILE_DIM);
    sf::Vector2i end((int) target.x % WIDTH / MINI_TILE_DIM,
                     (int) target.y % HEIGHT / MINI_TILE_DIM);

    // initialize
    if (m_init) {
        std::vector<int> xs, ys;
        sf::FloatRect mgb;
        
        // Add collision markers for other mobs
        for (int i = 0; i < mobs.size(); i++) {
            mgb = mobs[i]->getGlobalBounds();

            // Ignore self
            if (mgb == gb) continue;

            // Mobs are 32x32.
            // Mob position is top-left oriented, so add padding on top and left.
            for (int i=0; i<9; i++) {
                int x = (int) mgb.left % WIDTH / MINI_TILE_DIM - 1 + i / 3;
                int y = (int) mgb.top % HEIGHT / MINI_TILE_DIM - 1 + i % 3;
                if (x > 0 && y > 0) {
                    if (pathMap[x][y] != '#') {
                        pathMap[x][y] = '#';
                        xs.push_back(x);
                        ys.push_back(y);
                    }
                }
            }
        }

        // Find the path
        m_route = AStar::pathFind(start.x, start.y, end.x, end.y,
                                            pathMap, numNodes.x, numNodes.y);

        // Clean up collision markers for other mobs
        for (int i=0; i<xs.size(); i++) {
            pathMap[xs[i]][ys[i]] = ' ';
        }

        m_prevEnd = end;
        if (m_route == "") return;

        m_walk = 0;
        m_di = m_route[m_walk] - '0';
        m_dest.x = ((int) pos.x / MINI_TILE_DIM + dx[m_di]) * MINI_TILE_DIM;
        m_dest.y = ((int) pos.y / MINI_TILE_DIM + dy[m_di]) * MINI_TILE_DIM;
        m_init = false;
    // already initialized
    } else {
        // if not at destination
        if (pos != m_dest) {
            // if was knockbacked, reset
            if (m_actor->getKnockback()) {
                m_actor->setKnockback(false);
                m_init = true;
                return;
            }

            // set speeds based on color
            int speed = m_actor->getSpeed();
            sf::Vector2i d;
            if (speed == RED_SPEED) {
                d.x = dx[m_di] * 1;
                d.y = dy[m_di] * 1;
            } else if (speed == BLUE_SPEED) {
                d.x = dx[m_di] * 2;
                d.y = dy[m_di] * 2;
            } else if (speed == YELLOW_SPEED) {
                d.x = dx[m_di] * 4;
                d.y = dy[m_di] * 4;
            }

            // check intersection with other mobs
            sf::Vector2f newPos(pos.x + d.x, pos.y + d.y);
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
                    m_actor->move(d.x, d.y, deltaTime);

                // else collided with player, so attack
                } else {
                    if (m_actor->canAttack()) {
                        AttackEvent *attackEvent = new AttackEvent(false, m_actor);
                        m_game->queueEvent(attackEvent);
                    }

                    m_actor->updateAttackClock(deltaTime);
                }
            }

        // reached destination
        } else {
            // if target has moved, get a new route
            if (end != m_prevEnd) {
                m_init = true;
            // else get next destination node
            } else {
                m_walk++;
                m_di = m_route[m_walk] - '0';
                m_dest.x = ((int) pos.x / MINI_TILE_DIM + dx[m_di]) * MINI_TILE_DIM;
                m_dest.y = ((int) pos.y / MINI_TILE_DIM + dy[m_di]) * MINI_TILE_DIM;
            }
        }
    }
}
