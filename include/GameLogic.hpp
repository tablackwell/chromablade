#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP


#include "Process.hpp"
#include "Player.hpp"
#include "EventInterface.hpp"
#include "MoveEvent.hpp"
#include "EventManager.hpp"
#include "EventListener.hpp"
#include "EventType.hpp"
#include <tuple>
#include <functional>

#define SPEED 200.f

enum Level { red, blue, yellow, green, orange, purple };

class ChromaBlade;

class GameLogic : public Process {
	public:
		GameLogic();
		void init();
		void update(float &deltaTime);
		Level getLevel();
		void setCharPosition(std::tuple<float, float> position);
		void setGameApplication(ChromaBlade* game);
        void setListener();

	private:
		void moveChar(const EventInterface& event);

	private:
        Level m_level;
        Player m_player;
        ChromaBlade* m_game;
};

#endif
