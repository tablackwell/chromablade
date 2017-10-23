#include "GameLogic.hpp"
#include "EventManager.hpp"

GameLogic::GameLogic(){

}

void GameLogic::init(){
	m_level = red;
}

void GameLogic::update(float deltaTime){
	m_eventManager.handleEvents();
}

Level GameLogic::getLevel(){
	return m_level;
}

