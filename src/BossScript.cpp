#include "BossScript.hpp"
#include "Macros.hpp"

BossScript::BossScript(DynamicActor *actor, GameLogic *gameLogic, ChromaBlade *game) {
    m_greyscale = actor;
    m_gameLogic = gameLogic;
    m_game = game;
    m_prevEnd.x = m_prevEnd.y = -1;
    m_dest.x = m_dest. y = -1;
    m_route = "";
    m_walk = 0;
    currIndex = 0;
    m_positions.push_back(sf::Vector2f(96,96));
}

void BossScript::update(const PlayerView* targetWindow, float &deltaTime){

}
