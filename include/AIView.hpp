#ifndef AIVIEW_HPP
#define AIVIEW_HPP

#include "DynamicActor.hpp"
#include "GameLogic.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class AIView {
public:
    AIView(DynamicActor *actor, GameLogic *gameLogic);
    void move(const sf::Vector2f& target);

private:
    DynamicActor *m_actor;
    GameLogic *m_gameLogic;
    sf::Vector2i m_prevEnd;
    std::string m_route;
};

#endif
