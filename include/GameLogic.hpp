#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP


#include "Process.hpp"
#include "Player.hpp"
#include "EventInterface.hpp"
#include "MoveEvent.hpp"
#include "EventManager.hpp"
#include "EventListener.hpp"
#include "EventType.hpp"
#include "Actor.hpp"
#include <tuple>
#include <functional>

#define SPEED 200.f

class ChromaBlade;
class PlayerView;

class GameLogic : public Process {
public:
    enum Level { red, blue, yellow, green, orange, purple };
    GameLogic();
    void init();
    void update(float &deltaTime);
    Level getLevel();
    void setCharPosition(std::tuple<float, float> position);
    void setGameApplication(ChromaBlade* game);
    void setView(PlayerView* view);
    void setListener();
    std::vector<Actor*> getRocks();
    void clearRocks();

private:
    void moveChar(const EventInterface& event);
    void attack(const EventInterface& event);
    void spawn(const EventInterface& event);

private:
    Level m_level;
    Player m_player;
    ChromaBlade* m_game;
    PlayerView* m_view;
    std::vector<Actor*> m_rocks;
};

#endif
