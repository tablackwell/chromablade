#ifndef BOSSSCRIPT_HPP
#define BOSSSCRIPT_HPP

#include "DynamicActor.hpp"
#include "GameLogic.hpp"
#include "PlayerView.hpp"
#include "ChromaBlade.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class BossScript{
public:
    BossScript(DynamicActor *actor, GameLogic *gameLogic, ChromaBlade *game);
    void update(const PlayerView* target, float &deltaTime);

private:
    DynamicActor *m_greyscale;
    GameLogic *m_gameLogic;
    ChromaBlade *m_game;
    sf::Vector2i m_prevEnd;
    sf::Vector2i m_di;
    sf::Vector2f m_dest;
    sf::Vector2f m_prevDist;
    std::vector<sf::Vector2f> m_positions;
    std::string m_route;
    int m_walk;
};

#endif
