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
#include "GameState.hpp"
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
    void setCharPosition(sf::Vector2f position);
    void setGameApplication(ChromaBlade* game);
    void setAnimatedSprite(AnimatedSprite* sprite);
    void setView(PlayerView* view);
    void setListener();
    std::vector<Actor*> getRocks();
    std::vector<DynamicActor*> getMobs();
    void clearRocks();
    void clearEnemies();
    void setCollisionMapping(std::vector<sf::RectangleShape>, std::vector<sf::RectangleShape>);
    void setBoundaries(int xBound, int yBound);
    void toggleLevel();
    bool hasColor(sf::Color col);

private:
    bool checkCollisions(const sf::FloatRect& fr);
    bool checkDoors(sf::FloatRect fr, int extra);
    bool checkPortals(const sf::FloatRect& fr);
    void playerAttack(Direction dir);
    void enemyAttack(DynamicActor* attacker);

    // Event triggered methods
    void moveChar(const EventInterface& event);
    void attack(const EventInterface& event);
    void spawn(const EventInterface& event);
    void useDoor(const EventInterface& event);
    void switchColor(const EventInterface& event);
    void unlockColor(GameState state);


private:
    std::vector<sf::RectangleShape> m_collisionVector;
    std::vector<sf::RectangleShape> m_doors;
    std::vector<Actor*> m_rocks;
    std::vector<DynamicActor*> m_mobs;
    std::vector<int> m_clearedRooms;
    bool m_possibleMobColors[3] = {true, false, false}; // in the order of red, blue, yellow
    std::vector<sf::RectangleShape> m_portals;

    sf::RectangleShape m_redPortal;
    sf::RectangleShape m_bluePortal;
    sf::RectangleShape m_yellowPortal;
    int m_xBound;
    int m_yBound;
    sf::Vector2f dungeonReturnPosition;
    sf::Vector2f dungeonReturnCamera;
    bool inDungeon;


    Player m_player;
    AnimatedSprite* m_sprite;
    ChromaBlade* m_game;
    PlayerView* m_view;
    bool m_onDoor;
    bool m_levelToggled;
};

#endif
