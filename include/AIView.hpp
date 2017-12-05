#ifndef AIVIEW_HPP
#define AIVIEW_HPP

#include "DynamicActor.hpp"
#include "GameLogic.hpp"
#include "PlayerView.hpp"
#include "ChromaBlade.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class AIView {
public:
    AIView(DynamicActor *actor, GameLogic *gameLogic, ChromaBlade *game);
    void move(const PlayerView* target, float &deltaTime);

private:
    DynamicActor *m_actor;
    GameLogic *m_gameLogic;
    ChromaBlade *m_game;
    sf::Vector2i m_prevEnd;
    sf::Vector2f m_dest;
    sf::Vector2f m_prevDist;
    std::string m_route;
    int m_walk;
    int m_di;
    bool m_init;
};

#endif
