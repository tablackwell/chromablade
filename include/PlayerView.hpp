#ifndef PLAYERVIEW_HPP
#define PLAYERVIEW_HPP

#include "EventInterface.hpp"
#include "Process.hpp"
#include "GameLogic.hpp"
#include "AnimatedSprite.hpp"
#include "Title.hpp"
#include "TileMap.hpp"
#include "Pause.hpp"
#include "PlayerDied.hpp"
#include "Instruction.hpp"

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>

class ChromaBlade; // Forward declaration of class ChromaBlade, so that we can declare a pointer to ChromaBlade in PlayerView


class PlayerView : public Process {
public:
    PlayerView();
    void init();
    void update(float &deltaTime);
    void draw();
    void setContext(sf::RenderWindow* window);
    void handleInput(float);
    bool isOpen();
    void setGameLogic(GameLogic* gameLogic);
    void setGameApplication(ChromaBlade* game);
    void clearTileMaps();
    void setMobAnimation(sf::Color col, DynamicActor &mob);
    void setRockTexture(Actor &rock);

    // event related methods
    void setListener();
    void update1(const EventInterface& event);
    void moveChar(const EventInterface& event);
    void useDoor(const EventInterface& event);
    void loadMap(const EventInterface& event);
    void playerAttacked(const EventInterface &event);
    void drawAnimation(Direction dir, sf::Vector2f moving, bool noKeyPressed, float deltaTime);

    //Camera
    void updateCamera(int newX, int newY);
    void resetCamera();
    sf::Vector2f getCameraCenter();
    sf::Vector2f getCameraSize();

private: //vars and objs
    void setSwordOrientation();
    void swingSword(float deltaTime);
    void loadMonsterAnimation();
    void resetPlayer();
    void updateHealthBar();
    bool isAttacking;
    bool m_drawPlayer;
    EventManager *m_eventManager;
    Animation *m_currAnimation;
    Animation m_walkingDown;
    Animation m_walkingUp;
    Animation m_walkingRight;
    Animation m_walkingLeft;
    Animation m_redMobWalkingDown;
    Animation m_redMobWalkingUp;
    Animation m_redMobWalkingRight;
    Animation m_redMobWalkingLeft;
    Animation m_blueMobWalkingDown;
    Animation m_blueMobWalkingUp;
    Animation m_blueMobWalkingRight;
    Animation m_blueMobWalkingLeft;
    Animation m_yellowMobWalkingDown;
    Animation m_yellowMobWalkingUp;
    Animation m_yellowMobWalkingRight;
    Animation m_yellowMobWalkingLeft;
    sf::View m_camera;
    sf::View m_pauseCamera;
    sf::FloatRect m_boundaryBox;
    sf::RectangleShape m_totalHealth;
    sf::RectangleShape m_health;
    AnimatedSprite m_animatedSprite;
    sf::RenderWindow* m_window;
    sf::Texture m_charTexture;
    sf::Texture m_monsterTexture;
    sf::Texture m_swordTexture;
    sf::Sprite m_sword;
    //sf::RectangleShape m_filter;
    GameLogic* m_gameLogic;
    ChromaBlade* m_game;
    TileMap m_map;
    TileMap m_overlay;
    TileMap m_collisions;
    TileMap m_doors;
    Title m_title;
    Pause m_pause;
    PlayerDied m_playerDied;
    Instruction m_instruction;
    sf::Sound m_swingSound;
    sf::SoundBuffer m_swingBuffer;
    sf::Sound m_switchSound;
    sf::SoundBuffer m_switchBuffer;
};

#endif
