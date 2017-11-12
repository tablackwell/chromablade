#include "GameLogic.hpp"
#include "EventManager.hpp"
#include <cstdio>

GameLogic::GameLogic() : Process() {
}

void GameLogic::init(){
	m_level = red;
    setState(Process::RUNNING);
}

void GameLogic::update(float &deltaTime){
}

Level GameLogic::getLevel(){
	return m_level;
}

void GameLogic::setCharPosition(std::tuple<float, float> position) {
    m_player.setPosition(position);
}


