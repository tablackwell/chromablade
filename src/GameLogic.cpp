#include "GameLogic.hpp"
#include "MoveEvent.hpp"
#include "ChromaBlade.hpp"

#include <tuple>
#include <iostream>


GameLogic::GameLogic() : Process() {
    init();
}

void GameLogic::init(){
	m_level = red;
    setState(Process::RUNNING);
//    registerListener();
}

void GameLogic::update(float &deltaTime){
}

Level GameLogic::getLevel(){
	return m_level;
}

void GameLogic::setCharPosition(std::tuple<float, float> position) {
    m_player.setPosition(position);
    std::cout << std::get<0>(position);
}


/* Adds listeners to eventManager */
void GameLogic::registerListener() {
    // Create function for listener. Add to event manager.
    std::function<void(const EventInterface &event)> move = std::bind(&GameLogic::moveChar, this, std::placeholders::_1);
    const EventListener listener = EventListener(move, 5);
    m_game->registerListener(listener, EventType::moveEvent);
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

