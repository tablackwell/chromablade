#include "GameLogic.hpp"
#include "MoveEvent.hpp"
#include "AttackEvent.hpp"
#include "ChromaBlade.hpp"

#include <tuple>
#include <iostream>


GameLogic::GameLogic() : Process() {
}

void GameLogic::init(){
	m_level = red;
    setState(Process::RUNNING);
}

void GameLogic::update(float &deltaTime){
}

GameLogic::Level GameLogic::getLevel(){
	return m_level;
}


/* Links game logic to game application */
void GameLogic::setGameApplication(ChromaBlade* game) {
    m_game = game;
}


/* Sets the position of character */
void GameLogic::setCharPosition(std::tuple<float, float> position) {
    m_player.setPosition(position);
    //std::cout << std::get<0>(position) << "\n";
    //std::cout << std::get<1>(position) << "\n";
}


/* Used to build a listener for moveEvent */
void GameLogic::moveChar(const EventInterface& event) {
    const EventInterface *ptr = &event;
    const MoveEvent *moveEvent = dynamic_cast<const MoveEvent*>(ptr);
    Direction dir = moveEvent->getDirection();
    float deltaTime = moveEvent->getDeltaTime();
    float x = std::get<0>(m_player.getPosition());
    float y = std::get<1>(m_player.getPosition());
    switch (dir){
    case Up:
        y = y - SPEED * deltaTime;
        break;
    case Down:
        y = y + SPEED * deltaTime;
        break;
    case Left:
        x = x - SPEED * deltaTime;
        break;
    case Right:
        x = x + SPEED * deltaTime;
        break;
    }
    setCharPosition(std::make_tuple(x, y));
}


/* Adds listeners to eventManager */
void GameLogic::setListener() {
    // Create function for listener. Add to event manager.
//    std::function<void(const EventInterface &event)> move = std::bind(&GameLogic::moveChar, this, std::placeholders::_1);
//    const EventListener moveListener = EventListener(move, 3);
//    m_game->registerListener(moveListener, EventType::moveEvent);
    std::function<void(const EventInterface &event)> attack = std::bind(&GameLogic::attack, this, std::placeholders::_1);
        const EventListener attackListener = EventListener(attack, 4);
        m_game->registerListener(attackListener, EventType::attackEvent);
}


void GameLogic::attack(const EventInterface& event) {
    const EventInterface *ptr = &event;
    const AttackEvent *attackEvent = dynamic_cast<const AttackEvent*>(ptr);
    if (attackEvent->getInitiator() == NULL) { // player attack
        // TODO: look for enemies nearby
        m_player.attack();
        std::cout << "player attack\n";
    }

}
