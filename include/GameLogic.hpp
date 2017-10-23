#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP

#include "EventManager.hpp"
#include "Player.hpp"
enum Level { red, blue, yellow, green, orange, purple };

class GameLogic{
	public:
		GameLogic();
		void init();
		void update(float deltaTime);
		Level getLevel();
	private:
		Level m_level;
		//Player m_player;
		EventManager m_eventManager;
	private:
};

#endif
