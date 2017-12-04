#include "PlayerView.hpp"
#include "GameState.hpp"
#include "ChromaBlade.hpp"
#include "KeySetting.hpp"
#include "Actor.hpp"

#include "MoveEvent.hpp"
#include "DoorEvent.hpp"
#include "AttackEvent.hpp"
#include "SpawnEvent.hpp"
#include "LoadMapEvent.hpp"
#include "SwitchColorEvent.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <cstdio>
#include <iostream>
#include <math.h>

#define SPEED 200.f


PlayerView::PlayerView() : Process() {
}


/* Initialize player view by loading files and setting initial positions */
void PlayerView::init(){

    // Load title screen.
    m_title.init();
    m_pause.init();
    m_playerDied.init();

    // Load texture for character
    if(!m_charTexture.loadFromFile("../res/sprite/spritenew.png")) {
        // ERROR
    }

    // Load sound for sword swing
    m_buffer.loadFromFile("../res/sfx/swordSwing.wav");
    m_sound.setBuffer(m_buffer);

    // Load texture for sword
    if(!m_swordTexture.loadFromFile("../res/sprite/sword.png")) {
         // ERROR
    }
    m_sword.setTexture(m_swordTexture);
    m_sword.setColor(sf::Color(255, 0, 0));
    m_sword.setTextureRect(sf::IntRect(21, 111, 42, 57));
    m_sword.setScale(0.5,0.5);

    // Load animations
    m_walkingDown.setSpriteSheet(m_charTexture);
    m_walkingDown.addFrame(sf::IntRect(0, 0, 32, 32));
    m_walkingDown.addFrame(sf::IntRect(0, 32, 32, 32));
    m_walkingDown.addFrame(sf::IntRect(0, 64, 32, 32));
    m_walkingDown.addFrame(sf::IntRect(0, 96, 32, 32));

    m_walkingLeft.setSpriteSheet(m_charTexture);
    m_walkingLeft.addFrame(sf::IntRect(32, 0, 32, 32));
    m_walkingLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    m_walkingLeft.addFrame(sf::IntRect(32, 64, 32, 32));
    m_walkingLeft.addFrame(sf::IntRect(32, 96, 32, 32));

    m_walkingRight.setSpriteSheet(m_charTexture);
    m_walkingRight.addFrame(sf::IntRect(96, 0, 32, 32));
    m_walkingRight.addFrame(sf::IntRect(96, 32, 32, 32));
    m_walkingRight.addFrame(sf::IntRect(96, 64, 32, 32));
    m_walkingRight.addFrame(sf::IntRect(96, 96, 32, 32));

    m_walkingUp.setSpriteSheet(m_charTexture);
    m_walkingUp.addFrame(sf::IntRect(64, 0, 32, 32));
    m_walkingUp.addFrame(sf::IntRect(64, 32, 32, 32));
    m_walkingUp.addFrame(sf::IntRect(64, 64, 32, 32));
    m_walkingUp.addFrame(sf::IntRect(64, 96, 32, 32));

    loadMonsterAnimation();

    resetPlayer();

    setState(Process::RUNNING);
    m_camera.setSize(WIDTH,HEIGHT);
    m_pauseCamera.reset(sf::FloatRect(0, 0, WIDTH, HEIGHT));
    //m_filter.setSize(sf::Vector2f(WIDTH,HEIGHT));
}

void PlayerView::resetPlayer() {
    m_currAnimation = &m_walkingDown;
    m_animatedSprite.setPosition(HUB_POS); // (196,255)
    setSwordOrientation();
    m_animatedSprite.setScale(0.9f,0.9f);
    m_animatedSprite.play(*m_currAnimation);
    isAttacking = false;
    m_drawPlayer = true;

    m_totalHealth.setSize(sf::Vector2f(30, 7));
    m_totalHealth.setFillColor(sf::Color(255, 0, 0));
    m_totalHealth.setOutlineColor(sf::Color(0, 0, 0));
    m_totalHealth.setOutlineThickness(1);
    m_health.setSize(sf::Vector2f(30, 7));
    m_health.setFillColor(sf::Color(0, 255, 0));

    updateHealth();
}

/* Update health bar and move with player */
void PlayerView::updateHealth() {
    float x = m_animatedSprite.getPosition().x;
    float y = m_animatedSprite.getPosition().y - 10;

    // Calculate pixels for player health convert to ratio of health:30
    // x = 30*playerHealth / 100
    float health = m_gameLogic->getPlayerHealth();
    float newHealth = (30 * health) / 100;

    m_totalHealth.setPosition(sf::Vector2f(x, y));
    m_health.setSize(sf::Vector2f(newHealth, 7));
    m_health.setPosition(sf::Vector2f(x, y));
}


void PlayerView::loadMonsterAnimation() {
    // Load texture for monster
    if(!m_monsterTexture.loadFromFile("../res/sprite/enemies.png")) {
        // ERROR
    }
    // Red mob
    m_redMobWalkingDown.setSpriteSheet(m_monsterTexture);
    m_redMobWalkingDown.addFrame(sf::IntRect(0, 32, 32, 32));
    m_redMobWalkingDown.addFrame(sf::IntRect(32, 32, 32, 32));
    m_redMobWalkingDown.addFrame(sf::IntRect(64, 32, 32, 32));

    m_redMobWalkingLeft.setSpriteSheet(m_monsterTexture);
    m_redMobWalkingLeft.addFrame(sf::IntRect(288, 32, 32, 32));
    m_redMobWalkingLeft.addFrame(sf::IntRect(320, 32, 32, 32));
    m_redMobWalkingLeft.addFrame(sf::IntRect(352, 32, 32, 32));

    m_redMobWalkingRight.setSpriteSheet(m_monsterTexture);
    m_redMobWalkingRight.addFrame(sf::IntRect(384, 32, 32, 32));
    m_redMobWalkingRight.addFrame(sf::IntRect(416, 32, 32, 32));
    m_redMobWalkingRight.addFrame(sf::IntRect(448, 32, 32, 32));

    m_redMobWalkingUp.setSpriteSheet(m_monsterTexture);
    m_redMobWalkingUp.addFrame(sf::IntRect(192, 32, 32, 32));
    m_redMobWalkingUp.addFrame(sf::IntRect(224, 32, 32, 32));
    m_redMobWalkingUp.addFrame(sf::IntRect(256, 32, 32, 32));

    // Blue mob
    m_blueMobWalkingDown.setSpriteSheet(m_monsterTexture);
    m_blueMobWalkingDown.addFrame(sf::IntRect(0, 96, 32, 32));
    m_blueMobWalkingDown.addFrame(sf::IntRect(32, 96, 32, 32));
    m_blueMobWalkingDown.addFrame(sf::IntRect(64, 96, 32, 32));

    m_blueMobWalkingLeft.setSpriteSheet(m_monsterTexture);
    m_blueMobWalkingLeft.addFrame(sf::IntRect(288, 96, 32, 32));
    m_blueMobWalkingLeft.addFrame(sf::IntRect(320, 96, 32, 32));
    m_blueMobWalkingLeft.addFrame(sf::IntRect(352, 96, 32, 32));

    m_blueMobWalkingRight.setSpriteSheet(m_monsterTexture);
    m_blueMobWalkingRight.addFrame(sf::IntRect(384, 96, 32, 32));
    m_blueMobWalkingRight.addFrame(sf::IntRect(416, 96, 32, 32));
    m_blueMobWalkingRight.addFrame(sf::IntRect(448, 96, 32, 32));

    m_blueMobWalkingUp.setSpriteSheet(m_monsterTexture);
    m_blueMobWalkingUp.addFrame(sf::IntRect(96, 96, 32, 32));
    m_blueMobWalkingUp.addFrame(sf::IntRect(128, 96, 32, 32));
    m_blueMobWalkingUp.addFrame(sf::IntRect(160, 96, 32, 32));

    // Yellow mob
    m_yellowMobWalkingDown.setSpriteSheet(m_monsterTexture);
    m_yellowMobWalkingDown.addFrame(sf::IntRect(0, 64, 32, 32));
    m_yellowMobWalkingDown.addFrame(sf::IntRect(32, 64, 32, 32));
    m_yellowMobWalkingDown.addFrame(sf::IntRect(64, 64, 32, 32));

    m_yellowMobWalkingLeft.setSpriteSheet(m_monsterTexture);
    m_yellowMobWalkingLeft.addFrame(sf::IntRect(288, 64, 32, 32));
    m_yellowMobWalkingLeft.addFrame(sf::IntRect(320, 64, 32, 32));
    m_yellowMobWalkingLeft.addFrame(sf::IntRect(352, 64, 32, 32));

    m_yellowMobWalkingRight.setSpriteSheet(m_monsterTexture);
    m_yellowMobWalkingRight.addFrame(sf::IntRect(384, 64, 32, 32));
    m_yellowMobWalkingRight.addFrame(sf::IntRect(416, 64, 32, 32));
    m_yellowMobWalkingRight.addFrame(sf::IntRect(448, 64, 32, 32));

    m_yellowMobWalkingUp.setSpriteSheet(m_monsterTexture);
    m_yellowMobWalkingUp.addFrame(sf::IntRect(96, 64, 32, 32));
    m_yellowMobWalkingUp.addFrame(sf::IntRect(128, 64, 32, 32));
    m_yellowMobWalkingUp.addFrame(sf::IntRect(160, 64, 32, 32));
}


/* Set the window of the view */
void PlayerView::setContext(sf::RenderWindow* window){
  m_window = window;
  sf::View view = window->getDefaultView();
  window->setView(view);
}


/* Link the game logic with player view */
void PlayerView::setGameLogic(GameLogic* gameLogic) {
    m_gameLogic = gameLogic;
    gameLogic->setAnimatedSprite(&m_animatedSprite);
}


/* Link the game application with player view, so that we can check game state. */
void PlayerView::setGameApplication(ChromaBlade* game) {
    m_game = game;
}


/* Handle user inputs */
void PlayerView::handleInput(float deltaTime) {
    // First check game state
    GameState state = m_game->getState();
    switch(state) {
        case GameState::Title:
            int rc;
            rc = m_title.update(*m_window);
            if (rc == 0) {} // Moved the cursor
            else if (rc == 1) { // Selected Play
                ChangeStateEvent* changeState = new ChangeStateEvent(GameState::Hub);
                LoadMapEvent* loadMap = new LoadMapEvent(GameState::Hub);
                m_game->queueEvent(changeState);
                m_game->queueEvent(loadMap);
                resetCamera();
                updateCamera(HUB_CAM);
            }
            else m_window->close(); // Selected Exit
            break;
        case GameState::Pause:
            rc = m_pause.update(*m_window);
            if(rc == 0) {} //Moved the cursor
            else if (rc == 1) { // Selected Resume
                m_window->setView(m_camera);
                GameState state = m_game->getPrevState();
                ChangeStateEvent* changeState = new ChangeStateEvent(state);
                m_game->queueEvent(changeState);
            }
            else m_window->close();
            break;
        case GameState::PlayerDied:
            rc = m_playerDied.update(*m_window);
            if (rc == 0) {} // Moved the cursor
            else if (rc == 1) { // Selected Restart
                resetPlayer();
                m_gameLogic->resetCharacter();
                resetCamera();
                updateCamera(HUB_CAM);
                // Load hub
                ChangeStateEvent* changeState = new ChangeStateEvent(GameState::Hub);
                LoadMapEvent* loadMap = new LoadMapEvent(GameState::Hub);
                m_game->queueEvent(changeState);
                m_game->queueEvent(loadMap);
            }
            else m_window->close();
            break;
        default: // in the game
            sf::Event event;
            while(m_window->pollEvent(event)){
                // Close window
                if(event.type == sf::Event::Closed){
                    m_window->close();
                }
                else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == KEY_ATTACK && !isAttacking) {
                        Direction dir;
                        if (m_currAnimation == &m_walkingUp) {
                            dir = Up;
                        }
                        else if (m_currAnimation == &m_walkingDown) {
                            dir = Down;
                        }
                        else if (m_currAnimation == &m_walkingLeft) {
                            dir = Left;
                        }
                        else if (m_currAnimation == &m_walkingRight) {
                            dir = Right;
                        }
                        AttackEvent *attack = new AttackEvent(true, dir, m_sword.getColor());
                        m_game->queueEvent(attack);
                        m_sound.play();
                        isAttacking = true;
                    }
                    if (event.key.code == KEY_RED) {
                        SwitchColorEvent *switchColor = new SwitchColorEvent(sf::Color::Red);
                        m_game->queueEvent(switchColor);
                        if (m_gameLogic->hasColor(sf::Color::Red)) {
                            m_sword.setColor(sf::Color(255, 0, 0));
                        }

                    }
                    if (event.key.code == KEY_BLUE) {
                        SwitchColorEvent *switchColor = new SwitchColorEvent(sf::Color::Blue);
                        m_game->queueEvent(switchColor);
                        if (m_gameLogic->hasColor(sf::Color::Blue)) {
                            m_sword.setColor(sf::Color(0, 0, 255));
                        }
                    }
                    if (event.key.code == KEY_YELLOW) {
                        SwitchColorEvent *switchColor = new SwitchColorEvent(sf::Color::Yellow);
                        m_game->queueEvent(switchColor);
                        if (m_gameLogic->hasColor(sf::Color::Yellow)) {
                            m_sword.setColor(sf::Color(255, 255, 0));
                        }
                    }
                    if (event.key.code == KEY_PAUSE) {
                        m_window->setView(m_pauseCamera);
                        ChangeStateEvent *changeState = new ChangeStateEvent(GameState::Pause);
                        m_game->queueEvent(changeState);
                        int levelCleared_int = m_gameLogic->getLevelsCleared();
                        m_pause.setLevelsCleared(levelCleared_int);
                    }
                }
            }
            sf::Vector2f v;
            Direction dir;

            if (sf::Keyboard::isKeyPressed(KEY_LEFT)){
                v.x -= SPEED;
            } else if (sf::Keyboard::isKeyPressed(KEY_RIGHT)){
                v.x += SPEED;
            } if (sf::Keyboard::isKeyPressed(KEY_UP)){
                v.y -= SPEED;
            } else if (sf::Keyboard::isKeyPressed(KEY_DOWN)){
                v.y += SPEED;
            }

            if (v.x != 0.f && v.y != 0.f) {
                v.x /= sqrt(2.f);
                v.y /= sqrt(2.f);
            }

            if (v.x > 0) {
                MoveEvent *move = new MoveEvent(Direction::Right, v.x);
                m_game->queueEvent(move);
            } else if (v.x < 0) {
                MoveEvent *move = new MoveEvent(Direction::Left, v.x);
                m_game->queueEvent(move);
            }

            if (v.y > 0) {
                MoveEvent *move = new MoveEvent(Direction::Down, v.y);
                m_game->queueEvent(move);
            } else if (v.y < 0) {
                MoveEvent *move = new MoveEvent(Direction::Up, v.y);
                m_game->queueEvent(move);
            }
            break;
    }
}


/* Camera Functions */
void PlayerView::updateCamera(int newX, int newY){
  m_camera.setCenter(m_camera.getCenter().x + newX, m_camera.getCenter().y + newY);
  m_window->setView(m_camera);
}

void PlayerView::resetCamera(){
  m_camera.setCenter(0,0);
  m_window->setView(m_camera);
}

sf::Vector2f PlayerView::getCameraCenter(){
  return m_camera.getCenter();
}

sf::Vector2f PlayerView::getCameraSize(){
  return m_camera.getSize();
}


/* Render */
void PlayerView::draw() {
    m_window->clear();
    GameState state = m_game->getState();
    std::vector<Actor*> rocks = m_gameLogic->getRocks();
    std::vector<DynamicActor*> mobs = m_gameLogic->getMobs();

    // Render the content depending on the game state
    switch(state) {
        case GameState::Title:
            m_title.draw(*m_window);
            break;
        case GameState::Pause:
            m_pause.draw(*m_window);
            break;
        case GameState::PlayerDied:
            m_window->draw(m_map);
            m_window->draw(m_overlay); // Draw background of incomplete dungeon
            m_playerDied.draw(*m_window);
            break;
        default:
            m_window->draw(m_map);
            m_window->draw(m_overlay);
            for (int i=0; i<rocks.size(); i++) {
                rocks[i]->draw(m_window);
            }
            for (int i=0; i<mobs.size(); i++) {
                mobs[i]->draw(m_window);
            }
            // m_window->draw(m_filter);

            if (m_drawPlayer) {
                m_window->draw(m_sword);
                m_window->draw(m_animatedSprite);
                m_window->draw(m_totalHealth);
                m_window->draw(m_health);
            }

            /* Debug stuff */
            if(m_game->inDebugMode()){
              sf::RectangleShape debugRectangle(sf::Vector2f(m_animatedSprite.getGlobalBounds().width, m_animatedSprite.getGlobalBounds().height));
              debugRectangle.setFillColor(sf::Color(250, 150, 100, 150));
              debugRectangle.setPosition(m_animatedSprite.getPosition().x, m_animatedSprite.getPosition().y);
              m_window->draw(debugRectangle);
              m_collisions.drawBoxes(m_window);
              m_doors.drawBoxes(m_window);
              /*temporary ugly portal stuff*/
              sf::RectangleShape bluePortal(sf::Vector2f(32,32));
              bluePortal.setPosition(384,32);
              bluePortal.setFillColor(sf::Color(0, 0, 255, 100));
              sf::RectangleShape redPortal(sf::Vector2f(32,32));
              redPortal.setPosition(1184,32);
              redPortal.setFillColor(sf::Color(255,0,0,100));
              sf::RectangleShape yellowPortal(sf::Vector2f(32,32));
              yellowPortal.setPosition(1984,32);
              yellowPortal.setFillColor(sf::Color(255,255,0,100));
              sf::RectangleShape greyPortal(sf::Vector2f(32,32));
              greyPortal.setPosition(1184,880);
              greyPortal.setFillColor(sf::Color(128,128,128,100));
              m_window->draw(bluePortal);
              m_window->draw(redPortal);
              m_window->draw(yellowPortal);
              m_window->draw(greyPortal);
            }
            break;
    }
    m_window->display();
}


/* Check if the window is open */
bool PlayerView::isOpen(){
    return m_window->isOpen();
}


/* Update view. */
void PlayerView::update(float &deltaTime){
    updateHealth();
    if (isAttacking) {
        if (m_sword.getRotation() < 70 || m_sword.getRotation() > 290) {
            swingSword(deltaTime);
        }
        else {
            isAttacking = false;
        }
    }
    else {
        m_sword.setRotation(0);
    }
}


/* Play sword animation */
void PlayerView::swingSword(float deltaTime) {
    if (m_currAnimation == &m_walkingUp) { // works
        m_sword.rotate(deltaTime * 600);
    }
    else if (m_currAnimation == &m_walkingDown) {
        m_sword.rotate(deltaTime * -600);
    }
    else if (m_currAnimation == &m_walkingLeft) { // works
        m_sword.rotate(deltaTime * 600);
    }
    else if (m_currAnimation == &m_walkingRight) {
        m_sword.rotate(deltaTime * -600);
    }
}


/* Set sword orientation according to the direction that the character is facing; called when drawing animation */
void PlayerView::setSwordOrientation() {
    if (m_currAnimation == &m_walkingUp) {
        m_sword.setOrigin(42, 57);
        m_sword.setTextureRect(sf::IntRect(21, 4, 42, 57));
        m_sword.setPosition(m_animatedSprite.getPosition().x + 6, m_animatedSprite.getPosition().y + 23.5);
    }
    else if (m_currAnimation == &m_walkingDown) {
        m_sword.setOrigin(42, 0);
        m_sword.setTextureRect(sf::IntRect(21, 111, 42, 57));
        m_sword.setPosition(m_animatedSprite.getPosition().x + 6, m_animatedSprite.getPosition().y + 25);
    }
    else if (m_currAnimation == &m_walkingLeft) {
        m_sword.setOrigin(57, 21);
        m_sword.setTextureRect(sf::IntRect(3, 64, 57, 42));
        m_sword.setPosition(m_animatedSprite.getPosition().x + 13.5, m_animatedSprite.getPosition().y + 25.5);
    }
    else if (m_currAnimation == &m_walkingRight) {
        m_sword.setOrigin(0, 21);
        m_sword.setTextureRect(sf::IntRect(122, 64, 57, 42));
        m_sword.setPosition(m_animatedSprite.getPosition().x + 10, m_animatedSprite.getPosition().y + 25.5);
    }
}


/* Adds listeners to eventManager */
void PlayerView::setListener() {
    // LoadMapEvent
    std::function<void(const EventInterface &event)> loadMap = std::bind(&PlayerView::loadMap, this, std::placeholders::_1);
    const EventListener loadMapListener = EventListener(loadMap, EventType::loadMapEvent);
    m_game->registerListener(loadMapListener, EventType::loadMapEvent);

    // AttackEvent
    std::function<void(const EventInterface &event)> attacked = std::bind(&PlayerView::playerAttacked, this, std::placeholders::_1);
    const EventListener attackListener = EventListener(attacked, 10);
    m_game->registerListener(attackListener, EventType::attackEvent);
}



void PlayerView::drawAnimation(Direction dir, sf::Vector2f moving , bool noKeyPressed, float deltaTime) {
    switch (dir) {
        case Up: {
            m_currAnimation = &m_walkingUp;
            break;
        }
        case Down: {
            m_currAnimation = &m_walkingDown;
            break;
        }
        case Right: {
            m_currAnimation = &m_walkingRight;
            break;
        }
        case Left: {
            m_currAnimation = &m_walkingLeft;
            break;
        }
    }
    setSwordOrientation();
    m_animatedSprite.play(*m_currAnimation);
    m_animatedSprite.move(moving);

    if (noKeyPressed) {
        m_animatedSprite.stop();
    }
    noKeyPressed = true;
    m_animatedSprite.update(sf::seconds(deltaTime));
}


void PlayerView::clearTileMaps() {
    fprintf(stderr, "clearTileMaps!\n");
    m_map.clear();
    m_overlay.clear();
    m_collisions.clear();
    m_doors.clear();
}


/* Load the map of a level. Triggered by a LoadMapEvent. */
void PlayerView::loadMap(const EventInterface& event) {
    fprintf(stderr, "loadMap!\n");
    const EventInterface *ptr = &event;
    const LoadMapEvent *loadMapEvent = dynamic_cast<const LoadMapEvent*>(ptr);
    const GameState state = loadMapEvent->getGameState();

    clearTileMaps();
    m_gameLogic->clearRocks();
    m_gameLogic->clearEnemies();

    switch (state) {
        case GameState::Hub:
            m_map.loadFromText("../res/tilesets/lightworld.png",
                    "../res/level/Hub/Hub_base.csv",
                    sf::Vector2u(16, 16), 150, 76);
            m_overlay.loadFromText("../res/tilesets/lightworld.png",
                    "../res/level/Hub/Hub_overlay.csv",
                    sf::Vector2u(16, 16),150, 76);
            m_collisions.loadCollisionsFromText("../res/tilesets/lightworld.png",
                    "../res/level/Hub/Hub_collision.csv",
                    sf::Vector2u(16, 16), 150, 76);
            m_doors.loadDoorsFromText("../res/tilesets/lightworld.png",
                    "../res/level/Hub/Hub_doors.csv",
                    sf::Vector2u(16, 16), 150, 76);
            m_gameLogic->setCollisionMapping(m_collisions.m_boxes, m_doors.m_boxes);
            m_gameLogic->setBoundaries(150*16, 76*16);

        break;
        case GameState::RedLevel:
            fprintf(stderr, "loading RedLevel!\n");
            m_map.loadFromText("../res/tilesets/dungeon.png",
                    "../res/level/RedDungeon/dungeon_base.csv",
                    sf::Vector2u(16, 16), 100, 114);
            m_overlay.loadFromText("../res/tilesets/dungeon.png", "../res/level/RedDungeon/dungeon_overlay.csv",
                    sf::Vector2u(16, 16), 100, 114);
            m_collisions.loadCollisionsFromText("../res/tilesets/dungeon.png",
                    "../res/level/RedDungeon/dungeon_collision.csv",
                    sf::Vector2u(16, 16), 100, 114);
            m_doors.loadDoorsFromText("../res/tilesets/dungeon.png",
                    "../res/level/RedDungeon/dungeon_doors.csv",
                    sf::Vector2u(16, 16), 100, 114);
            m_gameLogic->setCollisionMapping(m_collisions.m_boxes, m_doors.m_boxes);
            m_gameLogic->setBoundaries(100*16,114*16);
        break;
        case GameState::BlueLevel:
            fprintf(stderr, "loadingBlueLevel!\n");
            m_map.loadFromText("../res/tilesets/dungeon.png",
                    "../res/level/BlueDungeon/bluedungeon_base.csv",
                    sf::Vector2u(16, 16), 200, 76);
            m_overlay.loadFromText("../res/tilesets/dungeon.png", "../res/level/BlueDungeon/bluedungeon_overlay.csv", sf::Vector2u(16, 16),200, 76);
            m_collisions.loadCollisionsFromText("../res/tilesets/dungeon.png",
                    "../res/level/BlueDungeon/bluedungeon_collision.csv",
                    sf::Vector2u(16, 16), 200, 76);
            m_doors.loadDoorsFromText("../res/tilesets/dungeon.png",
                    "../res/level/BlueDungeon/bluedungeon_doors.csv",
                    sf::Vector2u(16, 16), 200, 76);
            m_gameLogic->setCollisionMapping(m_collisions.m_boxes, m_doors.m_boxes);
            m_gameLogic->setBoundaries(200*16,76*16);
        break;
        case GameState::YellowLevel:
        fprintf(stderr, "loadingYellow!\n");
          m_map.loadFromText("../res/tilesets/dungeon.png",
                  "../res/level/YellowDungeon/yellowdungeon_base.csv",
                  sf::Vector2u(16, 16), 150, 114);
          m_overlay.loadFromText("../res/tilesets/dungeon.png", "../res/level/YellowDungeon/yellowdungeon_overlay.csv", sf::Vector2u(16, 16),150, 114);
          m_collisions.loadCollisionsFromText("../res/tilesets/dungeon.png",
                  "../res/level/YellowDungeon/yellowdungeon_collision.csv",
                  sf::Vector2u(16, 16), 150, 114);
          m_doors.loadDoorsFromText("../res/tilesets/dungeon.png",
                  "../res/level/YellowDungeon/yellowdungeon_doors.csv",
                  sf::Vector2u(16, 16),150, 114);
          m_gameLogic->setCollisionMapping(m_collisions.m_boxes, m_doors.m_boxes);
          m_gameLogic->setBoundaries(150*16,114*16);
        break;
        case GameState::BossLevel:
        fprintf(stderr, "Loading Boss Level \n");
          m_map.loadFromText("../res/tilesets/dungeon.png",
                  "../res/level/BossLevel/bosslevel_base.csv",
                  sf::Vector2u(16, 16), 50, 76);
          m_overlay.loadFromText("../res/tilesets/dungeon.png", "../res/level/BossLevel/bosslevel_overlay.csv", sf::Vector2u(16, 16),50, 76);
          m_collisions.loadCollisionsFromText("../res/tilesets/dungeon.png",
                  "../res/level/BossLevel/bosslevel_collision.csv",
                  sf::Vector2u(16, 16), 50, 76);
          m_doors.loadDoorsFromText("../res/tilesets/dungeon.png",
                  "../res/level/BossLevel/bosslevel_doors.csv",
                  sf::Vector2u(16, 16),50, 76);
          m_gameLogic->setCollisionMapping(m_collisions.m_boxes, m_doors.m_boxes);
          m_gameLogic->setBoundaries(50*16,76*16);
        break;
    }
}


/* Player flashes on screen. Triggered by an AttackEvent. */
void PlayerView::playerAttacked(const EventInterface &event) {
    const EventInterface *ptr = &event;
    const AttackEvent *attackEvent = dynamic_cast<const AttackEvent*>(ptr);
    if (attackEvent->isFromPlayer() == false) { // enemy attack
        int stop = 10;
        int blinks = 0;
        // Toggle boolean to only draw player on some frames
        while (blinks < stop) {
            if (m_drawPlayer) {
                m_drawPlayer = false;
            } else {
                m_drawPlayer = true;
            }
            draw();
            blinks += 1;
        }
        m_drawPlayer = true;
    }
}


void PlayerView::setMobAnimation(sf::Color col, DynamicActor &mob) {
    if (col == sf::Color::Red) {
        mob.setAnimation(m_redMobWalkingLeft, m_redMobWalkingRight, m_redMobWalkingUp, m_redMobWalkingDown);
    }
    else if (col == sf::Color::Blue) {
        mob.setAnimation(m_blueMobWalkingLeft, m_blueMobWalkingRight, m_blueMobWalkingUp, m_blueMobWalkingDown);
    }
    else {
        mob.setAnimation(m_yellowMobWalkingLeft, m_yellowMobWalkingRight, m_yellowMobWalkingUp, m_yellowMobWalkingDown);
    }
}
