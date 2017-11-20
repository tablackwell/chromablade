#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP


#include "Process.hpp"
#include "Player.hpp"
#include "EventInterface.hpp"
#include "MoveEvent.hpp"
#include "EventManager.hpp"
#include "EventListener.hpp"
#include "AnimatedSprite.hpp"
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
    void setAnimatedSprite(AnimatedSprite* sprite);
    void setView(PlayerView* view);
    void setListener();
    std::vector<Actor*> getRocks();
    void clearRocks();
    void setCollisionMapping(std::vector<sf::RectangleShape>, std::vector<sf::RectangleShape>);

private:
    void moveChar(const EventInterface& event);
    void attack(const EventInterface& event);
    void spawn(const EventInterface& event);
    bool m_onDoor;

private:
    Level m_level;
    std::vector<sf::RectangleShape> m_collisionVector;
    std::vector<sf::RectangleShape> m_doors;
    Player m_player;
    AnimatedSprite* m_sprite;
    ChromaBlade* m_game;
    PlayerView* m_view;
    std::vector<Actor*> m_rocks;
};

#endif
