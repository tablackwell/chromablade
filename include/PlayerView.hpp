#ifndef PLAYERVIEW_HPP
#define PLAYERVIEW_HPP

#include "EventInterface.hpp"
#include "Process.hpp"
#include "GameLogic.hpp"
#include "AnimatedSprite.hpp"
#include "Title.hpp"
#include "TileMap.hpp"

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


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

    // event related methods
    void update1(const EventInterface &event);
    void setListener();
    void moveChar(const EventInterface& event);
    void useDoor(const EventInterface& event);
    void loadMap(const EventInterface& event);
    void drawAnimation(Direction dir, sf::Vector2f moving, bool noKeyPressed, float deltaTime);

    //Camera
    void updateCamera(int newX, int newY);
    void resetCamera();
    sf::Vector2f getCameraCenter();
    sf::Vector2f getCameraSize();

private: //vars and objs
    EventManager *m_eventManager;
    Animation *currAnimation;
    Animation walkingDown;
    Animation walkingUp;
    Animation walkingRight;
    Animation walkingLeft;
    sf::View m_camera;
    sf::FloatRect boundaryBox;
    AnimatedSprite animatedSprite;
    sf::RenderWindow* m_window;
    sf::Sprite m_character;
    sf::Texture m_charTexture;
    sf::RectangleShape m_filter;
    int prevX;
    int prevY;
    float m_speed;
    bool m_notReleased;
    bool m_onDoor;
    bool levelToggled = false;
    GameLogic* m_gameLogic;
    ChromaBlade* m_game;
    TileMap m_map;
    TileMap m_overlay;
    TileMap m_collisions;
    TileMap m_doors;
    TileMap m_map2;
    TileMap m_overlay2;
    TileMap m_collisions2;
    TileMap m_doors2;
    Title m_title;
    sf::Sound m_sound;
    sf::SoundBuffer m_buffer;
};

#endif
