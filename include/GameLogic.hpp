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

class ChromaBlade;
class PlayerView;
class AIView;

class GameLogic : public Process {
public:
    enum Level { red, blue, yellow, green, orange, purple };
    GameLogic();
    void init();
    void update(float &deltaTime);
    Level getLevel();
    void setCharPosition(sf::Vector2f position);
    void resetCharacter();
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
    int getLevelsCleared();
    float getPlayerHealth();
    char** getPathMap();
    sf::Vector2i getNumNodes();

private:
    bool checkCollisions(const sf::FloatRect& fr);
    bool checkDoors(sf::FloatRect fr, int extra);
    bool checkPortals(const sf::FloatRect& fr);
    void playerAttack(Direction dir);
    void moveMobs();
    void enemyAttack(DynamicActor* attacker);

    // Event triggered methods
    void moveChar(const EventInterface& event);
    void attack(const EventInterface& event);
    void spawn(const EventInterface& event);
    void useDoor(const EventInterface& event);
    void switchColor(const EventInterface& event);
    void unlockColor(GameState state);
    void pathMap(const EventInterface& event);


private:
    std::vector<sf::RectangleShape> m_collisionVector;
    std::vector<sf::RectangleShape> m_doors;
    std::vector<Actor*> m_rocks;
    std::vector<DynamicActor*> m_mobs;
    std::vector<int> m_clearedRooms;
    bool m_possibleMobColors[3] = {true, false, false}; // in the order of red, blue, yellow
    std::vector<sf::RectangleShape> m_portals;

    char **m_pathMap;
    sf::Vector2i m_numNodes;

    sf::RectangleShape m_redPortal;
    sf::RectangleShape m_bluePortal;
    sf::RectangleShape m_yellowPortal;
    sf::RectangleShape m_greyPortal;

    int m_xBound;
    int m_yBound;
    sf::Vector2f dungeonReturnPosition;
    sf::Vector2f dungeonReturnCamera;
    bool inCombat;
    bool bossAvailable;

    Player m_player;
    AnimatedSprite* m_sprite;
    ChromaBlade* m_game;
    PlayerView* m_view;
    std::vector<AIView*> m_aiviews;
    bool m_onDoor;
    bool m_levelToggled;
};

#endif
