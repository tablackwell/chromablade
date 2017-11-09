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
	m_eventManager.update();
}

Level GameLogic::getLevel(){
	return m_level;
}

